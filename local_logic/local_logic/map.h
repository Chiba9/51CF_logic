#pragma once

#ifndef MAP_H_
#define MAP_h_
#include"student.h"
#include<vector>
#include <string>
using namespace std;


typedef  int TMap;
typedef  int TMapID;

class Tentacle;
class Player;


class Map:public BaseMap
{
public:
	//Map();
	//~Map();

	//void   setWidth(TMap );
	//void   setHeiget(TMap );
	
	bool   init(string filename);                        //�����ļ���ʼ����ǰ��ͼ,���ɹ�����false

};

#endif
