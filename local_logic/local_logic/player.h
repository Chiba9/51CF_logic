#ifndef PLAYER_H
#define PLAYER_H

#include "definition.h"
#include "object.h"
#include <vector>


class Student;

class Player :public Object<Player>
{
private:
	std::vector<TId> m_students;         //����ͬѧ
	TDepartment m_department;            //Ժϵ����
	TResourceD m_technologyPoint = 0.0;        //�Ƽ�����

	TLevel m_RegenerationSpeedLevel = 0;      //�������ʵȼ�
	TLevel m_ExtendingSpeedLevel = 0;      //�����ٶȵȼ�
	TLevel m_ExtraControlLevel = 0;        //����������ȼ�
	TLevel m_DefenceLevel = 0;       //�����ȼ�

	TRound m_skillLeftRound = 0;       //ʣ���������ܻغ�
	std::size_t m_maxControlNumber;    //��������

	bool m_hacked = false;                //�Ƿ񱻺�
	bool m_alive = true;                  //�Ƿ񻹻���

	//�������ֱ������ԣ������Ƿ�ɹ�
	bool _upgradeRegeneration();
	bool _upgradeExtending();
	bool _upgradeExtraControl();
	bool _upgradeDefence();

public:

	void addStudent(TId student);             //����ͬѧ
	void removeStudent(TId student);          //����ͬѧ
	void setHacked(bool isHacked);            //�����Ƿ񱻺�
	bool upgrade(TPlayerPowerProperty property);    //����    
	void addTechPoint();                      //���ݵ�ǰϸ�����ӿƼ�����
	void Kill();                              //ɱ�������

	//�õ�������

	bool isHacked() { return m_hacked; }
	bool isAlive() { return m_alive; }
	TResourceD techPoint() { return m_technologyPoint; }
	std::vector<TId> getStudents() { return m_students; }
	std::size_t getStudentNumber() { return m_students.size(); }
	std::size_t maxControlNumber() { return m_maxControlNumber;}
	TDepartment getDepartment() { return m_department; }
	TLevel regenerationSpeedLevel() { return m_RegenerationSpeedLevel; }
	TLevel extendingSpeedLevel() { return m_ExtendingSpeedLevel; }
	TLevel extraControlLevel() { return m_ExtraControlLevel; }
	TLevel defenceLevel() { return m_DefenceLevel; }
	TRound skillLeftRound() { return m_skillLeftRound; }
};

#endif // PLAYER_H
