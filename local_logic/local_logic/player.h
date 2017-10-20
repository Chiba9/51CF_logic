#ifndef PLAYER_H
#define PLAYER_H

#include "definition.h"
#include "object.h"
#include <vector>
#include <set>
namespace DATA
{
	struct Data;
}

class Student;

class Player :public Object<Player>
{
private:
	std::set<TId> m_students;         //����ͬѧ
	TDepartment m_department;            //Ժϵ����
	TResourceD m_technologyPoint = 0.0;        //�Ƽ�����

	TLevel m_RegenerationSpeedLevel = 0;      //�������ʵȼ�
	TLevel m_ExtendingSpeedLevel = 0;      //�����ٶȵȼ�
	TLevel m_ExtraControlLevel = 0;        //����������ȼ�
	TLevel m_DefenceLevel = 0;       //�����ȼ�

	TRound m_skillLeftRound = 0;       //ʣ���������ܻغ�
	std::size_t m_maxControlNumber;    //��������

	DATA::Data* const  data;

	TRound m_hackedLeftRound = 0;                //�Ƿ񱻺�
	bool m_alive = true;                  //�Ƿ񻹻���

	//�������ֱ������ԣ������Ƿ�ɹ�
	bool _upgradeRegeneration();
	bool _upgradeExtending();
	bool _upgradeExtraControl();
	bool _upgradeDefence();

public:
	Player():Object(NO_DATA),data(nullptr){}
	Player(DATA::Data* _data, TDepartment _department, std::set<TId> _stu);

	void addStudent(TStudentID student);             //����ͬѧ
	void removeStudent(TStudentID student);          //����ͬѧ
	void setHacked(TRound HachRound);
	bool upgrade(TPlayerPowerProperty property);    //����    
	void addTechPoint();                      //���ݵ�ǰϸ�����ӿƼ�����
	void Kill();                              //ɱ�������
	void reduceTech(TResourceD minus) { m_technologyPoint -= minus; }
	void updateMaxControl() { m_maxControlNumber = m_students.size() / 2 + 1; }

	//�õ�������

	TRound HackedLeftRound() { return m_hackedLeftRound; }
	bool isAlive() { return m_alive; }
	TResourceD techPoint() { return m_technologyPoint; }
	std::set<TId> getStudents() { return m_students; }
	std::size_t getStudentNumber() { return m_students.size(); }
	std::size_t maxControlNumber() { return m_maxControlNumber;}
	TDepartment getDepartment() { return m_department; }
	TLevel regenerationSpeedLevel() { return m_RegenerationSpeedLevel; }
	TLevel extendingSpeedLevel() { return m_ExtendingSpeedLevel; }
	TLevel extraControlLevel() { return m_ExtraControlLevel; }
	TLevel defenceLevel() { return m_DefenceLevel; }
	void   setSkillLeftRound(TRound round) { m_skillLeftRound = round; }
	void   setMaxControl(int max) { m_maxControlNumber = max; }
	void   setHackedRound(TRound round) { m_hackedLeftRound = round; }
	TRound skillLeftRound() { return m_skillLeftRound; }
	TResourceD totalResource();
};

#endif // PLAYER_H
