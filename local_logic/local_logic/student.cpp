#include"student.h"
#include "data.h"
#include "tentacle.h"
#include <algorithm>

using namespace DATA;
Student::~Student()
{}

Student::Student(DATA::Data* _data,TPoint pos, TCamp campid, TResourceD resource, bool special, TSpeed techPoint)
	:m_campID(campid),m_resource(resource),m_position(pos),data(_data)
{
	updateProperty(special);
	if(campid == Neutral)    //中立同学
		m_occupyPoint = 0.0;

	//特殊同学额外设置
	if (special)
		m_property.m_techSpeed = techPoint;

	//加入到Data中
	data->students.push_back(*this);

	//初始化的形式待定
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

void Student::addLA()
{
	int level = data->players[m_campID].regenerationSpeedLevel();
	double extraPower = 1.0;
	//技能特判
	if (data->players[m_campID].isHacked())
		extraPower /= 2;
	if (data->players[m_campID].skillLeftRound > 0
		&& data->players[m_campID].getDepartment() == Medical)
		extraPower *= 2;
	m_resource += RegenerationSpeedStage[level] * m_property.m_regenarationSpeed * extraPower;
}

bool Student::addTentacle(const TStudentID& _id)
{
	//触手数量
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
	//检查触手是否有效
	auto ans = find(m_preTentacle.cbegin(), m_preTentacle.cend(), _id);
	if (ans != m_preTentacle.cend())
		return false;
	
	//否则切断触手
	data->tentacles[*ans].cut();
	m_preTentacle.erase(ans);
	return true;
}

void Student::updateProperty(bool special /*= false*/)
{
	//查找等级
	int stage = 0;
	for (; stage != STUDENT_LEVEL_COUNT; ++stage)
		if (STUDENT_STAGE[stage] <= m_resource < STUDENT_STAGE[stage + 1])
			break;

	m_studentType = StudentType(stage);
	
	m_property.m_maxTentacleNum = TENTACLE_NUMBER[stage];
	m_property.m_regenarationSpeed = BASE_REGENERETION_SPEED[stage];
	m_property.m_special = special;

	//通常细胞科创值为学习能力/10
	if (!special)
		m_property.m_techSpeed = m_property.m_regenarationSpeed / 10.0;
}