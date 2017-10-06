#ifndef DEFINITION_H
#define DEFINITION_H

typedef double TSpeed;
typedef double TResourceD;
typedef int    TResourceI;
typedef double TLength;
typedef int    TStudentID ;
typedef int    TLA;
typedef int    TPosition;
typedef int    TCamp;
typedef int    TMap;
typedef int    TMapID;

const TSpeed     BASE_LEARN_ABILITY[5]{ 1,1.5,2,2.5,3 };
const TResourceI STUDENT_STAGE[4]{ 10,40,80,150 };
const TResourceI MAX_RESOURCE = 200;
const int        NO_DATA = -1;

enum TentacleStatus
{
	Extending           //������
	,Backing            //�˺��У������ˣ�
	,Confrontation      //������
	,Arrived            //�ѵ���Ŀ�ĵ�
	,AfterCut           //���ж�
	,Finished           //�Ѿ�������ϣ���ʧ
};

enum PointState
 {
	 Normal,
	 Barriar,
	 Disables
};

struct Point
{
	TPosition  m_x;
	TPosition  m_y;
	PointState m_state;
};


enum StudentType  //ѧ�������ö��
{ 
     XianYu,
	 XueZha,
	 XueBa,
	 DaLao,
	 JuLao,
	 Neutral;
};  

#endif // DEFINITION_H