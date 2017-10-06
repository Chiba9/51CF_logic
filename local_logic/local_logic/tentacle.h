#ifndef TENTACLE_H
#define TENTACLE_H
#include "definition.h"
#include "object.h"

//������ʾ��Ŀ��ͬѧ����Ч������ʱ����
struct TransEffect
{
	TId m_targetStudent;
	TId m_
	TResourceD m_amount;
	
};

class Tentacle:public Object<Tentacle>
{
private:
	const TId m_sourceStudent;              //Դͬѧ
	const TId m_targetStudent;              //Ŀ��ͬѧ
	TentacleStatus m_status;                //����״̬
	const TLength m_length;                 //���ֳ��ȣ���Դ/Ŀ�������
	TResourceI m_resource;                  //��ǰ��Դ      ���ж�ǰ��Ч��
	TResourceI m_frontResource;             //�жϺ�ǰ����Դ���жϺ���Ч��
	TResourceI m_backResource;              //�жϺ����Դ���жϺ���Ч��

public:
	//�½�����
	Tentacle(TId source, TId target);
	//�жϴ��֣�positionΪ��Դϸ���������Դ��������ֵ��ʾ�Ƿ�ɹ�
	bool cut(int position);
	//
};

#endif // !TENTACLE_H