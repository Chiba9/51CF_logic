#pragma once
/*
**Tencacle��
**
**2017/12/26
**By Chiba
**
*/
#ifndef TENTACLE_H
#define TENTACLE_H
#include "definition.h"
#include "data.h"
#include "cell.h"
#include "player.h"
enum TransType
{
	moveE, transE
};
using namespace DATA;
//������ʾ��Ŀ��ͬѧ����Ч������ʱ����
struct TransEffect
{
	TransType      m_type;
	TCellID        m_target;                   //Ŀ��ϸ��
	TCellID        m_source;                   //Դϸ��
	TPlayerID      m_currOwner; //��ǰԴϸ��������
	TResourceD     m_resourceToTarget = 0.0;          //��Ŀ�����Դ��
	TResourceD     m_resourceToSource = 0.0;          //��Դ����Դ��
	TResourceD     m_resourceChange = 0.0;           //����Դ�ı���
	TentacleState m_currstate;                      //��ǰ״̬-�����ж�����ʱ
	TResourceD     m_frontChange = 0.0;        //ֻ�����ж�
	TResourceD     m_backChange = 0.0;         //ֻ�����ж�
	bool handle; //�Ƿ�Ҫ����
	TransEffect(int target, int source,TentacleState ts, TPlayerID p):
		m_target(target), m_source(source), m_currstate(ts),m_currOwner(p) {handle = true;}
	TransEffect() { handle = false; }
};

class Tentacle
{
private:
	const TCellID             m_source;              //Դϸ��
	const TCellID             m_target;              //Ŀ��ϸ��
	TentacleState  m_state;                     //����״̬
	TTentacleID  m_id;
	const TLength         m_length;                     //���ֳ��ȣ���Դ/Ŀ�������
	const TResourceD      m_maxResource;
	TResourceD      m_resource;                   //��ǰ��Դ      ���ж�ǰ��Ч��
	TResourceD      m_frontResource;              //�жϺ�ǰ����Դ���жϺ���Ч��
	TResourceD      m_backResource;               //�жϺ����Դ���жϺ���Ч��

	DATA::Data* const     data;

public:
	//�½�����
	Tentacle() :m_source(NO_DATA),
		m_target(NO_DATA), m_length(0), m_maxResource(0), data(nullptr) {}
	Tentacle(TCellID source, TCellID target, DATA::Data* _data);
	//�жϴ��֣�positionΪ��Դϸ���������Դ��������ֵ��ʾ�Ƿ�ɹ�
	
	bool cut(TResourceD position = 0);
	//�����ƶ���ֻ��Extending/Attacking/Backing��Ч
	TransEffect move();
	//��������
	TransEffect transport();

	bool           isTargetEnemy() const;
	const CellStrategy   srcStg(); //Դϸ������
	const CellStrategy   tgtStg(); //Ŀ��ϸ������
	TTentacleID getID()const { return m_id; }
	const TSpeed         getExtendSpeed()   const;
	const TSpeed         getFrontSpeed()   const;
	const TSpeed         getBackSpeed()   const;
	const TCellID            getTargetCell() const { return m_target; }
	const TCellID            getSourceCell() const { return m_source; }
	TentacleState getstate()        const { return m_state; }
	const TLength        getLength()        const { return m_length; }
	TResourceD     getResource()      const { return m_resource; }
	TResourceD     getFrontResource() const { return m_frontResource; }
	TResourceD     getBackResource()  const { return m_backResource; }
	Tentacle*      getEnemyTentacle() const { return data->tentacles[m_target][m_source]; }
	void takeEffect(const TransEffect& te);
	void           setstate(TentacleState ts) { m_state = ts; }
	TResourceD     totalResource()const;
	void           finish();                //�����������ֵ�һ��
};

#endif // !TENTACLE_H