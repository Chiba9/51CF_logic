#ifndef TENTACLE_H
#define TENTACLE_H
#include "definition.h"
#include "object.h"
namespace DATA
{
	struct Data;
}
//������ʾ��Ŀ��ͬѧ����Ч������ʱ����
struct TransEffect
{
	TId            m_targetStudent;                   //Ŀ��ͬѧ
	TId            m_sourceStudent;                   //Դͬѧ
	TResourceD     m_resourceToTarget = 0.0;          //��Ŀ�����Դ��
	TResourceD     m_resourceToSource = 0.0;          //��Դ����Դ��
	TentacleStatus m_currStatus;                      //��ǰ״̬-�����ж�����ʱ
};

class Tentacle:public Object<Tentacle>
{
private:
	const TStudentID             m_sourceStudent;              //Դͬѧ
	const TStudentID             m_targetStudent;              //Ŀ��ͬѧ
	      TentacleStatus  m_status;                     //����״̬
	const TLength         m_length;                     //���ֳ��ȣ���Դ/Ŀ�������
	const TResourceI      m_maxResource;
	      TResourceD      m_resource;                   //��ǰ��Դ      ���ж�ǰ��Ч��
	      TResourceD      m_frontResource;              //�жϺ�ǰ����Դ���жϺ���Ч��
	      TResourceD      m_backResource;               //�жϺ����Դ���жϺ���Ч��
	      TTentacleID             m_enemyTentacle;              //�Է�����
		  DATA::Data* const     data;

public:
	//�½�����
	Tentacle():Object(NO_DATA),m_sourceStudent(NO_DATA),
		m_targetStudent(NO_DATA),m_length(0),m_maxResource(0),data(nullptr){}
	Tentacle(TId source, TId target, DATA::Data* _data);
	//�жϴ��֣�positionΪ��Դϸ���������Դ��������ֵ��ʾ�Ƿ�ɹ�
	
	bool cut(TResourceD position = 0);
	//�����ƶ�
	TransEffect move();
	//��������
	TransEffect transport();
	
	bool           isTargetEnemy() const;
	const TSpeed         getExtendSpeed()   const;
	const TSpeed         getFrontSpeed()   const;
	const TSpeed         getBackSpeed()   const;
	const TSpeed         getTransportSpeed()   const;
	const TId            getTargetStudent() const { return m_targetStudent; }
	const TId            getSourceStudent() const { return m_sourceStudent; }
	      TentacleStatus getStatus()        const { return m_status; }
	const TLength        getLength()        const { return m_length; }
	      TResourceD     getResource()      const { return m_resource; }
	      TResourceD     getFrontResource() const { return m_frontResource; }
	      TResourceD     getBackResource()  const { return m_backResource; }
		  TTentacleID    getEnemyTentacle() const { return m_enemyTentacle; }
		  void           setEnemyTentacle(TId enemy) { m_enemyTentacle = enemy; }
		  void           setStatus(TentacleStatus ts) { m_status = ts; }
	      TResourceD     totalResource()const;
		  void           finish();                //�����������ֵ�һ��
};

#endif // !TENTACLE_H