#include"map.h"
#include<fstream>
#include<iostream>
#include "data.h"
#include "cell.h"
#include "player.h"
#include "tentacle.h"


bool Map::init(ifstream& inMap,TResourceI _MAX_RESOURCE_, bool enableOutput)  //ͨ���ļ�����ʼ����Ϣ
{

	//��ʼ����ͼ
	inMap >> m_height;
	inMap >> m_width;

	int barrierNum;
	TPoint beginP, endP;
	TBarrier _barrier;
	inMap >> barrierNum;

	if (enableOutput)
		cout << "��ʼ����ͼ......" << endl;

	for (int i = 0; i < barrierNum; i++)
	{
		inMap >> beginP.m_x;
		inMap >> beginP.m_y;
		//beginP.m_state = Barrier;
		inMap >> endP.m_x;
		inMap >> endP.m_y;
		//endP.m_state = Barrier;

		_barrier.m_beginPoint = beginP;
		_barrier.m_endPoint = endP;
		m_barrier.push_back(_barrier);
	}

	//��ʼ����Ӫ
	if (enableOutput)
		cout << "��ʼ����Ӫ......" << endl;
	inMap >> data->PlayerNum;
	data->players = new Player[data->PlayerNum];
	for (int i = 0; i != data->PlayerNum; ++i)
		data->players[i].setdata(data);

	//��ʼ��ϸ��
	if (enableOutput)
		cout << "��ʼ��ϸ��......" << endl;
	inMap >> data->CellNum;
	data->cells = new Cell[data->CellNum];
	TCellID _id;
	TPoint _point;   //λ��
	TPlayerID _camp; //��Ӫ
	TResourceD _resource; //��Դֵ
	TPower _techPower; //�Ƽ�ֵϵ��
	TResourceD _maxResource; //�����Դ
	for (int i = 0; i < data->CellNum; i++)
	{
		inMap >> _point.m_x;
		inMap >> _point.m_y;
		m_studentPos.push_back(_point);

		inMap >> _id >> _camp >> _resource >> _techPower >> _maxResource;
		if (_camp != Neutral)
		{
			data->cells[i].init(_id, data, _point, _camp, _resource, _maxResource, _techPower);
			data->players[_camp].cells().insert(i);//����cells����
		}
		else
		{
			data->cells[i].init(_id, data, _point, _camp, _resource, _maxResource, _techPower);
		}
	}
	data->TentacleCount = 0;
	return true;
}

bool Map::init(const TMapID& filename,TResourceI _MAX_RESOURCE_)
{
	bool ret;
	setID(filename);
	ifstream inMap(filename, ios_base::binary);
	if (!inMap)
	{
		cerr << "can't open the map file" << endl;
		return false;
	}
	ret = init(filename,_MAX_RESOURCE_);
	inMap.close();
	return ret;
}
