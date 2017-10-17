#include"map.h"
#include<fstream>
#include<iostream>
#include "data.h"
#include "student.h"
#include "player.h"
#include "tentacle.h"

Map::Map(DATA::Data* _data):data(_data)
{
}

bool Map::init(ifstream& inMap,TResourceI _MAX_RESOURCE_)  //ͨ���ļ�����ʼ����Ϣ
{

	//��ʼ����ͼ
	inMap >> m_height;
	inMap >> m_width;

	int barrierNum;
	TPoint beginP, endP;
	TBarrier _barrier;
	inMap >> barrierNum;
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
	int campNum;
	inMap >> campNum;
	int _department;
	int stuNum,_tempid;
	vector<TStudentID> _stu;
	for (int i = 0; i < campNum; i++)
	{
		inMap >> _department >> stuNum;
		for (int i = 0; i != stuNum; ++i)
		{
			inMap >> _tempid;
			_stu.push_back(_tempid);
		}
		Player player(data, static_cast<TDepartment>(_department), _stu);
		data->players.push_back(player);
		_stu.clear();   //��շ���ѭ������
	}

	//��ʼ��ѧ��
	int studentNum;
	inMap >> studentNum;
	TPoint _point;
	TCamp _camp; //��Ӫ
	TResourceD _resource;
	bool special;
	TResourceD _techPoint;
	TResourceD _maxResource;
	for (int i = 0; i < studentNum; i++)
	{
		inMap >> _point.m_x;
		inMap >> _point.m_y;
		_point.m_state = Normal;
		m_studentPos.push_back(_point);

		inMap >> _camp >> _resource >> special;
		if (special)
			inMap >> _techPoint >> _maxResource;
		else
			_maxResource = _MAX_RESOURCE_;
		Student stu(data, _point, _camp, _resource,_maxResource, special, _techPoint);
		data->students.push_back(stu);
	}
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
