#ifndef GAME_H
#define GAME_H

#include "definition.h"
#include "data.h"
#include <vector>
#include <string>
using std::vector; 
using std::string;
using std::size_t;


class Game
{
public:
	void init(string filename);//��ʼ����Ϣ
	void run();                //��ʼ�ܴ���
	vector<Info>* generateInfo();
	//void Run(vector<vector<>>)
private:
	void Round();             //ÿ���غ�
	void skillPhase();         //���ܽ׶�
	void regeneratePhase();    //�ָ��׶�
	void transPhase();         //����/�����׶�
	void killPlayer(TCamp id); //ɱ�����   
	vector<Info>* info;
	DATA::Data data;      //���е����ݴ�Ŵ�
	TRound currentRound;  //��ǰ�غ���
	size_t playerSize;    //��Ϸ��ģ
	size_t playerAlive;   //�������
	vector<TStudentID> Rank;//��������Դ������
	TResourceI _MAX_RESOURCE_;//ÿ���ض��������Դ
	vector<int> controlCount; //��¼������
};

#endif // !GAME_H

