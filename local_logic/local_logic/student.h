#pragma once

#ifndef  STUDENT_H_
#define  STUDENT_H_

#include"object.h"
#include<vector>
#include"tentacle.h"
#include"definition.h"
using namespace std;


struct StudentProperty
{
   TLA m_minLA;
   TLA m_maxLA;
   int m_maxTentacleNum;  //���������
   TSpeed m_regenarationSpeed;  //�����ٶ�
};


class Student:public Object<Student>
{
public:
	Student();
	~Student();
	Student(const Student &);
	inline  StudentType    getStudentType();
    inline  void           setStudentType(const StudentType & _type);
	inline  TStudentID     getId();
	inline  void           setId( TStudentID _id);
	inline  TLA            getLeftLA();
	inline  void           setLeftLA(TLA);
	inline  TCamp          getCamp();
	inline  void           setCamp(TCamp _camp);
	inline  TPoint          getPos();
	inline  void           setPos(const TPoint& _point);
	inline  void           setOccupyLA(TLA _LA);
	inline  TLA            getOccupyLA();

	bool    LAempty();                  //ѧ��ֵ�Ƿ��Ϊ0

	void    addLA();                    //ÿһ�غϺ��������Դ
	void    reduceLAForAttacked();      //��Ϊ������������ѧ��ֵ���ɱ��������Լ���ѧ��vector������
	void    reduceLAForstalemate();     //��Ϊ���Ŷ�����ѧ��ֵ,ͨ�������Լ��Ĵ���vector������ 
	bool    addTentacle(const TCamp &,const TStudentID&);  //���Ӵ���,ѧ����������false
	bool    cutTentacle(int _id, const TPosition &);       //��ĳһ���㿳�ϴ��֣�����Ч�򿳶ϲ�����Ч,����bool

private:
	StudentType      m_studentType;      //ѧ�����࣬���е� int
	TCamp            m_camp;             //������Ӫ  int
	TStudentID       id;                 //ѧ��id   int
	TLA              m_leftLA;           //ʣ��ѧ��ֵ
	TPoint            m_position;         //���ڵ��λ�õ���Ϣ
	TLA              m_occupyLA;         //����ͬѧ��ռ��ֵ
	vector<Tentacle> m_preTentacle;      //��ǰ���ȥ�Ĵ���
	vector<Student>  m_attackedBy;       //���ڱ�����Щͬѧ����
	
};

#endif // STUDENT_H_