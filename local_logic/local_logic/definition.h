#ifndef DEFINITION_H
#define DEFINITION_H

typedef double TSpeed;
typedef double TResourceD;
typedef int TResourceI;
typedef double TLength;

const TSpeed BASE_LEARN_ABILITY[5]{ 1,1.5,2,2.5,3 };
const TResourceI STUDENT_STAGE[4]{ 10,40,80,150 };
const TResourceI MAX_RESOURCE = 200;
const int NO_DATA = -1;

enum TentacleStatus
{
	Extending           //������
	,Backing            //�˺��У������ˣ�
	,Confrontation      //������
	,Arrived            //�ѵ���Ŀ�ĵ�
	,AfterCut           //���ж�
	,Finished           //�Ѿ�������ϣ���ʧ
};

#endif // DEFINITION_H