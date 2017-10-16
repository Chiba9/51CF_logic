#ifndef TENTACLE_H
#define TENTACLE_H
#include "definition.h"
#include "object.h"
namespace DATA
{
	class Data;
}
//������ʾ��Ŀ��ͬѧ����Ч������ʱ����
struct TransEffect
{
	TId            m_targetStudent;                   //Ŀ��ͬѧ
	TId            m_sourceStudent;                   //Դͬѧ
	TResourceD     m_resourceToTarget = 0.0;          //��Ŀ�����Դ��
	TResourceD     m_resourceToSource = 0.0;          //��Դ����Դ��
};

class Tentacle:public Object<Tentacle>
{
private:
	const TId             m_sourceStudent;              //Դͬѧ
	const TId             m_targetStudent;              //Ŀ��ͬѧ
	      TentacleStatus  m_status;                     //����״̬
	const TLength         m_length;                     //���ֳ��ȣ���Դ/Ŀ�������
	const TResourceI      m_maxResource;
	      TResourceD      m_resource;                   //��ǰ��Դ      ���ж�ǰ��Ч��
	      TResourceD      m_frontResource;              //�жϺ�ǰ����Դ���жϺ���Ч��
	      TResourceD      m_backResource;               //�жϺ����Դ���жϺ���Ч��
	      TId             m_enemyTentacle;              //�Է�����
		  DATA::Data* const     data;

public:
	//�½�����
	Tentacle(TId source, TId target, DATA::Data* _data);
	//�жϴ��֣�positionΪ��Դϸ���������Դ��������ֵ��ʾ�Ƿ�ɹ�
	bool cut(int position = 0);
	
	//�����ƶ�
	TransEffect move();
	//��������
	TransEffect transport();
	
	bool           isTargetEnemy() const;
	const TSpeed         getExtendSpeed()   const;
	const TSpeed         getFontSpeed()   const;
	const TSpeed         getBackSpeed()   const;
	const TSpeed         getTransportSpeed()   const;
	const TId            getTargetStudent() const { return m_targetStudent; }
	const TId            getSourceStudent() const { return m_sourceStudent; }
	      TentacleStatus getStatus()        const { return m_status; }
	const TLength        getLength()        const { return m_length; }
	      TResourceI     getResource()      const { return m_resource; }
	      TResourceI     getFrontResource() const { return m_frontResource; }
	      TResourceI     getBackResource()  const { return m_backResource; }
		  void           setEnemyTentacle(TId enemy) { m_enemyTentacle = enemy; }
		  void           setStatus(TentacleStatus ts) { m_status = ts; }
		  void           finish();                //�����������ֵ�һ��
};

#endif // !TENTACLE_H