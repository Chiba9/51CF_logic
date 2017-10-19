#pragma warning( disable : 4996 )
#include "Game.h"
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
void Game::init(string filename)
{
	//����Log�ļ�//�ο�ȥ�����
	char buffer[1024];
	time_t t = time(0);
	strftime(buffer, sizeof(buffer), "log_%Y%m%d_%H%M%S.txt", localtime(&t));
	LogFile.open(buffer);
	
	data.gameMap.setData(&data);
	ifstream in(filename, ios_base::binary);
	if (!in)
		cerr << "can't open the map file" << endl;
	in >> _MAX_RESOURCE_ >> _MAX_ROUND_;
	if (data.gameMap.init(in, _MAX_RESOURCE_))
		cerr << "��ͼ��ʼ��ʧ�ܣ�";
	in.close();
	currentRound = 0;
	playerSize = playerAlive = data.players.size();
	
	//��ʼ������
	for (int i = 0; i != playerSize; ++i)
		Rank.push_back(i);
}

void Game::run()
{
	currentRound = 1;
	while (currentRound <= _MAX_ROUND_)
	{
		updateLog();
		Round();
		if (playerAlive == 1)
			break;
		currentRound++;
	}
	updateLog();
}

//����ѡ����Ϣ
vector<Info>* Game::generateInfo()
{
	vector<Info>* info = new vector<Info>;
	map <TCamp,PlayerInfo> playerInfo;   //������Ϣ
	map<TCamp,StudentInfo> studentInfo; //ͬѧ��Ϣ
	map<TTentacleID,TentacleInfo> tentacleInfo; //������Ϣ
	BaseMap* mapInfo;  //��ͼ��Ϣ

	//��ʼ����Ӫ
	for (int i = 0; i != data.players.size(); ++i)
	{
		PlayerInfo temp;
		Player* curr = &data.players[i];
		temp.alive = curr->isAlive();
		temp.DefenceLevel = curr->defenceLevel();
		temp.ExtendingSpeedLevel = curr->extendingSpeedLevel();
		temp.ExtraControlLevel = curr->extraControlLevel();
		temp.hackedLeftRound = curr->HackedLeftRound();
		temp.id = curr->ID();
		temp.maxControlNumber = curr->maxControlNumber();
		temp.department = curr->getDepartment();
		temp.rank = Rank[temp.id];
		temp.RegenerationSpeedLevel = curr->regenerationSpeedLevel();
		temp.skillLeftRound = curr->skillLeftRound();
		temp.studentIds.assign(curr->getStudents().cbegin(), curr->getStudents().cend());
		temp.technologyPoint = curr->techPoint();
		playerInfo.insert({ temp.id,temp });
	}

	//��ʼ��Stu
	for (int i = 0; i != data.students.size(); ++i)
	{
		StudentInfo temp;
		Student* curr = &data.students[i];
		temp.attackBy.assign(curr->attackedBy().cbegin(), curr->attackedBy().cend());
		temp.id = curr->ID();
		temp.resource = curr->getLeftLA();
		temp.occupyPoint = curr->getOccupyLA();
		temp.playerId = curr->getCampID();
		temp.position = curr->getPos();
		temp.tentacleIds.assign(curr->getTentacles().cbegin(), curr->getTentacles().cend());
		temp.type = curr->getStudentType();
		studentInfo.insert({ temp.id,temp });
	}

	//��ʼ��Tentacle
	for (int i = 0; i != data.tentacles.size(); ++i)
	{
		TentacleInfo temp;
		Tentacle* curr = &data.tentacles[i];
		if (curr->getStatus() == Finished)
			continue;
		temp.id = curr->ID();
		temp.backResource = curr->getBackResource();
		temp.enemyTentacle = curr->getEnemyTentacle();
		temp.frontResource = curr->getFrontResource();
		temp.length = curr->getLength();
		temp.resource = curr->getResource();
		temp.sourceStudent = curr->getSourceStudent();
		temp.targetStudent = curr->getTargetStudent();
		temp.status = curr->getStatus();
		tentacleInfo.insert({ temp.id,temp });
	}

	//��ʼ����ͼ������ָ��
	mapInfo = &data.gameMap;   
	
	for (int i = 0; i != playerSize; ++i)
	{
		Info _i = { playerSize, playerAlive, i, playerInfo[i].maxControlNumber, currentRound,
			CommandList(), playerInfo, studentInfo, tentacleInfo, mapInfo };
		info->push_back(_i);
	}

	return info;
}

