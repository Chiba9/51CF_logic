#include "ai.h"
#include "definition.h"
#include "user_toolbox.h"
#include <iostream>
#include <vector>
void player_ai(Info& info)
{
	TPlayerID myid = info.myID;
	//������ָ��ѹ����У����ݵ÷�ѡȡָ��
	MaxHeap<float, Command> evalution; 
	for(TCellID mycell:info.playerInfo[info.])
}
