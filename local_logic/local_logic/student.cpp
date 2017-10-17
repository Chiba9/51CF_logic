#include"student.h"
#include "data.h"
#include "tentacle.h"
#include <algorithm>

using namespace DATA;
Student::~Student()
{}

Student::Student(DATA::Data* _data, TPoint pos, TCamp campid, TResourceD resource, TResourceD maxResource, bool special, TSpeed techPoint)
	:m_campID(campid),m_resource(resource),m_position(pos),data(_data)
{
	updateProperty(special);
	if(campid == Neutral)    //����ͬѧ
		m_occupyPoint = 0.0;

	//����ͬѧ��������
	if (special)
		m_property.m_techSpeed = techPoint;
	m_property.m_maxResource = maxResource;

	//���뵽Data��
	data->students.push_back(*this);

	//��ʼ������ʽ����
	/*  
	id = ;
	m_camp = ;
	m_leftLA = ;
	m_position = ;
	m_occupyLA = ;
	m_preTentacle.clear();
	m_attackedBy.clear();
	*/
}

TResourceD Student::totalResource()
{
	TResourceD total = m_resource;
	for (TTentacleID id : m_preTentacle)
		total += data->tentacles[id].totalResource();
	return total;
}

void Student::addLA()
{
	int level = data->players[m_campID].regenerationSpeedLevel();
	double extraPower = 1.0;
	//��������
	if (data->players[m_campID].HackedLeftRound() > 0)
		extraPower /= 2;
	if (data->players[m_campID].skillLeftRound > 0
		&& data->players[m_campID].getDepartment() == Medical)
		extraPower *= 2;
	m_resource += RegenerationSpeedStage[level] * m_property.m_regenarationSpeed * extraPower;
}

bool Student::addTentacle(const TStudentID& _id)
{
	//��������
	if (m_preTentacle.size() == m_property.m_maxTentacleNum)
	{
		cout << "the tentacle can't be more!";
		return false;
	}

	Tentacle newTentacle(ID(), _id, data);
	m_preTentacle.push_back(newTentacle.ID());
	data->tentacles.push_back(newTentacle);
	return true;
}

bool Student::cutTentacle(TId _id, TPosition pos)
{
	//��鴥���Ƿ���Ч
	auto ans = find(m_preTentacle.cbegin(), m_preTentacle.cend(), _id);
	if (ans != m_preTentacle.cend())
		return false;
	
	//�����жϴ���
	data->tentacles[*ans].cut(pos);
	return true;
}

void Student::updateProperty(bool special /*= false*/)
{
	//���ҵȼ�
	int stage = 0;
	for (; stage != STUDENT_LEVEL_COUNT; ++stage)
		if (STUDENT_STAGE[stage] <= m_resource < STUDENT_STAGE[stage + 1])
			break;

	m_studentType = StudentType(stage);
	
	m_property.m_maxTentacleNum = TENTACLE_NUMBER[stage];
	m_property.m_regenarationSpeed = BASE_REGENERETION_SPEED[stage];
	m_property.m_special = special;

	//ͨ��ϸ���ƴ�ֵΪѧϰ����/10
	if (!special)
		m_property.m_techSpeed = m_property.m_regenarationSpeed / 10.0;
}

void Student::changeOwnerTo(TCamp newOwner)
{
	if (newOwner < -1 || newOwner >= data->players.size())
		return;
	//��ֹ֮ǰ��������ռ��ֵ����
	m_occupyPoint = 0;

	m_resource = 10;
	for (TTentacleID t : m_preTentacle)
	{
		if (data->tentacles[t].getStatus() != AfterCut)
			cutTentacle(t, data->tentacles[t].getResource());
	}
	data->players[m_campID].removeStudent(ID());
	//�ж��Ƿ�����
	if (data->players[m_campID].getStudentNumber() == 0)
		data->players[m_campID].Kill();
	//��������
	if (newOwner != Neutral)
		data->players[newOwner].addStudent(ID());
}

void Student::N_addOcuppyPoint(TCamp owner, TResourceD point)
{
	if (m_occupyOwner != owner)
		if (m_occupyPoint < point)
		{
			m_occupyPoint = point - m_occupyPoint;
			m_occupyOwner = owner;
		}
		else
			m_occupyPoint -= point;
	else
		m_occupyPoint += point;
}
