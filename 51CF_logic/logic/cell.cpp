#include "cell.h"
#include "data.h"
#include "player.h"
Cell::Cell(DATA::Data* _data, TPoint pos, TPlayerID playerid, TResourceD resource, TResourceD maxResource, TPower techPower)
	:data(_data),m_position(pos),m_PlayerID(playerid),m_resource(resource)
{
	m_property.m_maxResource = maxResource;
	m_property.m_techSpeed = techPower;
	m_strategy = Normal;
	updateProperty();
}

Cell::Cell(Cell& _cell)
{
	m_ID = _cell.getID();
	m_cellType = _cell.getCellType();
	m_property = _cell.getCellProperty();
	m_strategy = _cell.getStg();
	m_resource = _cell.getResource();
	m_PlayerID = _cell.getPlayerID();
	m_position = _cell.getPos();
	m_occupyPoint = _cell.getOccupyPoint();
	m_occupyOwner = _cell.getOccupyOwner();
	m_currTentacleNumber = _cell.TentacleNumber();

}

void Cell::init(TCellID _id, DATA::Data* _data, TPoint pos, TPlayerID campid, TResourceD resource, TResourceD maxResource, TPower techPower)
{
	m_ID = _id;
	data = _data;
	m_position = pos;
	m_PlayerID = campid;
	m_resource = resource;
	m_property.m_maxResource = maxResource;
	m_property.m_techSpeed = techPower;
	m_strategy = Normal;
	updateProperty();
	m_currTentacleNumber = 0;
	if (campid == Neutral)
	{
		m_occupyOwner = -1;
		m_occupyPoint = 0;
	}
}


bool Cell::changeStg(CellStrategy stg)
{
	if (data->players[getPlayerID()].techPoint() > CellChangeCost[m_strategy][stg])
	{
		data->players[getPlayerID()].subTechPoint(CellChangeCost[m_strategy][stg]);
		m_strategy = stg;
		return true;
	}
	else return false;
}

TResourceD Cell::totalResource()
{
	TResourceD sum = 0.0;
	for (int i = 0; i != data->CellNum; ++i)
		if (data->tentacles[m_ID][i])
			//�������ֵ���Դֻ�������������
			sum += (data->tentacles[m_ID][i]->getResource() +
				data->tentacles[m_ID][i]->getFrontResource() + data->tentacles[m_ID][i]->getBackResource());
	sum += m_resource;
	return sum;
}

TSpeed Cell::baseRegenerateSpeed() const
{
	if (getPlayerID() != -1)
		return BASE_REGENERETION_SPEED[getCellType()] *
		RegenerationSpeedStage[data->players[getPlayerID()].getRegenerationLevel()];
	else
		return 0.0;//����
}

TSpeed Cell::techRegenerateSpeed()const
{
	return baseRegenerateSpeed()*
		m_property.m_techSpeed;
}

TSpeed Cell::baseTransSpeed() const
{
	return baseRegenerateSpeed()*
		TentacleDecay[m_currTentacleNumber];

}

void Cell::regenerate()
{
#ifdef FC15_DEBUG
	TResourceD m_oldR = m_resource, m_oldT = data->players[m_PlayerID].techPoint();
#endif
	m_resource += baseRegenerateSpeed() * CellStrategyRegenerate[m_strategy];
	if (m_resource > m_property.m_maxResource)
		m_resource = m_property.m_maxResource;
	data->players[m_PlayerID].addTechPoint(baseRegenerateSpeed() * m_property.m_techSpeed * CellStrategyRegenerate[m_strategy]);
#ifdef FC15_DEBUG
    cout << "���� " << m_ID << " �ظ� " << m_resource - m_oldR << " ��Դ " << data->players[m_PlayerID].techPoint() - m_oldT << " �Ƽ� " << endl;
#endif
}

