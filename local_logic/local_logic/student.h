#pragma once

#ifndef  STUDENT_H_
#define  STUDENT_H_

#include"object.h"
#include<vector>
using namespace std;


typedef int   TStudentID ;
typedef int   TLA;
typedef int   TPosition;
typedef int   TCamp;
typedef float TRegenarationSpeed;

class Tentacle;
class Point;
class Tentacle;


enum PointState {NORMAL,BARRIER,DISABLED};
struct Point
{
	TPosition  m_x;
	TPosition  m_y;
	PointState m_state;
};


enum StudentType  { XIANYU,XUEZHA,XUEBA,DALAO,JULAO,NEUTRAL};  //ѧ�������ö��

struct StudentProperty
{
   TLA m_minLA;
   TLA m_maxLA;
   int m_maxTentacleNum;  //���������
   TRegenarationSpeed m_regenarationSpeed;  //�����ٶ�
};


class Student:public Object<Student>
{
public:
	Student();
	~Student();
	Student(const Student &);
	inline  StudentType    m_getStudentType();
    inline  void           m_setStudentType(const StudentType & _type);
	inline  TStudentID     m_getId();
	inline  void           m_setId( TStudentID _id);
	inline  TLA            m_getLeftLA();
	inline  void           m_setLeftLA(TLA);
	inline  TCamp          m_getCamp();
	inline  void           m_setCamp(TCamp _camp);
	inline  Point          m_getPos();
	inline  void           m_setPos(const Point& _point);
	inline  void           m_setOccupyLA(TLA _LA);
	inline  TLA            m_getOccupyLA();

	bool    m_LAempty();                  //ѧ��ֵ�Ƿ��Ϊ0

	void    m_addLA();                    //ÿһ�غϺ��������Դ
	void    m_reduceLAForAttacked();      //��Ϊ������������ѧ��ֵ���ɱ��������Լ���ѧ��vector������
	void    m_reduceLAForstalemate();     //��Ϊ���Ŷ�����ѧ��ֵ,ͨ�������Լ��Ĵ���vector������ 
	bool    m_addTentacle(const TCamp &,const TStudentID&);  //���Ӵ���,ѧ����������false
	bool    m_cutTentacle(int _id, const TPosition &);       //��ĳһ���㿳�ϴ��֣�����Ч�򿳶ϲ�����Ч,����bool

private:
	StudentType      m_studentType;      //ѧ�����࣬���е� int
	TCamp            m_camp;             //������Ӫ  int
	TStudentID       id;                 //ѧ��id   int
	TLA              m_leftLA;           //ʣ��ѧ��ֵ
	Point            m_position;         //���ڵ��λ�õ���Ϣ
	TLA              m_occupyLA;         //����ͬѧ��ռ��ֵ

	vector<Tentacle> m_preTentacle;      //��ǰ���ȥ�Ĵ���
	vector<Student>  m_attackedBy;       //���ڱ�����Щͬѧ����
	
};

#endif // STUDENT_H_