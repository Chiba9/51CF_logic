#include "game.h"
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
bool Game::init(string filename)
{
	//����Log�ļ�//�ο�ȥ�����
	char buffer[1024];
	time_t t = time(0);
	strftime(buffer, sizeof(buffer), "log_%Y%m%d_%H%M%S.txt", localtime(&t));
	LogFile.open(buffer);

	data.gameMap.setData(&data);
	ifstream in(filename);
	if (!in)
	{
		cerr << "can't open the map file" << endl;
		return false;
	}
	in >> _MAX_RESOURCE_ >> _MAX_ROUND_;
	if (!data.gameMap.init(in, _MAX_RESOURCE_, true))
	{
		cerr << "Something wrong when init the map infomation."<<endl;
		return false;
	}
	in.close();
	currentRound = 0;
	playerSize = playerAlive = data.PlayerNum;

	data.tentacles = new Tentacle**[data.CellNum];
	for (int i = 0; i != data.CellNum; ++i)
	{
		data.tentacles[i] = new Tentacle*[data.CellNum];
		for (int j = 0; j != data.CellNum; ++j)
			data.tentacles[i][j] = nullptr;
	}
	//��ʼ������
	for (int i = 0; i != playerSize; ++i)
		Rank.push_back(i);

	//��ʼ������
	for (int i = 0; i != playerSize; ++i)
		controlCount.push_back(0);
	return true;
}

void Game::DebugPhase()
{
	cout << "/*************** DEBUG ��Ϣ ***************/" << endl;
	cout << "Round " << currentRound << endl;
	cout << "���ʣ�ࣺ " << playerAlive << " / " << playerSize << endl;
	for (int i = 0; i != data.PlayerNum; ++i)
	{
		cout << "��� " << i << " �� " <<" ����Դ���� "<< data.players[i].totalResource() << " �Ƽ������� " << data.players[i].techPoint() << " ���ܵȼ��� "
			<< " �ظ� " << data.players[i].getRegenerationLevel() << " �ƶ� " << data.players[i].getMoveLevel()
			<< " ���� " << data.players[i].getExtraControlLevel() << " ���� " << data.players[i].getDefenceLevel() 
			<< " ��������" << data.players[i].maxControlNumber() << endl;
		cout << "����ϸ����";
		for (TCellID u : data.players[i].cells())
			cout << u <<" ";
		cout << endl;
		cout << "������ " << std::find(Rank.begin(),Rank.end(),i) - Rank.begin() + 1;
		cout << endl;
	}
	cout << endl;
	char stg[4] = { 'N','A','D','G' };
	for (int i = 0; i != data.CellNum; ++i)
	{
		cout << "ϸ�� " << i << " �� " << "������ " << data.cells[i].getPlayerID()
			<< " ��Դ�� " << data.cells[i].getResource() << " ����Դ�� " << data.cells[i].totalResource()
			<< " ���ԣ� " <<stg[data.cells[i].getStg()]
			<< " ���ڹ����� ";
		for (int j = 0; j != data.CellNum; ++j)
		{
			if (data.tentacles[i][j])
				cout << j << " ";
		}
		cout << endl;
		if (data.cells[i].getPlayerID() == Neutral)
			cout << "����ϸ�����ԣ�" << "ռ�������� " << data.cells[i].getOccupyOwner() << " ռ��㣺 " << data.cells[i].getOccupyPoint() <<endl;
	}
	cout << "������Ϣ��" <<endl;
	for (int i = 0; i != data.CellNum; ++i)
	{
		for (int j = 0; j != data.CellNum; ++j)
			if (data.tentacles[i][j])
				cout << 1;
			else
				cout << 0;
		cout << endl;
	}
	cout << endl;
	vector<string> n2str{ "Extending","Attacking","Backing","Confrontation","Arrived","AfterCut" };
	for (int i = 0; i != data.CellNum; ++i)
		for (int j = 0; j != data.CellNum; ++j)
			if (data.tentacles[i][j])
			{
				cout << "���� " << i << " -> " << j << " : "
					<< " ״̬�� " << n2str[data.tentacles[i][j]->getstate()];
				if (data.tentacles[i][j]->getstate() == AfterCut)
					cout << " ǰ����Դ�� " << data.tentacles[i][j]->getFrontResource()
					<< "����Դ�� " << data.tentacles[i][j]->getBackResource();
				else
					cout << " ��Դ�� " << data.tentacles[i][j]->getResource();
				cout << endl;
			}
	cout << "\n\n";
}

