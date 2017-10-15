#pragma once

#ifndef  STUDENT_H_
#define  STUDENT_H_

#include"object.h"
#include<vector>
#include"tentacle.h"
#include"definition.h"
#include"data.h"
#include"iostream"
using namespace DATA;
using namespace std;


struct StudentProperty
{
   TLA m_minLA;
   TLA m_maxLA;
   int m_maxTentacleNum;  //���������
   TSpeed m_regenarationSpeed;  //�����ٶ�
   TSpeed m_techSpeed;    //�ƴ�����
   bool m_special;        //�Ƿ�������ϸ��/tech������LA�����Ƿ����
};


class Student:public Object<Student>
{
public:
	Student();
	~Student();
	Student(const Student &);
	/*
	inline  const StudentType    getStudentType()const;
    inline  void                 setStudentType(const StudentType & _type);
	inline  const TStudentID     getId()const;
	inline  void                 setId( TStudentID _id);
	inline  const TLA            getLeftLA()const;
	inline  void                 setLeftLA(TLA);
	inline  const TCamp          getCamp()const;
	inline  void                 setCamp(TCamp _camp);
	inline  const TPoint         getPos() const;
	inline  void                 setPos(const TPoint& _point);
	inline  void                 setOccupyLA(TLA _LA);
	inline  const TLA            getOccupyLA() const;


	bool    LAempty();                  //ѧ��ֵ�Ƿ��Ϊ0
	*/
	Student(StudentType);
	
	inline  TLA              getLeftLA()           const { return m_leftLA;     }
	inline  TStudentID       getId()               const { return id;           }
	inline  TCamp            getCampID()           const { return m_campID;       }
	inline  TPoint           getPos()              const { return m_position;   }
	inline  TLA              getOccupyLA()         const { return m_occupyLA;   }
	inline  StudentType      getStudentType()      const { return m_studentType;}
	inline  StudentProperty& getStudentProperty()        { return m_property;   }
	inline  vector<TId>&      getTentacles() { return m_preTentacle; }
	inline  vector<TId>&      attackedBy() { return m_attackedBy; }

	inline  void             setOccupyLA(TLA _LA)    { m_occupyLA = _LA; }
	inline  void             setId(TStudentID _id)   { id = _id;         }
	inline  void             setLeftLA(TLA _la)      { m_leftLA = _la;   }
	inline  void             setCampID(TCamp _camp)  { m_campID = _camp; }
	inline  void             setStudentType(const StudentType & _type) { m_studentType = _type; }
	inline  void             setPos(const TPoint& _point)              { m_position = _point;   }

	bool    LAempty()     { return m_leftLA == 0; }                  //ѧ��ֵ�Ƿ��Ϊ0
	

	void    addLA();                    //ÿһ�غϺ��������Դ
	void    reduceLAForAttacked();      //��Ϊ������������ѧ��ֵ���ɱ��������Լ���ѧ��vector������
	void    reduceLAForstalemate();     //��Ϊ���Ŷ�����ѧ��ֵ,ͨ�������Լ��Ĵ���vector������ 
	bool    addTentacle(const TStudentID&);  //���Ӵ���,ѧ����������false
	bool    cutTentacle(int _id, const TPosition &);       //��ĳһ���㿳�ϴ��֣�����Ч�򿳶ϲ�����Ч,����bool

private:
	StudentType      m_studentType;      //ѧ�����࣬���е� int	
	StudentProperty  m_property;         //�ص�
	TStudentID       id;                 //ѧ��id   int

	TLA              m_leftLA;           //ʣ��ѧ��ֵ

	TLA              m_leftLA;           //ʣ��ѧ��ֵ	
	Data             m_data;             //��������
	TCamp            m_campID;           //������Ӫ  int
	TPoint           m_position;         //���ڵ��λ�õ���Ϣ
	TLA              m_occupyLA;         //����ͬѧ��ռ��ֵ
	vector<TTentacleID> m_preTentacle;   //��ǰ���ȥ�Ĵ���
	vector<TId>        m_attackedBy;    //���ڱ�����Щ���ֹ���

};

#endif // STUDENT_H_