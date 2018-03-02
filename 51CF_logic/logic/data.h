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

#include "Map.h"
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

		Map gameMap;
	};
}

#endif // !_DATA_H