bool Cell::addTentacle(const TCellID& target)
{
	//�Ѿ��������������
	if (m_currTentacleNumber >= m_property.m_maxTentacleNum)
		return false;
	//���������Ѿ�����
	if (data->tentacles[m_ID][target])
		return false;
	if (m_ID == target)
		return false;
	//���ݶ�����û�д����ж�״̬
	if (data->tentacles[target][m_ID])
	{
		//�������Ѿ���Ҳ�д���
		if (data->cells[target].getPlayerID() == getPlayerID())
		{
			/*
			data->tentacles[target][m_ID]->cut(data->tentacles[target][m_ID]->getResource());
			t->setstate(Extending);*///Ӧ��ΪΥ������
			return false;
		}
		else
		{
			switch (data->tentacles[target][m_ID]->getstate())
			{
			case Attacking:break; //�����ܳ���
			case Backing:break; //�����ܳ���
			case Confrontation:break; //�����ܳ���
			case Extending:
			{
				Tentacle* t = new Tentacle(m_ID, target, data);
				t->setstate(Extending);
				data->tentacles[m_ID][target] = t;
				m_currTentacleNumber++;
				m_currTentacle.insert(t->getID());
				return true;
			}
			case Arrived:
			{
				Tentacle* t = new Tentacle(m_ID, target, data);
				t->setstate(Attacking); data->tentacles[target][m_ID]->setstate(Backing);
				data->tentacles[m_ID][target] = t;
				m_currTentacleNumber++;
				m_currTentacle.insert(t->getID());
				return true;
			}
			case AfterCut:
			{
				if (data->tentacles[target][m_ID]->getFrontResource() > 0.001)//�Է����ڹ���
					return false;
				else
				{
					Tentacle* t = new Tentacle(m_ID, target, data);
					t->setstate(Extending);
					data->tentacles[m_ID][target] = t;
					m_currTentacleNumber++;
					m_currTentacle.insert(t->getID());
					return true;
				}
			}
			default:
				return false;
				break;
			}
		}
	}
	else
	{
		Tentacle* t = new Tentacle(m_ID, target, data);
		t->setstate(Extending);
		data->tentacles[m_ID][target] = t;
		m_currTentacleNumber++;
		m_currTentacle.insert(t->getID());
		return true;
	}
	return false;
}

bool Cell::cutTentacle(const TCellID& tag, TPosition pos)
{
	//û�д���
	if (!data->tentacles[m_ID][tag])
		return false;
	Tentacle* t = data->tentacles[m_ID][tag];
	return t->cut(pos);//�����������cut�ڲ�����
}

void Cell::updateProperty()
{
	for (int i = 0; i != STUDENT_LEVEL_COUNT; ++i)
		if (STUDENT_STAGE[i] <= m_resource||i == 0)//����Ҳ����������
			m_cellType = static_cast<CellType>(i);
		else
			break;
	m_property.m_maxTentacleNum = MAX_TENTACLE_NUMBER[m_cellType];
}

void Cell::changeOwnerTo(TPlayerID newOwner)
{
	//���ж����д���
	for (int i = 0; i != data->CellNum; ++i)
	{
		cutTentacle(i, 1000000/*һ���ܴ����*/);//���津�ֵ�����Ѿ����ڲ�����
	}
	m_strategy = Normal; //���ò���
	if (m_PlayerID >= 0 && m_PlayerID < data->PlayerNum)//������
	{
		data->players[m_PlayerID].cells().erase(m_ID);
	}
	if (newOwner >= 0 && newOwner < data->PlayerNum)//������
	{
		data->players[newOwner].cells().insert(m_ID);
	}
	if(m_PlayerID != Neutral) //�������������õ�10
		m_resource = 10;
	else
	{
		m_occupyOwner = Neutral;
		m_occupyPoint = 0.0;
	}
	m_PlayerID = newOwner; //�ı�����
}

void Cell::N_addOcuppyPoint(TPlayerID owner, TResourceD point)
{
	if (m_PlayerID != Neutral)return;//��֤����
	if (m_occupyOwner == owner)
		m_occupyPoint += point;
	else
	{
		if (m_occupyPoint > point)
			m_occupyPoint -= point;
		else //��ԭ�ȵ�����
		{
			m_occupyOwner = owner;
			m_occupyPoint = point - m_occupyPoint;
		}
	}
}