void Game::Round()
{
	regeneratePhase();
	info = generateInfo();
	/*����player_ai(info[i])*/
	skillPhase();
	movePhase();
	transPhase();
	
}

void Game::skillPhase()
{
	for (int i = 0; i != playerSize; ++i)
	{
		for (Command& c : info->operator[](i).myCommandList)
		{
			//���������
			if (data.players[i].maxControlNumber() <= controlCount[i])
				break;
			//���Ǽ��ܵĲ���
			if (c.type == addTentacle || c.type == cutTentacle)
				continue;
			//����������
			controlCount[i]++;
			//����Ҳ���������
			if (data.players[i].HackedLeftRound())
				continue;
			//��������
			if (c.type == passiveSkill)
				if (c.parameters.size() == 1)
					data.players[i].upgrade(TPlayerPowerProperty(c.parameters[0]));
			//��������
			if (c.type == activeSkill)
				switch (data.players[i].getDepartment())
				{
				case Aeronautics:          //��������
					if (c.parameters.size() != 3 || data.players[i].techPoint() < 5)
						continue;
					if (data.students[i].getLeftLA() < c.parameters[2] || c.parameters[2] > 30
						|| data.students[c.parameters[0]].getCampID() != i || data.students[c.parameters[1]].getCampID() != i)
						continue;
					//����ʹ�ü���
					data.players[i].reduceTech(5);
					data.students[c.parameters[0]].setResource(data.students[c.parameters[0]].getLeftLA() - c.parameters[2]);
					data.students[c.parameters[1]].setResource(data.students[c.parameters[1]].getLeftLA() + c.parameters[2]);
					break;
				case Medical:             //��ҩ
					if (c.parameters.size() != 0 || data.players[i].techPoint() < 10)
						continue;
					data.players[i].reduceTech(10);
					data.players[i].setSkillLeftRound(5);
					break;
				case Energy:             //����
					if (c.parameters.size() != 1 || data.players[i].techPoint() < 5
						|| data.students[c.parameters[0]].getCampID() != i)
						continue;
					data.players[i].reduceTech(5);
					data.students[c.parameters[0]].setResource(data.students[c.parameters[0]].getLeftLA() + 20);
					break;
				case Electronic:         //Wifi
					if (c.parameters.size() != 0 || data.players[i].techPoint() < 10)
						continue;
					data.players[i].reduceTech(10);
					data.players[i].setSkillLeftRound(10);
					break;
				case Economy:            //Money
					if (c.parameters.size() != 0 || data.players[i].techPoint() < 10)
						continue;
					data.players[i].reduceTech(10);
					data.players[i].setSkillLeftRound(5);
					data.players[i].setMaxControl(100000);//�ܴ󲻿��ܴﵽ/Ӧ��
					break;
				case Computer:        //hacker
					if (c.parameters.size() != 1 || data.players[i].techPoint() < 15)
						continue;
					if (c.parameters[0] < 0 || c.parameters[0] >= playerSize)
						continue;
					data.players[i].reduceTech(15);
					data.players[c.parameters[0]].setHackedRound(8);  //8���غϰ�...��Ȼ̫Imba��
					break;
				case Automation:      //feedback
					if (c.parameters.size() != 1 || data.players[i].techPoint() < 15)
						continue;
					if (c.parameters[0] < 0 || c.parameters[0] >= data.tentacles.size()
						|| data.tentacles[c.parameters[0]].getStatus() == AfterCut
						|| data.tentacles[c.parameters[0]].getStatus() == Finished)
						continue;
					//ֱ�Ӵ��
					if (TResourceD over = data.tentacles[c.parameters[0]].getResource() / 2
						- data.students[data.tentacles[c.parameters[0]].getSourceStudent()].getLeftLA() > 0)
					{
						data.students[data.tentacles[c.parameters[0]].getSourceStudent()].changeOwnerTo(i);
						data.students[data.tentacles[c.parameters[0]].getSourceStudent()].setResource(10 + over);
					}
					else
						data.students[data.tentacles[c.parameters[0]].getSourceStudent()].setResource(-over);
					break;
				case Environment:             //lowWaste
					if (c.parameters.size() != 0 || data.players[i].techPoint() < 10)
						continue;
					data.players[i].reduceTech(10);
					data.players[i].setSkillLeftRound(10);
					break;
				default:
					break;
				}
		}
	}
}

