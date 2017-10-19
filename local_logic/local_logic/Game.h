#ifndef GAME_H
#define GAME_H

#include "definition.h"
#include "data.h"
#include <vector>
#include <string>
#include <fstream>
using std::vector; 
using std::string;
using std::size_t;


class Game
{
public:
	void init(string filename);//��ʼ����Ϣ
	void run();                //��ʼ�ܴ���
	//void Run(vector<vector<>>)
private:
	vector<Info>* generateInfo();
	void Round();             //ÿ���غ�
	void skillPhase();         //���ܽ׶�
	void regeneratePhase();    //�ָ��׶�
	void movePhase();          //�����ƶ�
	void transPhase();         //����/�����׶�
	void subRoundPhase();      //��С���ֻغ���
	void killPlayer(TCamp id); //ɱ�����   
	void updateLog();
	std::ofstream LogFile;
	vector<Info>* info;
	DATA::Data data;      //���е����ݴ�Ŵ�
	TRound currentRound;  //��ǰ�غ���
	size_t playerSize;    //��Ϸ��ģ
	size_t playerAlive;   //�������
	vector<TStudentID> Rank;//��������Դ������
	TResourceI _MAX_RESOURCE_;//ÿ���ض��������Դ
	TRound _MAX_ROUND_;
	vector<int> controlCount; //��¼������
};

#endif // !GAME_H

