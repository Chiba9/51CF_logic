#pragma once

#ifndef MAP_H_
#define MAP_h_
#include"student.h"
#include<vector>
using namespace std;

typedef  int TMap;
typedef  int TMapID;

class Tentacle;
class Player;

struct Barrier
{
	Point m_beginPoint;
	Point m_endPoing;
};

class Map
{
public:
	Map();
	~Map();
	TMap   getWidth()  const;
	TMap   getHeigth() const ;
	void   setWidth(TMap );
	void   setHeiget(TMap );
	
	bool   init();                        //�����ļ���ʼ����ǰ��ͼ,���ɹ�����false
	bool   passable(Point p1,Point p2);   //�жϴ����ܷ�������������
	bool   isOutside(Point );             //�жϵ��Ƿ�Խ��
	
	const  vector<Point>  &  getStudentPos() const;
	const  vector<Barrier>&  getBarriar()    const;
private:
	TMapID            id;                  //��¼��ͼ��id����game��ֵ����init����ʹ�ã�ѡ���Ӧ���ļ�
	TMap              m_width;
	TMap              m_height;
	vector<Point>     m_studentPos;        //ֻ�趨ϸ�������֮꣬����������佻��game
	vector<Barrier>   m_bariar; 

};

#endif
