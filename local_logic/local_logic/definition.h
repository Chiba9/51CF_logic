#ifndef DEFINITION_H
#define DEFINITION_H

#include <vector>
#include <cmath>
#include <string>
using namespace std;
typedef double TSpeed;
typedef double TResourceD;  //double ����Դ���������ڲ�����
typedef int    TResourceI;  //int    ����Դ����������ʾ
typedef double TLength;
typedef int    TStudentID;
typedef int    TLA;
typedef int    TPosition;
typedef int    TCamp;
typedef string TMapID;
typedef int    TMap;
typedef int    TLevel;  //�������Եȼ�
typedef int    TRound;  //�غ���
typedef double TPower;  //����
typedef int    TTentacleNum;
typedef int    TTentacleID;


const TLevel       STUDENT_LEVEL_COUNT = 5;
const TResourceI   MAX_RESOURCE = 200;
const TSpeed       BASE_REGENERETION_SPEED[STUDENT_LEVEL_COUNT]{ 1,1.5,2,2.5,3 };
const TTentacleNum TENTACLE_NUMBER[STUDENT_LEVEL_COUNT]{1,2,2,3,3};  //���촥������
const TResourceI   STUDENT_STAGE[STUDENT_LEVEL_COUNT + 1]{ 0 ,10,40,80,150,MAX_RESOURCE };
const int          NO_DATA = -1;

//����ܵȼ�
const TLevel MAX_REGENERATION_SPEED_LEVEL = 5;
const TLevel MAX_EXTENDING_SPEED_LEVEL = 5;
const TLevel MAX_EXTRA_CONTROL_LEVEL = 3;
const TLevel MAX_DEFENCE_LEVEL = 3;

//�����ܵȼ���Ӧ��ֵ
const TPower RegenerationSpeedStage[MAX_REGENERATION_SPEED_LEVEL + 1] = { 1,1.05,1.1,1.15,1.2,1.25 };
const TPower ExtendingSpeedStage[MAX_EXTENDING_SPEED_LEVEL + 1] = { 1,1.1,1.2,1.3,1.4,1.5 };
const TPower ExtraControlStage[MAX_EXTRA_CONTROL_LEVEL + 1] = { 0,0.5,1,1.5 };
const TPower DefenceStage[MAX_DEFENCE_LEVEL + 1] = { 1.5,1.4,1.3,1.2 };

//����������������ƴ�����
const TResourceD RegenerationSpeedUpdateCost[MAX_REGENERATION_SPEED_LEVEL] = {2,4,6,8,10};
const TResourceD ExtendingSpeedUpdateCost[MAX_EXTENDING_SPEED_LEVEL] = {2,4,6,8,10};
const TResourceD ExtraControlStageUpdateCost[MAX_EXTRA_CONTROL_LEVEL] = {3,5,7};
const TResourceD DefenceStageUpdateCost[MAX_DEFENCE_LEVEL] = {3,5,7};

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
	Barrier,
	Disables
};

struct TPoint
{
	TPosition  m_x;
	TPosition  m_y;
	PointState m_state;
};


TPoint operator-(const TPoint& p1, const TPoint& p2)
{
	TPoint temp;
	temp.m_x = p1.m_x - p2.m_x;
	temp.m_y = p1.m_y - p2.m_y;
	temp.m_state = Disables;
	return temp;
}

//����ŷʽ����
TLength getDistance(const TPoint& p1, const TPoint& p2)
{
	return sqrt(pow(p1.m_x - p2.m_x, 2) + pow(p1.m_y - p2.m_y, 2));
}

enum StudentType  //ѧ�������ö��
{ 
    XianYu=0,
	XueZha,
	XueBa,
	DaLao,
	JuLao,
	Neutral
};  

struct StudentInfo
{
	TId id;
	StudentType type;
	TId playerId;
	vector<TId> tentacleIds;
	TResourceD learnAbility;
	TResourceD occupyLearingAbility; 
	vector<TId> attackTo;
	vector<TId> attackBy;
	TPoint position;
};

struct PlayerInfo
{
	TId id;
	bool isAlive;
	int rank;          //����/����ѧ��/���������ϵ�
	vector<TId> studentIds;  //ѧ��ID
	TDepartment m_department;            //Ժϵ����
	TResourceD m_technologyPoint;        //�Ƽ�����

