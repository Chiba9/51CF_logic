#ifndef  STUDENT_H_
#define  STUDENT_H_

#include"object.h"
#include<vector>
#include"tentacle.h"
#include"definition.h"
#include <iostream>
#include <set>
namespace DATA
{
	class Data;
}
using namespace std;


struct StudentProperty
{
   //TLA m_minLA;
   TResourceD m_maxResource;
   int m_maxTentacleNum;  //���������
   TSpeed m_regenarationSpeed;  //�����ٶ�
   TSpeed m_techSpeed;    //�ƴ�����
   bool m_special;        //�Ƿ�������ϸ��/tech������LA�����Ƿ����
};


class Student:public Object<Student>
{
public:
	Student():Object(NO_DATA),data(nullptr){}   //Ĭ�Ϲ��캯�������������Ϣ
	Student(DATA::Data* _data,TPoint pos, TCamp campid, TResourceD resource,TResourceD maxResource, bool special, TSpeed techPoint);
	~Student();
	Student(const Student &) = default;

	
	inline  TResourceD              getLeftLA()           const { return m_resource;     }

	inline  TCamp            getCampID()           const { return m_campID;       }
	inline  TPoint           getPos()              const { return m_position;   }
	inline  TResourceD              getOccupyLA()         const { return m_occupyPoint;   }
	inline  StudentType      getStudentType()      const { return m_studentType;}
	inline  StudentProperty& getStudentProperty()        { return m_property;   }
	inline  set<TId>&      getTentacles() { return m_preTentacle; }
	inline  set<TTentacleID>&      attackedBy() { return m_attackedBy; }

	inline  void             setOccupyLA(TResourceD _LA)    { m_occupyPoint = _LA; }

	inline  void             setResource(TResourceD _la)      { m_resource = _la;   }
	inline  void             setCampID(TCamp _camp)  { m_campID = _camp; }
	inline  void             setStudentType(const StudentType & _type) { m_studentType = _type; }
	inline  void             setPos(const TPoint& _point)              { m_position = _point;   }
	inline  TResourceD       totalResource();    //���ظ�ϸ����Դֵ���䴥����Դֵ

	bool    resourceEmpty()     { return m_resource <= 0; }                  //ѧ��ֵ�Ƿ��Ϊ0
	
	void    addLA();                    //ÿһ�غϺ��������Դ

	bool    addTentacle(const TStudentID&);  //���Ӵ���,ѧ����������false
	bool    cutTentacle(TId _id, TPosition pos);       //��ĳһ���㿳�ϴ��֣�����Ч�򿳶ϲ�����Ч,����bool
	void    updateProperty(bool special = false);            //���ݵ�ǰ��Դ��������
	void    changeOwnerTo(TCamp newOwner);
	void    N_addOcuppyPoint(TCamp owner, TResourceD point);  //N_ǰ׺/ֻ������ϸ���ܹ�����/����Ӧ����

private:
	StudentType      m_studentType;      //ѧ�����࣬���е� int	
	StudentProperty  m_property;         //�ص�


	TResourceD       m_resource;           //ʣ��ѧ��ֵ

	DATA::Data* const             data;             //��������
	TCamp            m_campID;           //������Ӫ  int
	TPoint           m_position;         //���ڵ��λ�õ���Ϣ
	TResourceD              m_occupyPoint;         //����ͬѧ��ռ��ֵ
	TCamp               m_occupyOwner;       //������������
	set<TTentacleID> m_preTentacle;   //��ǰ���ȥ�Ĵ���
	set<TTentacleID> m_attackedBy;    //���ڱ�����Щ���ֹ���

};

#endif // STUDENT_H_