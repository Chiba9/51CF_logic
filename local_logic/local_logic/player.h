#ifndef PLAYER_H
#define PLAYER_H

#include "definition.h"
#include "object.h"
#include "vector"


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
	bool _updateRegeneration();
	bool _updateExtending();
	bool _updateExtraControl();
	bool _updateDefence();

public:

	void addStudent(TId student);             //����ͬѧ
	void removeStudent(TId student);          //����ͬѧ
	void setHacked(bool isHacked);            //�����Ƿ񱻺�
	bool update(TPlayerProperty property);    //����    
	void addTechPoint();                      //���ݵ�ǰϸ�����ӿƼ�����

	//�õ�������

	bool isHacked();
	bool isAlive();
	TResourceD techPoint();
	std::vector<TId> getStudents();
	std::size_t maxControlNumber();
	TDepartment getDepartment();
	TLevel regenerationSpeedLevel();
	TLevel extendingSpeedLevel();
	TLevel extraControlLevel();
	TLevel defenceLevel();
	TRound skillLeftRound();
};

#endif // PLAYER_H