	TLevel RegenerationSpeedLevel;      //�������ʵȼ�
	TLevel ExtendingSpeedLevel;         //�����ٶȵȼ�
	TLevel ExtraControlLevel;           //����������ȼ�
	TLevel DefenceLevel;          //�����ȼ�

	TRound skillLeftRound = 0;       //ʣ���������ܻغ�
	size_t maxControlNumber;    //��������

	bool hacked;                //�Ƿ񱻺�
	bool alive;                  //�Ƿ񻹻���
};

struct TentacleInfo
{
	TId             m_sourceStudent;              //Դͬѧ
	TId             m_targetStudent;              //Ŀ��ͬѧ
	TentacleStatus  m_status;                     //����״̬
	TLength         m_length;                     //���ֳ��ȣ���Դ/Ŀ�������
	TResourceI      m_resource;                   //��ǰ��Դ      ���ж�ǰ��Ч��
	TResourceI      m_frontResource;              //�жϺ�ǰ����Դ���жϺ���Ч��
	TResourceI      m_backResource;               //�жϺ����Դ���жϺ���Ч��
	TId             m_enemyTentacle;              //�Է�����
};

struct TBarrier
{
	TPoint m_beginPoint;
	TPoint m_endPoint;
};

class BaseMap
{
public:
	void   setID(TMapID _id) { id = _id;        }
	TMap   getWidth()  const { return m_width;  }
	TMap   getHeigth() const { return m_height; }
	bool   passable(TPoint p1, TPoint p2)   //�жϴ����ܷ�������������
	{
		for (auto b : m_barrier)
		{
			//�����ų�ʵ��
			int minFX = max(min(p1.m_x, p2.m_x), min(b.m_beginPoint.m_x, b.m_endPoint.m_x));
			int maxFX = min(max(p1.m_x, p2.m_x), max(b.m_beginPoint.m_x, b.m_endPoint.m_x));
			int minFY = max(min(p1.m_y, p2.m_y), min(b.m_beginPoint.m_y, b.m_endPoint.m_y));
			int maxFY = min(max(p1.m_y, p2.m_y), max(b.m_beginPoint.m_y, b.m_endPoint.m_y));
			if (minFX > maxFX || minFY > maxFY)
				return false;
			//��Խʵ��
			if (cross(p1 - b.m_beginPoint, b.m_endPoint - b.m_beginPoint)*cross(b.m_endPoint - b.m_beginPoint, p2 - b.m_beginPoint) >= 0
				|| cross(b.m_beginPoint - p1, p2 - p1)*cross(p2 - p1, b.m_endPoint - p1) >= 0)
				return false;
		}
		return true;
	}
	bool   isPosValid(TPoint p) { return isPosValid(p.m_x, p.m_y); }             //�жϵ��Ƿ�Խ��
	bool   isPosValid(int x, int y) { return x >= 0 && x < m_width&&y >= 0 && y <= m_height; }

	const  vector<TPoint>  &  getStudentPos() const { return m_studentPos; }
	const  vector<TBarrier>&  getBarriar()    const { return m_barrier;    }
protected:
	string             id;                  //��¼��ͼ��id����game��ֵ����init����ʹ�ã�ѡ���Ӧ���ļ�
	TMap               m_width;
	TMap               m_height;
	vector<TPoint>     m_studentPos;        //ֻ�趨ϸ�������֮꣬����������佻��game
	vector<TBarrier>   m_barrier;
private:
	int cross(const TPoint& p1, const TPoint& p2) { return p1.m_x*p2.m_y - p1.m_y*p2.m_x; }//���
	int min(int a, int b) { return a < b ? a : b; }
	int max(int a, int b) { return a < b ? b : a; }
};

struct Info
{
	int playerCount;  //ʣ�������
	int id;           //ѡ��ID��
	TRound round;     //�غ���
	vector<PlayerInfo> playerInfo;   //������Ϣ
	vector<StudentInfo> studentInfo; //ͬѧ��Ϣ
	vector<TentacleInfo> tentacleInfo; //������Ϣ
	BaseMap* mapInfo;  //��ͼ��Ϣ
};

#endif // DEFINITION_H