//����ѡ����Ϣ
vector<Info> Game::generateInfo()
{
	vector<Info> info;
	//PlayerInfo playerInfo;   //������Ϣ
	//CellInfo cellInfo; //ͬѧ��Ϣ
	//TentacleInfo tentacleInfo; //������Ϣ
	BaseMap* mapInfo;  //��ͼ��Ϣ
	//��ʼ��������Ϣ
	for (int i = 0; i != data.PlayerNum; ++i)
	{
		Info I;
		I.playerSize = data.PlayerNum;
		int alive = 0;
		for (int j = 0; j != data.PlayerNum; ++j)
		{
			if (data.players[j].isAlive())
				alive++;
		}
		I.playerAlive = alive;
		I.myID = i;
		I.cellNum = data.CellNum;
		I.round = currentRound;
		I.myMaxControl = data.players[i].maxControlNumber();
		I.mapInfo = &data.gameMap;
		info.push_back(I);
	}
	//��ʼ����Ӫ
	for (int i = 0; i != data.PlayerNum; ++i)
	{
		PlayerInfo temp;
		Player* curr = &data.players[i];
		temp.alive = curr->isAlive();
		temp.DefenceLevel = curr->getDefenceLevel();
		temp.ExtendingSpeedLevel = curr->getMoveLevel();
		temp.ExtraControlLevel = curr->getExtraControlLevel();
		temp.id = i;
		temp.maxControlNumber = curr->maxControlNumber();
		temp.rank = Rank[i];
		temp.RegenerationSpeedLevel = curr->getRegenerationLevel();
		temp.technologyPoint = curr->techPoint();
		temp.cells = curr->cells();
		for (int j = 0; j != data.PlayerNum; ++j)
		{
			info[j].playerInfo.push_back(temp);
		}
	}

	//��ʼ��ϸ����Ϣ
	for (int i = 0; i != data.CellNum; ++i)
	{
		CellInfo temp;
		Cell* curr = &data.cells[i];
		temp.id = i;
		temp.occupyPoint = curr->getOccupyPoint();
		temp.occupyOwner = curr->getOccupyOwner();
		temp.owner = curr->getPlayerID();
		temp.position = curr->getPos();
		temp.resource = curr->getResource();
		temp.strategy = curr->getStg();
		temp.type = curr->getCellType();
		for (int j = 0; j != data.PlayerNum; ++j)
		{
			info[j].cellInfo.push_back(temp);
		}
	}

	//��ʼ��Tentacle
	vector<TentacleInfo> templist;
	for (int k = 0; k != data.PlayerNum; ++k)
		for (int j = 0; j != data.CellNum; ++j)
	{
		info[k].tentacleInfo.push_back(templist);
	}

	for (int i = 0; i != data.CellNum; ++i)
		for(int j = 0;j!=data.CellNum;++j)
	{
		TentacleInfo temp;
		Tentacle* curr = data.tentacles[i][j];
		if (!curr)
		{
			temp.exist = false;
			for (int k = 0; k != data.PlayerNum; ++k)
			{
				info[k].tentacleInfo[i].push_back(temp);
			}
			continue;
		}
		temp.backResource = curr->getBackResource();
		temp.exist = true;
		temp.frontResource = curr->getFrontResource();
		temp.maxlength = curr->getLength();
		temp.resource = curr->getResource();
		temp.sourceCell = curr->getSourceCell();
		temp.state = curr->getstate();
		temp.targetCell = curr->getTargetCell();
		for (int k = 0; k != data.PlayerNum; ++k)
		{
			info[k].tentacleInfo[i].push_back(temp);
		}
	}

	//��ʼ����ͼ������ָ��
	mapInfo = &data.gameMap;

	return info;
}

bool Game::isValid()
{
	if (playerAlive == 1 || currentRound >= _MAX_ROUND_)
		return false;
	else
		return true;
}

void Game::takeEffect(TransEffect& te)
{
	Tentacle& t = *data.tentacles[te.m_source][te.m_target];
	t.takeEffect(te);
	data.cells[te.m_source].addResource(te.m_resourceToSource);
	if(abs(te.m_resourceToTarget) > 0.0001)//��Ч
		if (data.cells[te.m_target].getPlayerID() != Neutral)
			data.cells[te.m_target].addResource(te.m_resourceToTarget);
		else//Ŀ��Ϊ����
			data.cells[te.m_target].N_addOcuppyPoint(data.cells[te.m_source].getPlayerID(), -te.m_resourceToTarget);
	te.handle = false;
	cout << te.m_source << " -> " << te.m_target;
	switch (te.m_type)
	{
	case moveE:
		cout << " �ƶ��� ";
		break;
	case transE:
		cout << " ���䣺 ";
		break;
	default:
		break;
	}
	cout << " ��Դϸ�� " << te.m_source << " : " << te.m_resourceToSource
		<< " ��Ŀ��ϸ�� " << te.m_target << " : " << te.m_resourceToTarget
		<< " ����ı䣺" << te.m_resourceChange << "/" << te.m_frontChange << "/" << te.m_backChange << endl;
}