void Game::regeneratePhase()
{
	//�ظ��Ƽ�����
	for (auto& p:data.players)
	{
		if (p.second.isAlive())
			p.second.addTechPoint();
	}
	//ÿ��ϸ���ظ���Դ
	for (auto& p:data.students)
	{
		Student& s = p.second;
		TPower extraPower = 1.0;
		if (s.getCampID() != Neutral) {
			s.addLA();
		}
	}
}

void Game::movePhase()
{
	for (auto &p : data.tentacles)
	{
		Tentacle& t = p.second;
		TransEffect te = t.move();
		data.students[t.getSourceStudent()].setResource(data.students[t.getSourceStudent()].getLeftLA() + te.m_resourceToSource);
	}
}

void Game::transPhase()
{
	vector<TransEffect> Effects;     //���洫����Ϣ�����ڽ���
	for (auto& p:data.tentacles)
	{
		Tentacle& t = p.second;
		if(t.getStatus()!=Finished)
			Effects.push_back(t.transport());
	}
	TResourceD* totalEffect = new TResourceD[data.students.size()];
	for (TransEffect& e : Effects)
	{
		totalEffect[e.m_sourceStudent] += e.m_resourceToSource;
		totalEffect[e.m_targetStudent] += e.m_resourceToTarget;
	}
	for (auto& p:data.students)
	{
		Student& s = p.second;
		if (s.getCampID() != Neutral)
		{
			//δ����0����
			if (TResourceD left = s.getLeftLA() - totalEffect[s.ID()] > 0)
				s.setResource(left);
			//�Ѿ�����0����
			else
			{
				//���¼���te����ΪAttackBy�еĿ����Ѿ���ɴ��������
				vector<TCamp> priority[3];
				for (TransEffect& e : Effects)
				{
					if (e.m_targetStudent == s.ID())
					{
						switch (e.m_currStatus)
						{
						case Extending:
							break;
						case Attacking:
						case Backing:
						case Confrontation:
							priority[2].push_back(e.m_sourceStudent);
						case Arrived:
							priority[1].push_back(e.m_sourceStudent);
							break;
						case AfterCut:
							priority[0].push_back(e.m_sourceStudent);
							break;
						case Finished:
							break;
						default:
							break;
						}
					}
				}
				for (int i = 0; i != 3; ++i)
				{
					//�����ǰ���ȼ�����
					if (!priority[i].empty())
					{
						//�洢��ǰ���ȼ��е���Ӫ
						set<TCamp> camps;
						for (TTentacleID id : priority[i])
							camps.insert(data.students[i].getCampID());
						//�����ǰ���ȼ�ֻ��1����Ӫ
						if (camps.size() == 1)
							s.changeOwnerTo(*camps.begin());
						else
							s.changeOwnerTo(Neutral);
					}
				}
			}
		}
		else      //��Ӧ����ϸ��
			for (TransEffect& e : Effects)
			{
				if (e.m_targetStudent == s.ID())
					s.N_addOcuppyPoint(data.students[e.m_sourceStudent].getCampID(), e.m_resourceToTarget);
			}
	}
}

void Game::subRoundPhase()
{
	for (std::pair<const TCamp,Player>& p:data.players)
	{
		if (p.second.skillLeftRound() != 0)
		{
			p.second.setSkillLeftRound(p.second.skillLeftRound() - 1);
			/*��Щ���ĸı�
			if (p.second.skillLeftRound() == 0)
			{
			
			}
			*/
		}
		if (p.second.HackedLeftRound() != 0)
			p.second.setHackedRound(p.second.HackedLeftRound() - 1);
		
		//��[�����о���]����������
		if (p.second.skillLeftRound() == 0 || p.second.getDepartment() == Economy)
			p.second.updateMaxControl();
	}
}

void Game::killPlayer(TCamp id)
{
	data.players[id].Kill();
	playerAlive--;
}

void Game::updateLog()
{
	//��LogFile�д�����Ϣ
}