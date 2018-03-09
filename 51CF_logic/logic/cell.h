#pragma once
/*
** Class Cell
** ϸ����
** ����ÿ��ϸ������Ϣ
** ����޸�:2017/12/26
** By Chiba
*/
#ifndef  STUDENT_H_
#define  STUDENT_H_

#include<vector>
#include"tentacle.h"
#include"definition.h"
#include <iostream>
#include <set>
#include "data.h"

using namespace std;

struct CellProperty
{
	//TLA m_minLA;
	TResourceD m_maxResource;
	int m_maxTentacleNum;  //���������
	TPower m_techSpeed;    //�ƴ���������Դ�������ʵļ���
};


class Cell
{
	friend class Tentacle;
public:
	Cell() :data(nullptr) {}   //Ĭ�Ϲ��캯�������������Ϣ
	//����������Ϣ���г�ʼ��
	Cell(DATA::Data* _data, TPoint pos, TPlayerID campid, TResourceD resource, TResourceD maxResource, TPower techPower);
	~Cell(){}
	//Cell(const Cell &) = default;
	Cell(Cell& _cell); //#json
	
	void init(TCellID _id, DATA::Data* _data, TPoint pos, TPlayerID campid, TResourceD resource, TResourceD maxResource, TPower techPower);
	
	inline  TResourceD              getResource()           const { return m_resource; }
	inline  TCellID          getID() { return m_ID; }  //#json
	inline  TPlayerID        getPlayerID()const { return m_PlayerID; }
	inline  TPoint           getPos()              const { return m_position; }
	inline  TResourceD              getOccupyPoint()         const { return m_occupyPoint; }
	inline  CellType     getCellType()      const { return m_cellType; }
	inline  CellProperty& getCellProperty() { return m_property; }
	
	inline  CellStrategy getStg() { return m_strategy; }
	bool changeStg(CellStrategy stg);
	inline  void             setOccupyPoint(TResourceD val) { m_occupyPoint = val; }
	inline  TPlayerID getOccupyOwner() { return m_occupyOwner; }

	inline  void             setResource(TResourceD _la) { m_resource = _la; }
	inline  void             setPlayerID(TPlayerID _camp) { m_PlayerID = _camp; }
	inline  void             setCellType(const CellType & _type) { m_cellType = _type; }
	inline  void             setPos(const TPoint& _point) { m_position = _point; }
	TResourceD       totalResource();    //���ظ�ϸ����Դֵ���䴥����Դֵ

	inline  int   TentacleNumber()const { return m_currTentacleNumber; } //���ش�������
	TSpeed  baseRegenerateSpeed()const;
	TSpeed  baseTransSpeed()const;
	bool    resourceEmpty() { return m_resource <= 0.001; }                  //��Դֵ�Ƿ��Ϊ0
	TSpeed Cell::techRegenerateSpeed()const;
	void    regenerate();                    //ÿһ�غϺ��������Դ

	void addResource(TResourceD _r) { m_resource += _r; if (m_resource > m_property.m_maxResource)m_resource = m_property.m_maxResource; }

	bool    addTentacle(const TCellID&);  //���Ӵ���,���ɹ�����false
	bool    cutTentacle(const TCellID&, TPosition pos);       //��ĳһ���㿳�ϴ��֣�����Ч�򿳶ϲ�����Ч,�����Ƿ�ɹ�
	void    updateProperty();            //���ݵ�ǰ��Դ��������
	void    changeOwnerTo(TPlayerID newOwner); //�ı����ˣ���Դ���������ⲿ
	void    N_addOcuppyPoint(TPlayerID owner, TResourceD point);  //N_ǰ׺/ֻ������ϸ���ܹ�����/����Ӧ����
	void    subTentacleNum() { m_currTentacleNumber--; }
	std::set<TTentacleID>& getTentacles() { return m_currTentacle; }

private:
	TCellID m_ID; //�ҵ�ID
	CellType      m_cellType;      //ϸ������
	CellProperty  m_property;         //�ص�
	CellStrategy m_strategy;  //����

	TResourceD       m_resource;           //ʣ����Դֵ

	DATA::Data*            data;             //��������
	TPlayerID            m_PlayerID;           //������Ӫ  int
	TPoint           m_position;         //���ڵ��λ�õ���Ϣ
	TResourceD              m_occupyPoint;         //����ͬѧ��ռ��ֵ
	TPlayerID               m_occupyOwner;       //������������
	TTentacleNum m_currTentacleNumber;
	std::set<TTentacleID> m_currTentacle;
};

#endif // STUDENT_H_