void Game::regeneratePhase()
{
	/*//�ظ��Ƽ�����
	for (int i = 0;i!=data.PlayerNum;++i)
	{
		Player& p = data.players[i];
		if (p.isAlive())
			p.regenerateTechPoint();
	}*/
	//ÿ��ϸ���ظ���Դ//ͬʱ�ظ������Ƽ�����
	for (int i = 0;i!=data.CellNum;++i)
	{
		if (data.cells[i].getPlayerID() != Neutral) {
			data.cells[i].regenerate();
		}
	}
}

void Game::movePhase()
{
	TransEffect** TE = new TransEffect*[data.CellNum];
	//�õ�TE��
	for (int i = 0; i != data.CellNum; ++i)
	{
		TE[i] = new TransEffect[data.CellNum];
		for (int j = 0; j != data.CellNum; ++j)
		{
			if (!data.tentacles[i][j])
				continue;
			TE[i][j] = data.tentacles[i][j]->move();
		}
	}
	//����TE��
	for (int i = 0; i != data.CellNum; ++i)
	{
		for (int j = 0; j != data.CellNum; ++j)
		{
			if (TE[i][j].handle)
			{
				if (TE[j][i].handle)//����Ҳ�д���
				{
					if (data.tentacles[i][j]->getstate() == Extending
						&& data.tentacles[j][i]->getstate() == Extending)//����������
					{
						if (data.tentacles[i][j]->getResource() + data.tentacles[j][i]->getResource()
							+ TE[i][j].m_resourceChange + TE[j][i].m_resourceChange <= data.tentacles[i][j]->getLength() / 10)//��δ����
						{
							takeEffect(TE[i][j]); takeEffect(TE[j][i]);
						}
						else//�����м�
						{
							TResourceD distance = data.tentacles[i][j]->getLength() * Density - (data.tentacles[i][j]->getResource() + data.tentacles[j][i]->getResource());
							TE[i][j].m_resourceChange = TE[j][i].m_resourceChange = distance / 2;
							TE[i][j].m_resourceToSource = TE[j][i].m_resourceToSource = -distance / 2;
							//�ж�����
							if (data.tentacles[i][j]->getResource() + distance / 2 > data.tentacles[i][j]->getLength() *Density / 2)//Խ��һ��
							{
								data.tentacles[i][j]->setstate(Attacking);
								data.tentacles[j][i]->setstate(Backing);
							}
							else
							{
								data.tentacles[j][i]->setstate(Attacking);
								data.tentacles[i][j]->setstate(Backing);
							}
							takeEffect(TE[i][j]); takeEffect(TE[j][i]);
						}
					}
					else if (data.tentacles[i][j]->getstate() == Extending
						&& data.tentacles[j][i]->getstate() == AfterCut)
					{
						takeEffect(TE[j][i]);
						handleExtending(TE[i][j]);
					}
					else if (data.tentacles[i][j]->getstate() == Attacking
						&& data.tentacles[j][i]->getstate() == Backing)
					{
						if (data.tentacles[i][j]->getResource() + TE[i][j].m_resourceChange > data.tentacles[i][j]->getLength()*Density / 2) //�����Ƶ��е�
						{
							TResourceD distance = data.tentacles[i][j]->getLength() *Density / 2 - data.tentacles[i][j]->getResource();//���е�ľ���
							TE[i][j].m_resourceChange = TE[j][i].m_resourceToSource = distance;
							TE[i][j].m_resourceToSource = TE[j][i].m_resourceChange = -distance;
							data.tentacles[j][i]->setstate(Confrontation);
							data.tentacles[i][j]->setstate(Confrontation);
							takeEffect(TE[i][j]); takeEffect(TE[j][i]);
						}
						else//˳����Ȼ
						{
							takeEffect(TE[i][j]); takeEffect(TE[j][i]);
						}
					}
					else if (data.tentacles[i][j]->getstate() == Backing
						&& data.tentacles[j][i]->getstate() == Attacking)//�������෴
					{
						if (data.tentacles[j][i]->getResource() + TE[j][i].m_resourceChange > data.tentacles[j][i]->getLength()*Density / 2) //�����Ƶ��е�
						{
							TResourceD distance = data.tentacles[j][i]->getLength() *Density / 2 - data.tentacles[j][i]->getResource();//���е�ľ���
							TE[j][i].m_resourceChange = TE[i][j].m_resourceToSource = distance;
							TE[j][i].m_resourceToSource = TE[i][j].m_resourceChange = -distance;
							data.tentacles[i][j]->setstate(Confrontation);
							data.tentacles[j][i]->setstate(Confrontation);
							takeEffect(TE[j][i]); takeEffect(TE[i][j]);
						}
						else//˳����Ȼ
						{
							takeEffect(TE[j][i]); takeEffect(TE[i][j]);
						}
					}
					else if (data.tentacles[i][j]->getstate() == Confrontation
						&& data.tentacles[j][i]->getstate() == Confrontation)
					{
						takeEffect(TE[i][j]); takeEffect(TE[j][i]);
					}
					else if (data.tentacles[i][j]->getstate() == AfterCut
						&& data.tentacles[j][i]->getstate() == Extending)
					{
						takeEffect(TE[i][j]);
						handleExtending(TE[j][i]);
					}
				}
				else
				{
					switch (data.tentacles[i][j]->getstate())
					{
					case Extending:
						handleExtending(TE[i][j]);
						break;
					case Arrived:
						takeEffect(TE[i][j]);
						break;
					case AfterCut:
						takeEffect(TE[i][j]);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	//���Ƿ��������ת��
	OwnerChange(TE);
	for (int i = 0; i != data.CellNum; ++i)
		delete[] TE[i];
	delete[] TE;
}

void Game::transPhase()
{
	TransEffect** TE = new TransEffect*[data.CellNum];
	//�õ�TE��
	for (int i = 0; i != data.CellNum; ++i)
	{
		TE[i] = new TransEffect[data.CellNum];
		for (int j = 0; j != data.CellNum; ++j)
		{
			if (!data.tentacles[i][j])
				continue;
			TE[i][j] = data.tentacles[i][j]->transport();
		}
	}
	for (int i = 0; i != data.CellNum; ++i)
		for (int j = 0; j != data.CellNum; ++j)
			if (data.tentacles[i][j])
				takeEffect(TE[i][j]);
	OwnerChange(TE);
	for (int i = 0; i != data.CellNum; ++i)
		delete[] TE[i];
	delete[] TE;
}

void Game::beginPhase()
{

}

void Game::endPhase()
{
	for (int i = 0;i!=data.CellNum;++i)
		for (int j = 0; j != data.CellNum; ++j)
		{
			if (data.tentacles[i][j]
				&& data.tentacles[i][j]->getstate() == AfterCut
				&& data.tentacles[i][j]->getFrontResource() <= 0.0001
				&& data.tentacles[i][j]->getBackResource() <= 0.0001)//ʵ���Ѿ�û��
			{
				delete data.tentacles[i][j];
				data.tentacles[i][j] = nullptr;
				data.TentacleNum--;
			}
		}

	for (int i = 0; i != data.PlayerNum; ++i)
	{
		if (data.players[i].isAlive() && data.players[i].cells().empty())
			killPlayer(i);
	}
	//����ϸ����Ϣ
	for (int i = 0; i != data.CellNum; ++i)
	{
		data.cells[i].updateProperty();
	}
	//������Ϣ
	vector<std::pair<TPlayerID, TResourceD> > playerpair;
	for (int i = 0;i!=data.PlayerNum;++i)
	{
		if (data.players[i].isAlive())
			playerpair.push_back({ i,data.players[i].totalResource() });
	}
	std::sort(playerpair.begin(), playerpair.end(),
		[](const std::pair<TPlayerID, TResourceD>& a, std::pair<TPlayerID, TResourceD>& b) {return a.second > b.second; });
	int i = 0;
	for (auto &p : playerpair)
	{
		Rank[i++] = p.first;
	}
}

void Game::commandPhase(vector<CommandList>& command_list)
{
	for (int i = 0; i != playerSize; ++i)
	{
		controlCount[i] = 0;
		for (Command& c : command_list[i])
		{
			//���������
			if (data.players[i].maxControlNumber() <= controlCount[i])
				break;
			switch (c.type)
			{
			case addTentacle: 
			{
				if (c.parameters.size() < 2)break;
				TCellID source = c.parameters[0];
				TCellID target = c.parameters[1];
				if (data.cells[source].getPlayerID() == i)
					data.cells[source].addTentacle(target);
			}
			break;
			case cutTentacle:
			{
				if (c.parameters.size() < 3)break;
				TCellID source = c.parameters[0];
				TCellID target = c.parameters[1];
				TPosition pos = c.parameters[2];
				if (data.cells[source].getPlayerID() == i)
					data.cells[source].cutTentacle(target, pos);
			}
			break;
			case changeStrategy:
			{
				if (c.parameters.size() < 1)break;
				TCellID cell = c.parameters[0];
				CellStrategy nextStg = static_cast<CellStrategy>(c.parameters[1]);
				if (data.cells[cell].getPlayerID() == i)
					data.cells[cell].changeStg(nextStg);
			}
			break;
			case upgrade:
			{
				if (c.parameters.size() < 1)break;
				TPlayerProperty upgradeType = static_cast<TPlayerProperty>(c.parameters[0]);
				data.players[i].upgrade(upgradeType);
			}
			break;
			default:
				break;
			}
			controlCount[i]++;
		}
		
	}
}

void Game::killPlayer(TPlayerID id)
{
	data.players[id].Kill();
	playerAlive--;
}


void Game::handleExtending(TransEffect& te)
{
	//������ͨ���Ĵ���Extend�ķ���
	int i = te.m_source;
	int j = te.m_target;
	if (data.tentacles[i][j]->getResource() + te.m_resourceChange > data.tentacles[i][j]->getLength()*Density)//�����ִ�
	{
		TResourceD distance = data.tentacles[i][j]->getLength() *Density - data.tentacles[i][j]->getResource();//��Ŀ��ľ���
		te.m_resourceChange = distance;
		te.m_resourceToSource = -distance;
		data.tentacles[i][j]->setstate(Arrived);
		takeEffect(te);
	}
	else
		takeEffect(te);
}

void Game::OwnerChange(TransEffect** TE)
{
	for (int i = 0; i != data.CellNum; ++i)
	{
		if (data.cells[i].getResource()!=Neutral && data.cells[i].getResource() <= 0 )
		{
			set<TPlayerID> Cuter, Arriver, Confrontationer;//��Ӧ�жϡ�ѹ�ơ��������ֹ������ȵȼ�
			for (int j = 0; j != data.CellNum; ++j)
			{
				if (data.tentacles[j][i]
					&& data.cells[j].getPlayerID() != data.cells[i].getPlayerID())
				{
					switch (TE[j][i].m_currstate)
					{
					case AfterCut:
						if(TE[j][i].m_resourceToTarget <= -0.01) //ȷʵ�����Ч�������жϴ���
							Cuter.insert(TE[j][i].m_currOwner);
						break;
					case Arrived:
						Arriver.insert(TE[j][i].m_currOwner);
						break;
					case Attacking:
					case Backing:
					case Confrontation:
						Confrontationer.insert(TE[j][i].m_currOwner);
						break;
					default:
						break;
					}
				}
			}
			//���ݹ����ȼ��ж�����
			if (!Cuter.empty())
				if (Cuter.size() == 1)
					data.cells[i].changeOwnerTo(*Cuter.begin());
				else
					data.cells[i].changeOwnerTo(Neutral);
			else if (!Arriver.empty())
				if (Arriver.size() == 1)
					data.cells[i].changeOwnerTo(*Arriver.begin());
				else
					data.cells[i].changeOwnerTo(Neutral);
			else if(!Confrontationer.empty())
				if (Confrontationer.size() == 1)
					data.cells[i].changeOwnerTo(*Confrontationer.begin());
				else
					data.cells[i].changeOwnerTo(Neutral);
			else//û�����ڽ���,ֱ���ж���������
				for (int j = 0; j != data.CellNum; ++j)
					data.cells[i].cutTentacle(j, 1000000/*һ���ܴ����*/);
		}
		else if (data.cells[i].getPlayerID() == Neutral && data.cells[i].getOccupyPoint() > data.cells[i].getResource() / 3)//�����ı�
		{
			data.cells[i].changeOwnerTo(data.cells[i].getOccupyOwner());
		}
	}


}

void sample_ai(Info& info)
{
	vector<int> para;
	int temp;
	cout << "Player " << info.myID << " �����������" << endl;
	while (1)
	{
		para.clear();
		cout << "�Ƿ�����ָ�(�������� 0)" << endl;
		cin >> temp;
		if (temp == 0)
			break;
		cout << "�����룺����(0)������(1)�����(2)���ж�(3)���� -1 ����\n";
		cin.clear();	
		cin.sync();	
		while (cin >> temp)
		{
			if (temp == -1)break;
			para.push_back(temp);
		}
		CommandType t = CommandType(para[0]);
		para.erase(para.begin());
		info.myCommandList.addCommand(t, para);
	}
}