#ifndef DEFINITION_H
#define DEFINITION_H

typedef double TSpeed;
typedef double TResourceD;  //double ����Դ���������ڲ�����
typedef int    TResourceI;  //int    ����Դ����������ʾ
typedef double TLength;
typedef int    TStudentID ;
typedef int    TLA;
typedef int    TPosition;
typedef int    TCamp;
typedef int    TMap;
typedef int    TMapID;
typedef int    TLevel;  //�������Եȼ�
typedef int    TRound;  //�غ���
typedef double TPower;  //����

const TSpeed     BASE_LEARN_ABILITY[5]{ 1,1.5,2,2.5,3 };
const TResourceI STUDENT_STAGE[4]{ 10,40,80,150 };
const TResourceI MAX_RESOURCE = 200;
const int        NO_DATA = -1;

//����ܵȼ�
const TLevel MAX_REGENERATION_SPEED_LEVEL = 6;
const TLevel MAX_EXTENDING_SPEED_LEVEL = 6;
const TLevel MAX_EXTRA_CONTROL_LEVEL = 4;
const TLevel MAX_DEFENCE_LEVEL = 4;

//�����ܵȼ���Ӧ��ֵ
const TPower RegenerationSpeedStage[MAX_REGENERATION_SPEED_LEVEL] = { 1,1.05,1.1,1.15,1.2,1.25 };
const TPower ExtendingSpeedStage[MAX_EXTENDING_SPEED_LEVEL] = { 1,1.1,1.2,1.3,1.4,1.5 };
const TPower ExtraControlStage[MAX_EXTRA_CONTROL_LEVEL] = { 0,0.5,1,1.5 };
const TPower DefenceStage[MAX_DEFENCE_LEVEL] = { 1.5,1.4,1.3,1.2 };

enum TDepartment
{
	Aeronautics          //��Ժ
	, Medical            //ҽѧ
	, Energy             //��Դ
	, Electronic         //����
	, Economy            //����
	, Computer           //�����
	, Automation         //�Զ���
	, Environment        //����
};

enum TPlayerProperty
{
	RegenerationSpeed    //�����ٶ�
	, ExtendingSpeed //�����ٶ�
	, ExtraControl   //���������
	, Defence        //�����ȼ�
};

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
	Blocked,
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
	Neutral
};  

#endif // DEFINITION_H