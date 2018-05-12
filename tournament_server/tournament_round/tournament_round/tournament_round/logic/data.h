//#pragma once
#ifndef _DATA_H
#define _DATA_H
/*
**  Data�ṹ��
**  �������ݵĴ洢�͹���
**  ���ⲿ�洢�����ֻ��洢 ID �� Data �е���
*/
class Cell;
class Tentacle;
class Player;


#include "map.h"
#include "../json/json.h"

struct CutTentacleInfoJson
{
	int cutID = -1;
	double frontResource = -1;
};

namespace DATA//���ռ�
{
	struct Data
	{
		Cell* cells;
		int CellNum;

		Tentacle*** tentacles;
		int TentacleNum;

		Player* players;
		int PlayerNum;

		Json::Value root;
		Json::Value currentRoundJson;
		vector<vector<CutTentacleInfoJson>>  cutTentacleInfoJson;
		vector<vector<bool>> cutTentacleJson;  //�����жϱ�־
		vector<vector<bool>> cutTentacleBornJson;  // �ϴ������ɱ�־

		Map gameMap;
	};
}

#endif // !_DATA_H