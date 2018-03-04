#pragma once

#include "definition.h"
#include "cell.h"
#include "tentacle.h"
#include <set>
#include "data.h"
class Player
{
public:
	Player();
	~Player();
	//���ӿƼ�����
	void setdata(DATA::Data* d) { data = d; }
	void addTechPoint(TResourceD _techPoint);
	void regenerateTechPoint();
	//���ٿƼ�������ʧ�ܷ���false
	bool upgrade(TPlayerProperty kind);
	bool subTechPoint(TResourceD _techPoint);
	int getDefenceLevel() const { return m_DefenceLevel; }
	bool upgradeDefence(); //���������������Ƿ�ɹ�
	int getRegenerationLevel() const { return m_RegenerationLevel; }
	bool upgradeRegeneration();
	int getExtraControlLevel() const { return m_ExtraControlLevel; }
	bool upgradeExtraControl();
	int getMoveLevel() const { return m_MoveLevel; }
	bool upgradeMove();
	bool isAlive() { return alive; }
	int maxControlNumber();
	TResourceD totalResource();
	TResourceD techPoint() { return m_techPoint; }
	std::set<TCellID>& cells() { return m_cells; }
	void Kill();
private:
	bool alive = true;
	std::set<TCellID> m_cells;//��ǰϸ��
	TResourceD m_techPoint;//�Ƽ�����
	int m_MoveLevel = 0;
	int m_RegenerationLevel = 0;
	int m_ExtraControlLevel = 0;
	int m_DefenceLevel = 0;
	DATA::Data* data;
};

