#pragma once

#ifndef MAP_H_
#define MAP_h_
#include<vector>
#include <string>
#include "data.h"
using namespace std;
using namespace DATA;


class Map:public BaseMap
{
public:
	//Map();
	//~Map();

	//void   setWidth(TMap );
	//void   setHeiget(TMap );
	
	bool   init();            //�����ļ���ʼ����ǰ��ͼ,���ɹ�����false

};

#endif
