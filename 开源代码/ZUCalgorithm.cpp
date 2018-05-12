//                    ****************        ****          ****            *******
//                    ***************         ****          ****         ***     *****
//                             *****          ****          ****        ***          **
//                            ****            ****          ****       ***
//                          ****              ****          ****       ***
//                        ****                ****          ****       ***
//                      ****                   ****        ****         ***          **
//                    ***************           **************            ***     ****
//                   ****************B             ********   RKAX          *******     HY             
/*
   			    								   _ooOoo_                      ZUCalgorithm Inc.
												  o8888888o 
												  88" . "88 
												  (| -_- |) 
												  O\  =  /O 
											   ____/`---'\____ 
											 .'  \\|     |//  `. 
											/  \\|||  :  |||//  \ 
										   /  _||||| -:- |||||-  \ 
										   |   | \\\  -  /// |   | 
										   | \_|  ''\---/''  |   | 
										   \  .-\__  `-`  ___/-. / 
										 ___`. .'  /--.--\  `. . __ 
									  ."" '<  `.___\_<|>_/___.'  >'"". 
									 | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
									 \  \ `-.   \_ __\ /__ _/   .-` /  / 
								======`-.____`-.___\_____/___.-`____.-'====== 
												   `=---=' 
								^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
										   ���汣��       ����BUG
*/
//                       ˭�ս������˼�,�س������Լ�Ĭ;˭�ս���ȼ����,�س�������Ư����



/**

 * Copyright (C), 2018

 * File name:      zuc5.5(FINAL RELEASE)

 * Author:		   �»��� �����ϣ������������ľ �ű�  ��Members of ZUCalgorithm��             �����������У���

 * Description:    This is the final version of the AI code distributed by the team ZUCalgorithm.However,our
				   code is mainly based on the work done by the members of the Science and Technology Association of
				   the Department of Automation,Tsinghua University.We hereby sincerely thank them for their great
				   contribution	and the best chance they have offered us.

 * Team			   ZUCalgorithm

 * Slogan          ����������÷����

 * History version
				   The first series of the code��
						zuc1.0 zuc1.1 zuc1.2 zuc1.3 zuc1.4 zuc1.5 zuc1.6 zuc1.7    -2018.03.19--2018.03.30
				   The second series of the code��
						zuc2.0 zuc2.1 zuc2.2                                       -2018.03.30--2018.04.09
				   The third series of the code��
				        zuc3.0��ͼ zuc3.0 zuc3.1 zuc3.2 zuc3.2                     -2018.04.12--2018.04.26
                   The fourth series of the code��
						zuc_new.1 zuc_new.2 zuc_new.3δ��� zuc_new.4 zuc_new.5    -2018.04.28--2018.04.30
				   The fifth series of the code��
						zuc4.0 zuc4.1 zuc4.2 zuc4.3 zuc4.4 zuc4.5 zuc4.6 zuc4.7 zuc4.8 zuc4.9
																				   -2018.04.29--2018.05.05
				   The sixth series of the code��
						zuc5.0 zuc5.1 zuc5.2 zuc5.3 zuc5.4                         -2018.05.05--2018.05.07  
* notice 
					=============================================== 
					Permission is hereby granted, free of charge, to any person obtaining a copy
					of this software and associated documentation files (the "Software"), to deal
					in the Software without restriction, including without limitation the rights
					to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
					copies of the Software, and to permit persons to whom the Software is
					furnished to do so, subject to the following conditions:

					The above copyright notice and this permission notice shall be included in
					all copies or substantial portions of the Software.

					THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
					IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
					FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
					AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
					LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
					OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
					THE SOFTWARE.
					=============================================== 
																							   Last edited by Chen Huayu at 9.00pm,May 7th,2018
 **/



//                                           This is the final release of the zuc5.5 version 1
#include "ai.h"
#include "definition.h"
#include "user_toolbox.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include <fstream>
//***************����������������������أ�����μ���ת�����塱������������д������������ע�ͣ�******************************
void player_ai(Info& info);
//��ǽ�ӳɰٷֱ�
double attack_hurt_percentage(Info &info,TTowerID x);
int his_to_me(Info& info,int id);
double constrain(double x,double a,double b);
//��T1��������T2��Ҫ�Ļغ���
double arrive_round(Info& info,TTowerID T1,TTowerID T2);

// ��arrive_round�����Ͽ���������������Ĵ���  Ԥ�Ƶ���Ҫ���غ�    t1Ϊ�Է�
double coming_arrive_round(Info& info,TTowerID T1,TTowerID T2);

// ���Է���0  ����һ��Ԥ�ڱ���������1   ������������2  ���б��߷���3 ֻ������״���Ԥ��//state��д ��������  дΪ1 ���ж��ܷ�һ�����(�Կ�)
int addline_ok(Info& info,int from,int to,int state=0) ;

//�������Ļ����ȼ� 
int level(TResourceD towersource);

//������Tʵ�ʻظ�����
double real_recover_speed(Info& info,TTowerID T);

//������Tÿ�����߻�������//////�õ�real_recover_speed����  method ��д����ʹ�� �������Ϊ1�򷵻ؼ�������һ�����߱��ߵ�speed
double base_speed(Info& info,TTowerID T,int method=0);

//��T1����T2ÿ�غ���ɵ��˺�///////�õ�base_speed����
double attack_consume(Info& info,TTowerID T1,TTowerID T2,int method=0);

//�������ڶԿ���line����������
double confront_consume(Info& info,LineInfo line);
//�����������t1 �� t2 �Կ� ��������
double confront_consume(Info& info,TTowerID T1,TTowerID T2);
int player_towernum(Info& info,int id);
//������T��ǰÿ�غϾ�������Դ�������ǻָ���.// ��Դ���� ��������
double each_round_consume(Info& info,TTowerID T);
double all_resource(Info& info);
double player_resource(Info& info,int id);
double line_resource(Info &info,int tower);
//��T1����T2���ɲ����ԡ�������  �õ�arrive_round��each_round_consume����   ***û�п��Ƕ����жϱ��߿����� ����  method=1 �ر��tiaodou_cut_act����
void budao_evaluate_plus(Info& info,TTowerID T1,TTowerID T2,int method=0);
double budao_evaluate_new(Info& info,TTowerID T1,TTowerID T2);
void budao_brain(Info& info);
void help_brain(Info& info);
// ���������֣� ���ֺ���
double fightback(Info& info,TTowerID myT,TTowerID hisT);
//һ������attack ����ȫ���칥 ����ɶ���˺�  �������Ƕ��ҵ���������
double bomb1(Info& info,TTowerID a);
//�Ѻõ�bomb  ����ҷ���ʹ��
double bomb2(Info& info,TTowerID a);
//����  ����
double help_friend(Info& info,TTowerID giveT,TTowerID needT);
double help_friend_new(Info& info,TTowerID giveT,TTowerID needT);
//���Ѵ��ڵ��ҷ����ߣ�Ԯ��/�ù����£��Ƿ��жϵ�����
double helporattack_line_cut(Info& info,LineInfo line);

//���Կ칥
void kuai_gong(Info& info,TTowerID hisT);

//���Կ칥
double kuai_gong(Info& info,TTowerID from,TTowerID to);

//�������ڹ�����ѹ��/���ţ���T�ķ��ҷ�������
int others_attacking(Info& info,TTowerID T);

//�ж���tnum�Ƿ��Ƿ��ҷ��������ڹ�����ѹ��/���ţ���T,���ǹ��� ����1�����Ƕ��ţ�����2�����򷵻�0
int others_attacking_judge(Info& info,TTowerID T,TTowerID tnum);

// �ж�һ���з����ܲ��ܱ���ը��  ����0��Ϊ��ʱû�п���  ���򷵻�1
int can_it_be_bombed(Info& info,TTowerID x);

//��������ֵ
double propertychange(Info& info,int upgradetype);
double song_le(Info& info,LineInfo line);
//strategyΪ�����������Ĳ������ࣻ
double strategychange(Info& info,TTowerID id,int afterstrategy);
//�ı䱾���Ĳ���ֵ
double strategychange0(Info& info,TTowerID id,int nowstrategy);
double strategychange1(Info& info,TTowerID id,int nowstrategy);
double strategychange2(Info& info,TTowerID id,int nowstrategy);
double strategychange3(Info& info,TTowerID id,int nowstrategy);

// ���ظ������� ����(���ŵ�����)  �����ж� ��
int his_confront_lines_num(Info& info,TTowerID x);

//����:T1�Ƿ��ж�Ԯ���߰���T2
double help_bomb_evaluate(Info& info,TTowerID T1,TTowerID T2);

//    ����ļ�txt��ֻ�ڵ��Ե��Կ���  �Զ���ÿһ�����������ӻ��з�
void fileout(const char *a,const char *name="mylog.txt");
void fileout(const char *a,double b,const char *name="mylog.txt");
void fileout(const char *a,int b,const char *c,const char *name="mylog.txt");
void fileout(int a,const char *c,int b,const char *name="mylog.txt");
void fileout(double a,const char *name="mylog.txt");
void fileout(int a,const char *name="mylog.txt");

void fileoutteaminfo(Info& info);


//ͳ��ѡ��1  �� ѡ��2 �ı�������  ע�ⲻ��line������owner��ͬ��������Ϊ���Ż�ѹ��״̬������Ϊ�������� ���������û����

void baoshou_xingwei(Info& info,TTowerID i,int method=0);
void jijin_xingwei(Info& info,TTowerID i,int method=0);
//ռ������ս��ģ��
void touzhongta_tiaojianpanduan(Info& info);
void touzhongta_xingwei(Info& info,TTowerID x);
void tiaodou_xingwei(Info& info,TTowerID x);
void jizhonggongji_xingwei(Info& info,TTowerID x);
void choice_enermy(Info& info);
int choice_enermy1(Info& info,int line);

double money(Info& info,TTowerID x);

void commandcheck(Info &info);

//�ҵ����й������ô�����
void jizhonggongji_members_find(Info& info);

//�����й�������С��
void jizhonggongji_squrds_find(Info& info);


//���ĳ��Ա����ɽ��������������˳�����
void squrds_weihu(Info& info);

//*****����ִ��******0 ʧ�� 1�ɹ�
int act(Info& info);
//*******��ta��Ϊ��λ����  Ϊplayer ai��ѹ
void toweract(Info& info,TTowerID i);
//***���߼���ʼ�� don't mind
void init(Info& info);

//����cutline����,ͬʱά��lines_index���fightback
double fightback_lines_control(Info& info,TTowerID t,TTowerID target);
double zaqizaba_cut(Info& info,TTowerID x,TTowerID i);
void stagechange(Info& info);
int gamebegin(Info& info);
void lines_for_towers_init(Info& info);

double tiaodou_cut(Info& info,TTowerID t,TTowerID target);
double tiaodou_addline(Info& info,TTowerID t,TTowerID target);

int panduan_lineindex(Info& info,TTowerID j,TTowerID k);
void gou_xingwei(Info& info,int i);
int rank_judge(Info& info);
void lines_weihu(Info& info);
//**********************ȫ�ֱ���������**********************************
enum Tower_way
{
	baoshou,
	jijin,
	touzhongta,
	xiyinhuoli,
	jizhonggongji,
	gou
};
enum Evaluate_names 
{
	budao_score,
	fightback_score,
	help_score,
	tiaodou,

	jiugongbuxia_score,
	help_bomb_score,
	kuaigong_score,
	fightback_control_score,
	gang,
	noline
};
enum Stage
{
	qianqi,
	houqi
};
double _evaluate[4][13][13];
double songle_cengci;
double _added_lines_round[13][13][3]; //�洢��ӱ���ʱ�Ļغ�����Ŀ������Դ
double kuaigong_cengci;
double _kuaigong_recommend[13][13]; //��¼�칥����
double _cutline_weizhi[13][13];
const int _tower_basic_way[13]={0,0,0,0,0,0,0,0,0,0,0,0,jijin};
int _tower_way_index[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
int _touzhongta_xingwei_index;
int _is_for_tiaodou_porpose[13][13];
int _quyugongji_count=0;
int _tiaodou_xingwei_index=0;
int _tiaodou_use_once=0;
int _jizhonggongji_xingwei_index[13];
int _jizhonggongji_xingwei_usecount[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
const int quyu[13]={0,0,0,1,1,1,2,2,2,3,3,3,4};
int jizhonggongji_daifenpei[13]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};
int _last_round_tower_owner[13];
double _last_round_resource[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
int _danger_line[13];
int _budao_line[13];
int _budao_attack_round=0;
int _budao_vice_attack_round=0;
int _my_now_vice_target=-1;
double _budao_brain_outcome[13][13];
double _help_brain_outcome[13][13];
int _budao_vice_fenpei_log[500];
int _budao_fenpei_log[500];
int _tar_giveup_log[500];
int _begin=0;
int stragtegy[13][4];
int _badluck[6]={-1,-1,-1,-1,-1,-1};
struct Squad
{
	int be_using;//-1�����壬0�ǵȴ�������ˣ�1�����ڱ�ʹ��
	int member_num;
	int members[14];
	int members_state[14];  //0����δ���� 1���Ѿ�������һ��
	int target;
};
struct Squad squads[5];
#define _times_fightback 4
#define _times_budao_evaluate 2
#define _times_help_friend 1
#define _times_song_le 5
#define _times_helporattack_line_cut 1
#define _times_kuai_gong 5
#define _times_strategychange 3
#define _times_help_bomb 3    //��ʾ����
#define _times_fightback_cut 1
#define _times_zaqizaba_cut 1
#define _times_tiaodou 1
#define _times_tiaodou_cut 1
#define fence 65
#define BUDAO_BEGIN_ROUND 30
//����_evaluate_detailʱָ�����֣�����lines_indexʱָ����������
#define _evaluate_names_len 9
double _evaluate_detail[4][13][13][10];//��¼ÿ��evaluate������ϸ��,ֻ��¼���ػ򼤽���
double _lines_index[13][13];  //��¼ÿ�����ߵ�����
int gangcount[13][13];
int _my_now_budao_target=-1;
double _budao_evaluate_reference[13][13][2];
int _xiyinhuoli_bengin=0;
Stage stage=qianqi;
//                                           This is the final release of the zuc5.5 version 2
//****************************��������*****************************************************************************
void player_ai(Info& info)
{
	init(info);
	fileout("***********",info.round,"************","kuaigong.txt");
	//fileout("round******************",info.round,"******************");	
	stagechange(info);
	for (int i = 0; i < 13; i++)
		if(_last_round_tower_owner[i]==info.myID&&info.towerInfo[i].owner!=info.myID)
			_tower_way_index[i]=_tower_basic_way[i];
	lines_weihu(info);
	if(info.round<=12)
		touzhongta_tiaojianpanduan(info);    

	if(info.round<=25&&info.towerInfo[12].owner==info.myID&&_tiaodou_use_once==0)
	{
		_tower_way_index[12]=xiyinhuoli;//���䲻�ȶ�
		_tiaodou_xingwei_index=0;
		_tiaodou_use_once=1;
	}

	fileoutteaminfo(info);

	for(int i=0;i<4;i++)
	{
		_evaluate[upgrade][i][0]+=propertychange(info,i);
		//fileout ("sort",i);
		//fileout ("_evaluate[upgrade][i][0]", int (_evaluate[upgrade][i][0]),"****");
	}

	for(int i=0;i<13;i++)
		toweract(info,i);

	commandcheck(info);

	int tt=0;
	for(int count=1;count<=info.myMaxControl;count++)
		tt+=act(info);
	fileout(tt,"in",info.myMaxControl,"kuaigong.txt");
	// �Ϸ��Լ�飿
	//fileout("round!!!!",info.round,"d","control.txt");
	//fileout("max",info.myMaxControl,"d","control.txt");
	//fileout("use",info.myCommandList.size(),"d","control.txt");
	//��ϣ��Ӯ������
	if(rank_judge(info)==0)
	{
		/*ofstream log("gou.txt",ios::app);
		log<<"round"<<info.round<<endl;
		log.close();*/

		for(int i=0;i<13;i++)
			_tower_way_index[i]=gou;
	}
	for (int i = 0; i < 13; i++)
	{
		_last_round_tower_owner[i]=info.towerInfo[i].owner;
		_last_round_resource[i]=info.towerInfo[i].resource;
	}
}

//**********************************����������**********************************************
//******************************���߼���ʼ�� don't mind
void init(Info& info)
{
	srand(time(0));
	kuaigong_cengci=-1;
	songle_cengci=-0.5;
	if(info.round==0)
		for (int i = 0; i < 500; i++)
		{
			_budao_vice_fenpei_log[i]=-1;
			_budao_fenpei_log[i]=-1;
			_tar_giveup_log[i]=-1;
		}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			for (int k = 0; k < 13; k++)
			{
				_evaluate[i][j][k]=0;

				for(int m=0;m<_evaluate_names_len;m++)
					_evaluate_detail[i][j][k][m]=0;
			}
		}
	}
	if(info.round==0)
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				stragtegy[i][j]=-1;
			}
		}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			_budao_evaluate_reference[i][j][0]=0;
			_budao_evaluate_reference[i][j][1]=0;
			_budao_brain_outcome[i][j]=0;
			_help_brain_outcome[i][j]=0;
		}
	}
	budao_brain(info);
	help_brain(info);
	if(info.round==0) //helporattack����added_lines_round�ĳ�ʼ��
	{
		for(int i=0;i<13;i++)
		{
			for(int j=0;j<13;j++)
			{
				_added_lines_round[i][j][0]=302;
				_added_lines_round[i][j][1]=0;
				_added_lines_round[i][j][2]=0;
				_is_for_tiaodou_porpose[i][j]=0;
			}
		}
	}
	if(_my_now_budao_target==-1)
		_budao_attack_round=0;
	else
		_budao_attack_round++;
	if(_my_now_vice_target==-1)
	{
		for (int m = 0; m < 13; m++)
			jizhonggongji_daifenpei[m]=-1;
		_budao_vice_attack_round=0;		
	}
	else
		_budao_vice_attack_round++;
	lines_for_towers_init(info);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			for (int k = 0; k < 13; k++)
			{
				_kuaigong_recommend[j][k]=0;
				_evaluate[i][j][k]=0;
			}
		}
	}

	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner!=info.myID)
			kuai_gong(info,i);
	}
	if(info.round==0)
	{
		for(int i=0;i<13;i++)
			for(int j=0;j<13;j++)
				_lines_index[i][j]=noline;
	}
	if(info.round==0)
	{
		int a=0;
		int b=2;
		int c=4;
		int dis=0;
		for (int i = 0; i < 13; i++)
		{
			dis=getDistance(info.towerInfo[info.myID].position,info.towerInfo[i].position);
			if(dis<645&&dis>635)
			{
				_badluck[a]=i;
				a=3;
			}
			else if(dis<540&&dis>535)
			{
				_badluck[b]=i;
				b=1;
			}
			else if(dis>410&&dis<415)
			{
				_badluck[c]=i;
				c=5;		
			}
		}
	}
}
void lines_weihu(Info& info)
{
	//�Գ�Ա�ĸ���
	if(info.round!=0)
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if(i==j||info.towerInfo[i].owner==-1||info.towerInfo[j].owner==-1)
				{
					_lines_index[i][j]=noline;      //͵����û������line��Ȼ��noline
					continue;
				}
				if(info.lineInfo[i][j].exist==1&&info.lineInfo[i][j].state!=AfterCut)
				{
					if(info.towerInfo[i].owner==info.myID&&info.towerInfo[j].owner!=info.myID&&info.towerInfo[j].owner!=-1)
					{
						if((j==_my_now_vice_target||j==_my_now_budao_target)&&info.towerInfo[i].resource>_danger_line[i]+10)
							_lines_index[i][j]=noline;
						else if(j==_my_now_vice_target||j==_my_now_budao_target)
						{
							if(each_round_consume(info,i)<2)
								_lines_index[i][j]=gang;
							else
								_lines_index[i][j]=fightback_score;
						}
						else if(_lines_index[i][j]==noline)
							_lines_index[i][j]=fightback_score;
					}
					else
						_lines_index[i][j]=noline;
				}
				else
					_lines_index[i][j]=noline;
			}
		}		
	
	//line�Ļ����Ϸ��Ե��˽��� ���洦���noline�� ȫ��Ϊ����Ե��� �иõ��˲����ҵ�Ŀ�� ����ֻ���Ƿ������ʻ���������
	//����һ��Ϊ�������� ��̫���ܷ���ת���� ����ת���� Ҳ��̫��������ת���� ���ת���� �����Ѿ�ת�˱��˶������������Ȼ����������������Ȼcut
	//���ֻ��Ҫ��������֮���໥ת����  ���ڱ������ ����дһ������ת���� ����Ҫд�պ��Ƶ�ת��

		for (int i = 0; i < 13; i++)
		{
			int count=0;
			for (int k = 0; k < 13; k++)
				if(info.towerInfo[k].owner!=info.myID&&info.lineInfo[k][i].exist==1&&info.lineInfo[k][i].state!=AfterCut&&info.lineInfo[k][i].resource*10>=info.lineInfo[k][i].maxlength/2.0+10)
					count++;
			for (int j = 0; j < 13; j++)  //�ȶ�12�� д�ñ���ά��������
			{
				if(_lines_index[i][j]==noline)
					continue;//��ʱһ�������ҵ�Ҫ�� ��һ���ҷ�����һ�����ҷ��ǹ���Ŀ��������Ч����
				if(_lines_index[i][j]==fightback_score)
				{
					if(count>=info.towerInfo[i].maxLineNum)
						continue;
					if(player_towernum(info,info.myID)<=4)
						continue;
					if(info.playerInfo[info.myID].rank>=3)
						continue;
					if(info.towerInfo[i].resource<_danger_line[i]+15)
						continue;
					if(_tower_way_index[i]==gou||i==12)
						continue;
					if(bomb1(info,i)*2>info.towerInfo[i].resource)
						continue;
					if(!(info.towerInfo[i].strategy==Attack&&(info.towerInfo[j].strategy==Grow||info.towerInfo[j].strategy==Normal)))
						if(!(info.towerInfo[i].strategy==Defence&&info.towerInfo[j].strategy==Attack))
							if(!(info.towerInfo[i].strategy==Grow&&info.towerInfo[j].strategy==Normal))
								if(info.towerInfo[i].resource<0.9*info.towerInfo[i].maxResource)
									continue;
					if(info.towerInfo[i].resource<0.9*info.towerInfo[i].maxResource&&info.towerInfo[i].resource>info.towerInfo[j].resource)
					{
						_lines_index[i][j]=gang;
						continue;
					}
					if(info.towerInfo[i].resource>0.9*info.towerInfo[i].maxResource&&info.towerInfo[i].resource-50>info.towerInfo[j].resource)
					{
						_lines_index[i][j]=gang;
						continue;
					}
				}
				if(_lines_index[i][j]==gang)
				{
					if(!(info.towerInfo[i].strategy==Attack&&(info.towerInfo[j].strategy==Grow||info.towerInfo[j].strategy==Normal)))
						if(!(info.towerInfo[i].strategy==Defence&&info.towerInfo[j].strategy==Attack))
							if(!(info.towerInfo[i].strategy==Grow&&info.towerInfo[j].strategy==Normal))
								if(info.towerInfo[i].resource<0.65*info.towerInfo[i].maxResource||(info.towerInfo[i].resource-30<info.towerInfo[j].resource))
								{
									_lines_index[i][j]=fightback_score;
									continue;								
								}
					if(count>=info.towerInfo[i].maxLineNum||player_towernum(info,info.myID)<=4||info.playerInfo[info.myID].rank>=3||info.towerInfo[i].resource<_danger_line[i]+15||_tower_way_index[i]==gou||i==12||bomb1(info,i)*1.8>info.towerInfo[i].resource)
					{
						_lines_index[i][j]=fightback_score;
						continue;
					}
					if(gangcount[i][j]>17)
					{
						_lines_index[i][j]=fightback_score;
						continue;
					}
				}
			}
		}
	}
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
		{
			if(_lines_index[i][j]!=gang)
				gangcount[i][j]=0;
			else
				gangcount[i][j]++;
		}
	return;
}
int xiyinhuoliopen(Info& info)
{

	if(info.round<20||info.round>50||info.towerInfo[12].owner!=info.myID||info.towerInfo[12].strategy!=Attack)
	{
		return -1;
	}
	if(info.towerInfo[12].resource<20)
		return -1;
	if(info.towerInfo[12].currLineNum>=info.towerInfo[12].maxLineNum)
		return -1;
	for (int i = 0; i < 12; i++)
	{
		if(_lines_index[12][i]==fightback_score)
			return -1;
	}
	int coun=0;
	for (int i = 0; i < 12; i++)
	{
		if(info.towerInfo[i].owner!=info.myID&&info.lineInfo[i][12].exist==1&&info.lineInfo[12][i].exist==0&&coming_arrive_round(info,i,12)<3)
			coun++;
		else if(info.towerInfo[i].owner!=info.myID&&info.lineInfo[i][12].exist==1&&info.lineInfo[12][i].exist==1&&info.lineInfo[i][12].state!=AfterCut)
			coun++;
	}
	if(coun>=2)
		return -1;
	int t=0;
	int tem=0;
	for (int t = 0; t < 6; t++)
	{
		if(_badluck[t]!=-1&&info.towerInfo[_badluck[t]].strategy==Grow&&info.towerInfo[_badluck[t]].owner!=info.myID&&info.lineInfo[12][_badluck[t]].exist==0&&info.lineInfo[_badluck[t]][12].exist==0)
		{
			tem=_badluck[t];
			_badluck[t]=-1;
			return(tem);
		}
	}
	return -1;
}
void stagechange(Info& info)
{
	int count=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
			count++;
	}
	if(stage==qianqi)
	{
		if(count>=6&&info.playerInfo[info.myID].rank==1)
		{
			stage=houqi;
			fileout("stagechange","stagechange.txt");
			return;
		}
		if(info.playerInfo[info.myID].rank==0)
			fileout("rank","error.txt");
	}
}
//***********************����ִ��*************0 ʧ�� 1�ɹ�
int act(Info& info)
{
	double check=0;//ÿ����ÿ�غ����һ����
	for (int j = 0; j < 13; j++)
	{
		if(info.round<70&&j==12)   //���������̵�
			continue;
		check=0;
		for (int i = 1; i < 4; i++)
		{
			for (int k = 0; k < 13; k++)
			{
				if(_evaluate[i][j][k]>check)
					check=_evaluate[i][j][k];
			}
		}
		for (int i = 1; i < 4; i++)
		{
			for (int k = 0; k < 13; k++)
			{
				if(_evaluate[i][j][k]<check-0.0001)
					_evaluate[i][j][k]=0;
			}
		}
	}
	double comp=0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			for (int k = 0; k < 13; k++)
			{
				if(_evaluate[i][j][k]>comp)
					comp=_evaluate[i][j][k];
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			for (int k = 0; k < 13; k++)
			{
				if(_evaluate[i][j][k]>fence&&_evaluate[i][j][k]>comp-0.001&&_evaluate[i][j][k]<comp+0.001)
				{
					switch(i)
					{
					case 0:
						info.myCommandList.addCommand(upgrade,j);
						fileout("upgrade:",j);
						break;
					case 1:
						info.myCommandList.addCommand(changeStrategy,j,k);
						fileout("changeStrategy:",k);
						break;
					case 2:
						info.myCommandList.addCommand(addLine,j,k);
						_added_lines_round[j][k][0]=double(info.round)+arrive_round(info,j,k);
						_added_lines_round[j][k][1]=double(info.towerInfo[j].resource);
						_added_lines_round[j][k][2]=double(info.round);

						if(panduan_lineindex(info,j,k)==fightback_score)
						{
							//fileout("fightback_score",_evaluate_detail[addLine][j][k][fightback_score]);
							//fileout(_evaluate_detail[addLine][j][k][budao_score]);
							//fileout(_evaluate_detail[addLine][j][k][help_score]);
							//fileout(_evaluate[i][j][k]);
							//fileout(info.round);
							//fileout(j);
							//fileout(k);
							_lines_index[j][k]=fightback_score;
						}
						else if(panduan_lineindex(info,j,k)==tiaodou)
						{
							_lines_index[j][k]=tiaodou;
						}

						break;
					case 3:
						//fileout(k);
						if(_is_for_tiaodou_porpose[j][k]==1)
							_is_for_tiaodou_porpose[j][k]=0;
						info.myCommandList.addCommand(cutLine,j,k,_cutline_weizhi[j][k]);
						fileout("cutline: ",j,"to");
						fileout(k);
						break;
					default:
						fileout("sfasfsaggg","error.txt");
					}
					_evaluate[i][j][k]=-1;
					return(1);
				}
			}
		}
	}
	return 0;
}

void toweract(Info& info,TTowerID i)
{
	if(info.towerInfo[i].owner!=info.myID)
		return;

	double gap=0;
	double consume=each_round_consume(info,i);
	switch(_tower_way_index[i])
	{
	case baoshou:
		baoshou_xingwei(info,i);
		break;

	case jijin:
		jijin_xingwei(info,i);
		break;

	case touzhongta:
		touzhongta_xingwei(info,i);
		break;

	case xiyinhuoli:
		tiaodou_xingwei(info,i);
		break;

	case jizhonggongji:
		jizhonggongji_xingwei(info,i);
		break;

	case gou:
		gou_xingwei(info,i);
		break;
	}
}

void baoshou_xingwei(Info& info,TTowerID i,int method)
{
	double power=(info.towerInfo[i].maxResource)/200.00;
	int gap=0;
	for(int j=0;j<13;j++)
		if(_added_lines_round[i][j][2]>gap)		
			gap=_added_lines_round[i][j][2];
	gap=info.round-gap;
	double tem;
	double consume=each_round_consume(info,i);

	for (int j = 0; j < 4; j++)			
		_evaluate[changeStrategy][i][j]+=((tem=strategychange(info,i,j))>fence)?tem*(_times_strategychange+1):0.99;

	for (int j = 0; j < 13; j++)  
	{
		if(info.towerInfo[j].owner==-1||i==j)
			continue;
		if(info.towerInfo[j].owner!=info.myID)
		{
					double score=0;
					_evaluate[addLine][i][j]+=((tem=budao_evaluate_new(info,i,j))>fence)?(score=(tem*_times_budao_evaluate)):(score=0.98);
					_evaluate_detail[addLine][i][j][budao_score]=score;

			 score=0;
			_evaluate[addLine][i][j]+=((tem=fightback(info,i,j))>fence)?(score=(tem*_times_fightback)):(score=0.99);
			_evaluate_detail[addLine][i][j][fightback_score]=score;

			double score2=0;
			_evaluate[addLine][i][j]+=((tem=tiaodou_addline(info,i,j))>fence)?(score2=tem*_times_tiaodou):(score2=0.99);
			_evaluate_detail[addLine][i][j][tiaodou]=score2;

		}
		if(info.towerInfo[j].owner==info.myID)
		{
				double score=0;
				_evaluate[addLine][i][j]+=((tem=help_friend_new(info,i,j))>fence)?(score=tem*_times_help_friend):(score=0.97);
				_evaluate_detail[addLine][i][j][help_score]=score;
		}
	}

	for (int j = 0; j < 13; j++)
	{
		if(info.towerInfo[j].owner==-1||i==j)    //���������������Ժ�Ҫ��
			continue;
		if(info.lineInfo[i][j].exist&&info.lineInfo[i][j].state!=AfterCut)
		{
			double kuaigong_score=0;
			double helporattack_score=0;
			double songle_score=0;
			double help_bomb_score=0;
			double fightback_cut_score=0;
			double zaqizaba_cut_score=0;
			double tiaodou_cutscore=0;

			if(info.towerInfo[j].owner!=info.myID&&info.lineInfo[j][i].exist==0&&info.lineInfo[i][j].state==Arrived)
			{
				kuaigong_score=kuai_gong(info,i,j);
			}

			//helporattack_score=helporattack_line_cut(info,info.lineInfo[i][j]);	
			                            //��ر���Ҫ��˳��  ����
			songle_score=song_le(info,info.lineInfo[i][j]); 

			tiaodou_cutscore=tiaodou_cut(info,i,j);

			if(info.towerInfo[j].owner==info.myID&&info.lineInfo[j][i].exist==0&&info.lineInfo[i][j].state==Arrived)
			{
				help_bomb_score=help_bomb_evaluate(info,i,j);
			}
			
			if(info.towerInfo[i].owner==info.myID&&info.towerInfo[j].owner!=info.myID&&info.lineInfo[i][j].exist==1)
				fightback_cut_score=fightback_lines_control(info,i,j);	

			if(info.towerInfo[i].owner==info.myID)
				zaqizaba_cut_score=zaqizaba_cut(info,i,j);

			_evaluate[cutLine][i][j]+=(songle_score>fence)?(songle_score=songle_score*_times_song_le):(songle_score=0.95);
			_evaluate[cutLine][i][j]+=(helporattack_score>fence)?(helporattack_score=helporattack_score*_times_helporattack_line_cut):(helporattack_score=0.94);
			_evaluate[cutLine][i][j]+=(kuaigong_score>fence)?(kuaigong_score=kuaigong_score*_times_kuai_gong):(kuaigong_score=0.93);
			_evaluate[cutLine][i][j]+=(help_bomb_score>fence)?(help_bomb_score=help_bomb_score*_times_help_bomb):(help_bomb_score=0.92);
			_evaluate[cutLine][i][j]+=(fightback_cut_score>fence)?(fightback_cut_score=fightback_cut_score*_times_fightback_cut):(fightback_cut_score=0.90);
			_evaluate[cutLine][i][j]+=(zaqizaba_cut_score>fence)?(zaqizaba_cut_score=zaqizaba_cut_score*_times_zaqizaba_cut):(zaqizaba_cut_score=0.56);
			_evaluate[cutLine][i][j]+=(tiaodou_cutscore>fence)?(tiaodou_cutscore=tiaodou_cutscore*_times_tiaodou_cut):(tiaodou_cutscore=0.56);
			/*ofstream log("cut.txt",ios::app);
			log<<"***"<<info.round<<"***"<<endl;
			log<<i<<","<<j<<endl;
			log<<"songle_score"<<songle_score<<"helporattack_score"<<helporattack_score<<"kuaigong_score"<<kuaigong_score<<"help_bomb_score"<<help_bomb_score<<"fightback_cut_score"<<fightback_cut_score<<
				"zaqizaba_cut_score"<<zaqizaba_cut_score<<endl;
			log.close();*/
			//	fileout(i,"to kuaigong",j,"kuaigong.txt");
			//	fileout(kuaigong_score,"kuaigong.txt");
			int s1=(kuaigong_score>helporattack_score&&kuaigong_score>songle_score&&kuaigong_score>fightback_cut_score&&kuaigong_score>zaqizaba_cut_score&&kuaigong_score>tiaodou_cutscore);
			int s2=(help_bomb_score>helporattack_score&&help_bomb_score>songle_score&&help_bomb_score>fightback_cut_score&&help_bomb_score>zaqizaba_cut_score&&help_bomb_score>tiaodou_cutscore);

			if(s1||s2)
				_cutline_weizhi[i][j]=0;
			else
				_cutline_weizhi[i][j]=info.lineInfo[i][j].resource-0.001;

				//fileout(i,"to",j);
				//fileout("_evaluate[cutLine][i][j]   ",int(_evaluate[cutLine][i][j]),"*****");
			}
	}

}

void jijin_xingwei(Info& info,TTowerID i,int method)
{
	if(method==1)
	{
		fileout("jijin","error.txt");
	}
	double power=(info.towerInfo[i].maxResource)/200.00;
	double gap=0;
	double tem;
	double consume=each_round_consume(info,i);
		for (int j = 0; j < 4; j++)
		{
			_evaluate[changeStrategy][i][j]+=((tem=strategychange(info,i,j))>fence)?tem*_times_strategychange:0.99;
		}

		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner==-1||i==j)
				continue;
			if(info.towerInfo[j].owner!=info.myID)
			{
				if(method==0)
				{
					double score=0;
					double budao;
					budao=budao_evaluate_new(info,i,j);
					_evaluate[addLine][i][j]+=((tem=budao)>fence)?score=(tem*_times_budao_evaluate):score=0.98;
					_evaluate_detail[addLine][i][j][budao_score]=score;

				}

				double score=0;

				_evaluate[addLine][i][j]+=((tem=fightback(info,i,j))>fence)?score=(tem*_times_fightback):score=0.99;
				_evaluate_detail[addLine][i][j][fightback_score]=score;

				double score2=0;
				_evaluate[addLine][i][j]+=((tem=tiaodou_addline(info,i,j))>fence)?(score2=tem*_times_tiaodou):(score2=0.99);
				_evaluate_detail[addLine][i][j][tiaodou]=score2;
			}


			if(info.towerInfo[j].owner==info.myID)
			{
				double score=0;

				_evaluate[addLine][i][j]+=((tem=help_friend_new(info,i,j))>fence)?score=(tem*_times_help_friend):score=0.97;
				_evaluate_detail[addLine][i][j][help_score]=score;
			}

		}

//                                           This is the final release of the zuc5.5 version 3
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner==-1||i==j)    //���������������Ժ�Ҫ��
				continue;
			if(info.lineInfo[i][j].exist&&info.lineInfo[i][j].state!=AfterCut)
			{
				double kuaigong_score=0;
				double helporattack_score=0;
				double songle_score=0;
				double help_bomb_score=0;
				double fightback_cut_score=0;
				double zaqizaba_cut_score=0;
				double tiaodou_cutscore=0;
				if(info.towerInfo[j].owner!=info.myID)
				{
					kuaigong_score=kuai_gong(info,i,j);
					fightback_cut_score=fightback_lines_control(info,i,j);
				}

				helporattack_score=helporattack_line_cut(info,info.lineInfo[i][j]);	
				songle_score=song_le(info,info.lineInfo[i][j]);                             //��ر���Ҫ��˳��  ����

				if(info.towerInfo[j].owner==info.myID)
					help_bomb_score=help_bomb_evaluate(info,i,j);


					zaqizaba_cut_score=zaqizaba_cut(info,i,j);
					tiaodou_cutscore=tiaodou_cut(info,i,j);

				_evaluate[cutLine][i][j]+=(songle_score>fence)?(songle_score=songle_score*_times_song_le):(songle_score=0.95);
				_evaluate[cutLine][i][j]+=(helporattack_score>fence)?(helporattack_score=helporattack_score*_times_helporattack_line_cut):(helporattack_score=0.94);
				_evaluate[cutLine][i][j]+=(kuaigong_score>fence)?(kuaigong_score=kuaigong_score*_times_kuai_gong):(kuaigong_score=0.93);
				_evaluate[cutLine][i][j]+=(help_bomb_score>fence)?(help_bomb_score=help_bomb_score*_times_help_bomb):(help_bomb_score=0.92);
				_evaluate[cutLine][i][j]+=(fightback_cut_score>fence)?(fightback_cut_score=fightback_cut_score*_times_fightback_cut):(fightback_cut_score=0.92);
				_evaluate[cutLine][i][j]+=(zaqizaba_cut_score>fence)?(zaqizaba_cut_score=zaqizaba_cut_score*_times_zaqizaba_cut):(zaqizaba_cut_score=0.56);
				_evaluate[cutLine][i][j]+=(tiaodou_cutscore>fence)?(tiaodou_cutscore=tiaodou_cutscore*_times_tiaodou_cut):(tiaodou_cutscore=0.56);
				
				//fileout(i,"to kuaigong",j,"kuaigong.txt");
				//fileout(kuaigong_score,"kuaigong.txt");
				int s1=(kuaigong_score>helporattack_score&&kuaigong_score>songle_score&&kuaigong_score>fightback_cut_score&&kuaigong_score>zaqizaba_cut_score&&kuaigong_score>tiaodou_cutscore);
				int s2=(help_bomb_score>helporattack_score&&help_bomb_score>songle_score&&help_bomb_score>fightback_cut_score&&help_bomb_score>zaqizaba_cut_score&&help_bomb_score>tiaodou_cutscore);


				if(s1||s2)
					_cutline_weizhi[i][j]=0;
				else
					_cutline_weizhi[i][j]=info.lineInfo[i][j].resource;

			}

		}
}

void touzhongta_tiaojianpanduan(Info& info)
{
	if(info.round<=12&&(info.towerInfo[info.myID*3+1].strategy==Grow||info.towerInfo[info.myID*3+2].strategy==Grow))
	{
		int tem=0;
		int count=0;
		int gg=-1;  //-1 doubuxing  -2douxing >=0 wei xingdeid
		int bla[2];
		for(int i=0;i<12;i++)
		{
			if(info.lineInfo[i][12].exist==0)
				count++;
		}
		if(count==12)
		{
			for (int i = 0; i < 12; i++)
			{
				if(info.towerInfo[i].owner==info.myID&&i%3!=0&&addline_ok(info,i,12)==0&&info.towerInfo[i].strategy==Grow)
				{
					for (int j = 0; j < 12; j++)
					{
						if(info.towerInfo[i].owner==info.towerInfo[j].owner)
							continue;
						if(info.lineInfo[j][i].exist==1)
							tem=1;
					}
					if(tem==0)
					{
						if(gg==-1)
						{
							gg=i;
							bla[0]=i;
						}
						else if(gg>=0)
						{
							gg=-2;
							bla[1]=i;
						}
						else gg=-2;
					}
					else
						tem=0;
				}
			}
			if(gg>=0)
			{
				_tower_way_index[gg]=touzhongta;
				_touzhongta_xingwei_index=0;
				return;
			}
			else if(gg==-2)
			{
				srand(time(0));
				int k=rand()%2;
				_tower_way_index[bla[k]]=touzhongta;
				_touzhongta_xingwei_index=0;
				return;
				if(bla[0]<0||bla[1]<0||bla[1]>11||bla[0]>11||(bla[0]==bla[1]))
					fileout("serious!!!!!!!!!!!!!!!!!","error.txt");
			}
			else
				return;
		}
		else
			return;
	}
	else 
		return;
	return;
}
//                                           This is the final release of the zuc5.5 version 4
void touzhongta_xingwei(Info& info,TTowerID x)
{
	if(info.round==21)
	{
		_tower_way_index[x]=_tower_basic_way[x];
		baoshou_xingwei(info,x);
		return;
	}
	for (int i = 0; i < 12; i++)
	{
		if((info.round<12.1&&info.towerInfo[i].owner!=info.myID&&getDistance(info.towerInfo[x].position,info.towerInfo[i].position)<350&&info.lineInfo[i][x].exist==1
			)||(i!=x&&info.lineInfo[i][12].exist==1&&coming_arrive_round(info,i,12)<coming_arrive_round(info,x,12)+0.15))
		{
			_tower_way_index[x]=_tower_basic_way[x];
			_evaluate[cutLine][x][12]=1000;
			_cutline_weizhi[x][12]=0;
			_evaluate[changeStrategy][x][Grow]+=strategychange(info,x,Grow)*1000;
			return;		
		}
	}
	
start:
	double tem;
	switch(_touzhongta_xingwei_index)
	{
	case 0:
		if(info.lineInfo[x][12].exist==1)
		{
			_touzhongta_xingwei_index=1;
			goto start;
		}

		_evaluate[addLine][x][12]=1000;
		_evaluate[changeStrategy][x][Grow]+=((tem=strategychange(info,x,Grow))>fence)?tem*(_times_strategychange+1):0.99;
		break;
	case 1:
		if(info.lineInfo[x][12].exist==1&&info.lineInfo[x][12].state==Arrived)
		{
			_touzhongta_xingwei_index=2;
			goto start;
		}

		_evaluate[changeStrategy][x][Grow]+=((tem=strategychange(info,x,Grow))>fence)?tem*(_times_strategychange+1):0.99;
		break;
	case 2:
		if(info.lineInfo[x][12].state==AfterCut||info.lineInfo[x][12].exist==0)
		{
			_tower_way_index[x]=baoshou;
			_touzhongta_xingwei_index=0;
			return;
		}
		_evaluate[cutLine][x][12]=1000;
		_cutline_weizhi[x][12]=12;
		_evaluate[changeStrategy][x][Grow]+=((tem=strategychange(info,x,Grow))>fence)?tem*(_times_strategychange+1):0.99;
		return;
	}
}

void tiaodou_xingwei(Info& info,TTowerID i)
{
	if(info.round>49)
		_tower_way_index[i]=_tower_basic_way[i];
	double compare=555;
	int ruo=-1;
	int flag=0;
	//strategy����
	double tem=0;
	if(info.towerInfo[12].strategy==Normal&&info.towerInfo[info.myID].strategy==Grow&&info.towerInfo[info.myID].strategy==Grow&&info.towerInfo[info.myID].strategy==Grow)
	{
		if(info.round<20&&info.playerInfo[info.myID].technologyPoint>=StrategyChangeCost[Normal][Attack])
		_evaluate[changeStrategy][i][Attack]+=1300;
	}
	//add����
	double budao=0;
	tem=0;
	for (int j = 0; j < 12; j++)
	{
		if(info.towerInfo[j].owner!=info.myID&&info.towerInfo[j].owner!=-1)
		{
			double score=0;
			budao=budao_evaluate_new(info,i,j);
			_evaluate[addLine][i][j]+=((tem=budao)>fence)?score=(tem*_times_budao_evaluate):score=0.98;
			_evaluate_detail[addLine][i][j][budao_score]=score;
		}
	}

	if(_last_round_tower_owner[i]!=info.myID&&info.towerInfo[i].owner==info.myID)
	{
		for (int t = 0; t < 12; t++)
		{
			if(info.towerInfo[t].resource<compare&&info.towerInfo[t].owner==info.myID)
			{
				compare=info.towerInfo[t].resource;
				ruo=t;
			}
		}
		for (int t = 0; t < 12; t++)
		{
			if(info.lineInfo[t][12].exist==1&&info.towerInfo[t].owner!=info.towerInfo[12].owner&&info.lineInfo[t][12].state!=AfterCut)
				flag=1;
		}
		if(flag==0)
			_evaluate[addLine][12][ruo]+=1001;
	}
	for (int j = 0; j < 12; j++)
	{
		if(info.towerInfo[j].owner==info.myID||info.towerInfo[j].owner==-1)
			continue;
		double score=0;
		_evaluate[addLine][i][j]+=((tem=fightback(info,i,j))>fence)?score=(tem*_times_fightback):score=0.99;
		_evaluate_detail[addLine][i][j][fightback_score]=score;
	}
	
	double score2=0;
	int tar=xiyinhuoliopen(info);
	if(tar!=-1)
	{
		_evaluate[addLine][12][tar]+=954;
		_evaluate_detail[addLine][12][tar][tiaodou]=954;
	}

	//cut����
	for (int t = 0; t < 12; t++)
	{
		if(info.lineInfo[12][t].exist==1&&info.towerInfo[t].owner==info.myID&&info.lineInfo[12][t].state==Arrived)
		{
			_evaluate[cutLine][12][t]=1000;		
			_cutline_weizhi[12][t]=0;	
		}
	}
	//leisi songle
	int uy=0;
	for (int t = 0; t < 12; t++)
	{
		if(info.lineInfo[t][12].exist==1&&info.lineInfo[12][t].exist==0&&info.towerInfo[t].owner!=info.myID&&info.lineInfo[t][12].state!=AfterCut&&coming_arrive_round(info,t,12)<1.5)
			uy++;
	}
	if(uy>2-info.towerInfo[12].currLineNum)
	{
		for (int m = 0; m < 12; m++)
		{
			if(info.lineInfo[12][m].exist==1&&info.lineInfo[12][m].state!=AfterCut&&_lines_index[12][m]!=fightback_score)
			{
				_evaluate[cutLine][12][m]=1500+rand()%100;		
				_cutline_weizhi[12][m]=info.lineInfo[12][m].resource-1;					
			}
		}
	}
	//		
	double fightback_cut_score=0;
	for (int j = 0; j < 12; j++)
	{
		if(info.towerInfo[j].owner!=info.myID&&info.lineInfo[i][j].exist==1&&info.lineInfo[i][j].state!=AfterCut)
		{
			fightback_cut_score=fightback_lines_control(info,i,j);			
			_evaluate[cutLine][12][j]+=(fightback_cut_score>fence)?(fightback_cut_score=fightback_cut_score*_times_fightback_cut):(fightback_cut_score=0.90);
			_cutline_weizhi[12][j]=info.lineInfo[12][j].resource-1;	
		}
	}
	//  tiaodou weihu
	double tiaodou_cutscore=0;
	for (int j = 0; j < 12; j++)
	{
		if(info.towerInfo[j].owner!=info.myID&&info.lineInfo[i][j].exist==1&&info.lineInfo[i][j].state!=AfterCut)
		{
			tiaodou_cutscore=tiaodou_cut(info,i,j);
			_evaluate[cutLine][i][j]+=(tiaodou_cutscore>fence)?(tiaodou_cutscore=tiaodou_cutscore*_times_tiaodou_cut):(tiaodou_cutscore=0.56);
			_cutline_weizhi[12][j]=info.lineInfo[12][j].resource-1;	
		}
	}


}
void jizhonggongji_xingwei(Info& info,TTowerID x)
{
	int teamid=998;
	int memberid=234;
	for (int i = 0; i < 5; i++)
	{
		if(squads[i].be_using!=1)
			continue;
		for (int j = 0; j < squads[i].member_num; j++)
		{
			if(squads[i].members[j]==x)
			{
				teamid=i;
				memberid=j;
				break;
			}
		}//                                           This is the final release of the zuc5.5 version 5
	}
	if(teamid==998||memberid==234)
	{
		fileout("dsfasag",2,"fg","error.txt");                      // ���� �飡������������
											              //error ����  ���ģ�������
		fileout("eee",info.round,"eeee","error.txt"); 
		fileout("aaa",x,"eeee","error.txt"); 
	}
	int enemy=squads[teamid].target;
	fileout("member",x,"ddaa","jizhong.txt");
	fileout("team",teamid,"ddaa","jizhong.txt");
	fileout("round",info.round,"ddaa","jizhong.txt");
	fileout("teamipeope ",squads[teamid].member_num,"ddaa","jizhong.txt");
start:
	switch(_jizhonggongji_xingwei_index[x])
	{
	case 0:         //δִ�й���
		fileout("succsee0  ",enemy,"yeah","jizhong.txt");
		if(squads[teamid].members_state[memberid]==1)//�ֲ��ж� ����bug'
		{
			_jizhonggongji_xingwei_index[x]=1;
			goto start;
		}
		else if(info.lineInfo[x][enemy].exist==1)
		{
			_jizhonggongji_xingwei_index[x]=1;
			_jizhonggongji_xingwei_usecount[x]=0;
			fileout("fidkadhdaj",2,"sc","error.txt");                //error ����  ���ģ�������
			fileout("eee",info.round,"eeee","error.txt"); 
			fileout("aaa",x,"eeee","error.txt"); 
			goto start;		
		}
		if(info.towerInfo[enemy].owner==info.myID)
		{
			_jizhonggongji_xingwei_index[x]=3;
			goto start;
		}
		baoshou_xingwei(info,x);
		for (int i = 0; i < 13; i++)
		{
			_evaluate[addLine][x][i]-=2000;
		}
		_evaluate[addLine][x][enemy]=fence+50;
		_jizhonggongji_xingwei_usecount[x]=0;
		break;
	case 1:               //
		fileout("succsee1  ",enemy,"yeah","jizhong.txt");
		if(info.towerInfo[enemy].owner==info.myID)
		{
			_jizhonggongji_xingwei_index[x]=3;
			goto start;
		}
		if(info.lineInfo[enemy][x].exist==1)
		{
			_jizhonggongji_xingwei_index[x]=2;
			goto start;		
		}
		baoshou_xingwei(info,x);
		if(_jizhonggongji_xingwei_usecount[x]<8&&info.lineInfo[x][enemy].exist==1&&info.lineInfo[enemy][x].exist==0&&info.lineInfo[x][enemy].state==Arrived)     //�������˷����ȵ�����ʵ���� ��һ�º������           
		{
			_jizhonggongji_xingwei_usecount[x]++;
			_evaluate[cutLine][x][enemy]=0.01;
		}
		break;
	case 2:   //�Է��Ѿ����Լ�����˲���  ������������ģʽ
		fileout("succsee2  ",enemy,"yeah","jizhong.txt");
		if(info.towerInfo[enemy].owner==info.myID)
		{
			_jizhonggongji_xingwei_index[x]=3;
			goto start;
		}
		baoshou_xingwei(info,x);
		if(info.lineInfo[enemy][x].exist==1&&info.lineInfo[x][enemy].exist==1&&info.lineInfo[x][enemy].maxlength>=300)
		{
			_evaluate[cutLine][x][enemy]=fence+10;
			_cutline_weizhi[x][enemy]=info.lineInfo[x][enemy].resource-1;
		}
		break;
	case 3:            //�����Ѿ��ɹ�
		if(info.towerInfo[enemy].owner==info.myID&&info.lineInfo[x][enemy].exist==1)   //�ֲ��ж� û������ʱ����������
		{
			fileout("succsee",enemy,"yeah","jizhong.txt");
			//if(info.lineInfo[x][enemy].exist==1&&)
			//	_evaluate[cutLine][x][enemy]=0.02;
		//	else
			baoshou_xingwei(info,x);
			_evaluate[cutLine][x][enemy]=fence+16;
			_cutline_weizhi[x][enemy]=info.lineInfo[x][enemy].resource-1;                //�ǲ���Ҫ�ȼ����غ� ����
		}
		else if(info.towerInfo[enemy].owner==info.myID&&info.lineInfo[x][enemy].exist==0)   //�����ɹ��� �ȼ����غ� ��ɢС��
			baoshou_xingwei(info,x);
		else
		{
			_jizhonggongji_xingwei_index[x]=2;
			goto start;		
		}
		break;

	}

}

/*
int tiaodou_cut_act(Info& info,TTowerID x)
{
	for (int i = 0; i < 13; i++)
	{
		if(info.lineInfo[x][i].exist==0||_is_for_tiaodou_porpose[x][i]!=1)
			continue;
		if(info.lineInfo[i][x].exist==1)
		{
			_evaluate[cutLine][x][i]=(fence+15);
			_cutline_weizhi[x][i]=info.lineInfo[x][i].resource-1;
		}
		else if(coming_arrive_round(info,x,i)<2&&budao_evaluate_new(info,x,i,1)>(fence+20))   //���ԣ���������
		{
			_is_for_tiaodou_porpose[x][i]=0;
		}
		else
		{
			//_evaluate[cutLine][x][i]=(fence+100);
			//_cutline_weizhi[x][i]=info.lineInfo[x][i].resource-1;		
		}
	}
	return 0;
}
*/

int his_to_me(Info& info,int id)
{
	if(id!=0&&id!=1&&id!=2&&id!=3)
		return 0;
	if(id==info.myID)
		return 0;
	int count=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner!=id)
			continue;
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner!=info.myID)
				continue;
			if(info.lineInfo[i][j].exist==1&&info.lineInfo[i][j].state!=AfterCut)
				count++;
		}
	}
	return(count);
}

double arrive_round(Info& info,TTowerID T1,TTowerID T2)
{
	TPoint T1_pos=info.towerInfo[T1].position;
	TPoint T2_pos=info.towerInfo[T2].position;
	
	double distan=getDistance(T1_pos,T2_pos);

	int owner=info.towerInfo[T1].owner;
	if(owner==-1)
	{
		fileout("sagsghshhsh","error.txt");
		return 1000;
	}
	double result=distan*0.1/(3.0*SpeedStage[info.playerInfo[owner].ExtendingSpeedLevel]);

	return result;
}

double coming_arrive_round(Info& info,TTowerID T1,TTowerID T2)
{
	double l;
	l=arrive_round(info,T1,T2);
	if(info.towerInfo[T1].owner==-1)
	{
		fileout("sagsgsghhg","error.txt");
		return(l);
	}

	if(info.lineInfo[T1][T2].exist==0||info.lineInfo[T1][T2].state==AfterCut)
		return(l);
	else
	{
		int owner=info.towerInfo[T1].owner;
		if(info.lineInfo[T2][T1].exist==0)
			l=info.lineInfo[T1][T2].maxlength-(info.lineInfo[T1][T2].resource)*10.0;
		else
			l=info.lineInfo[T1][T2].maxlength-(info.lineInfo[T1][T2].resource+info.lineInfo[T2][T1].resource)*10.0;
		l=l*0.1/(3.0*SpeedStage[info.playerInfo[owner].ExtendingSpeedLevel]);
	}
	return(l);
}

double fightback(Info& info,TTowerID myT,TTowerID hisT)  //�Բ����ϴ������������Ϊ0
{
	//���ܻ������  �������ˣ���*���� �����е�һЩ֧Ԯ�ߵȣ� 
	//�����黹��  ����������ֺ���  
	//�ܻ���  ������  �������ж����(��������Խ��Խ����)  �Է�ʵ����Σ�*���Ľ���
	// ����֮�������������ʧ���� �õ��˶�е����٣�
	//�򲻹�ҲҪ������ ���Ľ�
	// ���������ƺ�����
	//**��Ϊ���ƻ��ߵ�ʱ��û���˺�

	if(info.lineInfo[hisT][myT].exist==0||info.lineInfo[hisT][myT].state==AfterCut||info.lineInfo[myT][hisT].exist!=0||info.towerInfo[myT].owner!=info.myID||info.towerInfo[hisT].owner==info.myID)
		return(0);
	if(myT==12&&info.round<50)
	{
		if(coming_arrive_round(info,hisT,myT)<2.1&&info.towerInfo[myT].resource>18)
			return(fence+20+(rand()%100)/33.33);
		else
			return 0;
	}
	if(info.towerInfo[myT].strategy==Attack&&info.towerInfo[hisT].strategy==Defence)
		return 0;
	fileout(myT ,"under attack!!! evaluating......", hisT);
	double score=0;
	double tem=0;
	double need=(getDistance(info.towerInfo[myT].position,info.towerInfo[hisT].position)/2)/10;
	double round=arrive_round(info,myT,hisT)/2;
	double left=info.towerInfo[myT].resource-need-round*constrain(each_round_consume(info,myT),0,50);
	if(addline_ok(info,myT,hisT)!=0||left<12) //���ֲ��ܾͷ��� �д��Ľ�
	{
		fileout("give up!");
		return 0;
	}
	else
	{
		if(left<20)
			score-=25;
		double survive_round =left/(each_round_consume(info,myT)+confront_consume(info,myT,hisT));
		if(survive_round<0)
			tem=150;
		else if(survive_round<5)
			tem=pow(survive_round,3)/5;
		else
		{
			survive_round-=5;
			tem=25+survive_round*4;
		}
		if(tem>=150)
			tem=150;                  //tem Ϊ��������ʵ���Ĺ���  ��׼�ǿ�����״̬���ܳŶ��ٻغϡ�=200�������
		double coming_round=coming_arrive_round(info,hisT,myT);
		if(coming_round<0.1)
			score+=1.25*tem;
		else if(coming_round<1.1)
			score+=1*tem;
		else if(coming_round<2.1)
			score+=0.9*tem;
		else if(coming_round<3.1)
			score+=0.8*tem;
		else if(coming_round<5.1)
			score+=0.5*tem;
		else if(coming_round<6.1)
			score+=0.25*tem;
		else 
			score+=0.1*tem;
		fileout("fight back score",score);
		return(score+(rand()%100)/33.3);
	}


	//���ֻ���  
	//����  Ԥ�����С��0 һƱ��� 
	//���С��10  -20
	//Ԥ�ƴ��غ�x  ��x^3  ��6 ÿ������20 500�ⶥ
	//�����Գ˷���Ȩ ��10 0.1 10-5 0.1++0.25 ��5 0.35 3 0.5 2 0.8 1 1 0 2
	// �������ֵ���100 ��Ƚ�����Ը
}

double help_friend(Info& info,TTowerID giveT,TTowerID needT)
{
	int me=info.myID;
	if((info.round<43||_begin==0)&&needT==12)
		return 1;
	if(info.lineInfo[giveT][needT].exist==1)
	{
		//fileout("help already exist");
		return 2;
	}
	if(info.towerInfo[needT].owner!=me||info.towerInfo[giveT].owner!=me)
	{
		fileout("help_friend use error","error.txt");
		return(0.55);
	}
	if(addline_ok(info,giveT,needT)!=0)
		return 0.2;
	//һ����ֻ��һ��help���ʵ�line
	for (int i = 0; i < 13; i++)
		if(i!=giveT&&info.towerInfo[i].owner==info.myID&&info.lineInfo[giveT][i].exist==1&&info.lineInfo[giveT][i].state!=AfterCut)
			return 0.22;
	if(info.towerInfo[giveT].resource<(_budao_line[giveT]+11)||info.towerInfo[needT].resource>0.9*info.towerInfo[needT].maxResource)
		return 0.57;
	if(each_round_consume(info,needT)<-10)
		return 0.7;
	double dis=getDistance(info.towerInfo[giveT].position,info.towerInfo[needT].position);
	if(info.towerInfo[giveT].resource<info.towerInfo[giveT].maxResource-2)
		if(!((dis<601&&(!(giveT%3!=0||giveT==12)))||(dis<450&&(giveT%3!=0||giveT==12))))
			return 0.316;
	if(each_round_consume(info,giveT)>7)
		return 0.88;
	int countn=0;
	int countg=0;
	for (int i = 0; i < 13; i++)
	{
		if(i!=needT&&info.towerInfo[i].owner!=info.myID&&info.towerInfo[i].owner!=-1&&info.lineInfo[i][needT].exist==1&&info.lineInfo[i][needT].state!=AfterCut)
			countn++;
		if(i!=giveT&&info.towerInfo[i].owner!=info.myID&&info.towerInfo[i].owner!=-1&&info.lineInfo[i][giveT].exist==1&&info.lineInfo[i][giveT].state!=AfterCut)
			countg++;
	}
	if(info.towerInfo[needT].resource>_budao_line[needT]+10&&info.towerInfo[giveT].resource<0.9*info.towerInfo[giveT].maxResource&&countn==0)
		return 0.39;
	if(countg>0)
		return 0.67;
	fileout(info.round,"here",needT,"pppp.txt");
	if(giveT%3!=0||giveT==12)
	{
		if((countn==0)&&(info.towerInfo[giveT].resource<info.towerInfo[giveT].maxResource-3))
			return 0.36;
		if(countn==0)
		{
			if(info.towerInfo[giveT].currLineNum<=info.towerInfo[giveT].maxLineNum-1)
				return 0.76;
			int fl=0;
			for (int i = 0; i < 12; i++)
			{
				if(info.towerInfo[i].owner==info.myID&&i!=12&&i!=needT&&info.towerInfo[i].resource<info.towerInfo[needT].resource-2)
					fl=1;
			}
			if(needT!=12&&fl==0)
				return (fence+info.towerInfo[needT].resource/200.0);
			if(needT==12&&info.towerInfo[needT].resource<23&&fl==0)
				return (fence+9.8);
		}
		else
			return(fence+info.towerInfo[giveT].resource/20+countn*20);
	}
	else
	{
		if(countn!=0&&countg==0)
			return(fence+info.towerInfo[giveT].resource/20+countn*10+10);
		if(info.towerInfo[giveT].currLineNum<=info.towerInfo[giveT].maxLineNum-1&&countn==0)
			return 0.75;
		if(info.towerInfo[giveT].resource>0.95*info.towerInfo[giveT].maxResource&&each_round_consume(info,giveT)<1.2&&info.towerInfo[needT].resource<0.8*info.towerInfo[needT].maxResource)
		{
			return(fence+constrain(100/info.towerInfo[needT].resource,0,10));
		}
		if(info.towerInfo[needT].resource<_budao_line[needT]&&info.towerInfo[needT].resource<0.8*info.towerInfo[giveT].resource)
			return(fence+info.towerInfo[giveT].resource/20);
	}
	return 0.147;
}
void help_brain(Info& info)
{
	double gap=0;

	double tem[13][13];
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			tem[i][j]=0;

	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner!=info.myID)
			continue;
		gap=0;
		for(int j=0;j<13;j++)
			if(_added_lines_round[i][j][2]>gap)		
				gap=_added_lines_round[i][j][2];

			gap=info.round-gap;
		if(gap<3.5&&info.towerInfo[i].resource<0.85*info.towerInfo[i].maxResource)
			continue;

		for (int j = 0; j < 13; j++)  
		{
			if(j==12&&info.round<45)
				continue;
			if(i==j)
				continue;
			if(info.towerInfo[j].owner!=info.myID)
				continue;
			if(info.lineInfo[i][j].exist==1||info.lineInfo[j][i].exist==1)
				continue;	
			tem[i][j]=help_friend(info,i,j)+(rand()%100)/100.0;
		fileout(info.round,"ppptp.txt");
			fileout(i,",",j,"ppptp.txt");
			fileout(tem[i][j],"ppptp.txt");
			if(tem[i][j]<fence)
				tem[i][j]=0;
		}
	}

	for (int needT = 0; needT < 13; needT++)
	{
		if(info.towerInfo[needT].owner!=info.myID)
			continue;
		int attackn=0;
		int existn=0;
		for (int i = 0; i < 13; i++)
		{
			if(i!=needT&&info.towerInfo[i].owner!=info.myID&&info.towerInfo[i].owner!=-1&&info.lineInfo[i][needT].exist==1&&info.lineInfo[i][needT].state!=AfterCut)
				attackn++;
			if(i!=needT&&info.towerInfo[i].owner==info.myID&&info.lineInfo[i][needT].exist==1&&info.lineInfo[i][needT].state!=AfterCut)
				existn++;
		}
		if((existn/2.0>0.9&&existn/2.0>(attackn-0.1))||(needT==12&&existn>1.5)||existn>5.1)
		{
			for (int k = 0; k < 13; k++)
			{
				tem[k][needT]=0;
			}
		}		
	}
	double com=0;
	for (int i = 0; i < 13; i++)
	{
		com=3;
		for (int j = 0; j < 13; j++)
		{
			if(tem[j][i]>com)
				com=tem[j][i];
		}
		for (int j = 0; j < 13; j++)
		{
			if(tem[j][i]<com-0.001)
				tem[j][i]=0.98;
		}
	}
	fileout("*");
	fileout(info.round,"pppp.txt");
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
		{
			_help_brain_outcome[i][j]=tem[i][j];
			fileout(i,",",j,"pppp.txt");
			fileout(tem[i][j],"pppp.txt");
		}

}
double help_friend_new(Info& info,TTowerID giveT,TTowerID needT)
{
	return(_help_brain_outcome[giveT][needT]);
}

//�ж�һ�����Ľ��ųɶ� ����1�������  ����0 ���鱣��
int jiaozhuo_evaluate(Info& info,TTowerID x)
{
	int owner=info.towerInfo[x].owner;
	int nummy=0;
	int nummys=0;
	int numtheir=0;
	int tem=55;
	int player=0;
	for (int i = 0; i < 13; i++)
	{
		if(i==x||info.towerInfo[i].owner==owner||info.towerInfo[i].owner==-1)
			continue;
		if(info.lineInfo[i][x].exist==1&&info.towerInfo[i].owner==info.myID)
		{
			nummy++;
			if(info.lineInfo[x][i].exist==0)
				nummys++;
		}
		if(info.lineInfo[i][x].exist==1&&info.towerInfo[i].owner!=info.myID)
		{
			if(info.towerInfo[i].owner!=tem)
			{
				tem=info.towerInfo[i].owner;
				player++;
			}
			numtheir++;
		}
	}
	if(info.towerInfo[x].resource>100&&nummy>=4)
		return 0;
	if(info.towerInfo[x].resource>100&&nummy>=3&&nummys>0)
		return 0;
	if(info.towerInfo[x].resource<=100&&nummy>=3)
		return 0;
	if(player>=2)
		return 0;
	if((nummy+numtheir)>=5)
		return 0;
	return 1;
}
void fileout(const char *a,const char *name)
{
	/*ofstream log(name,ios::app);
	log<<a<<endl;
	log.close();*/
	
}
void fileout(const char *a,double b,const char *name)
{
	
	/*ofstream log(name,ios::app);
	log<<a<<b<<endl;
	log.close();*/
	
}
void fileout(const char *a,int b,const char *c,const char *name)
{
	
	/*ofstream log(name,ios::app);
	log<<a<<b<<c<<endl;
	log.close();*/
	
}
void fileout(int a,const char *c,int b,const char *name)
{
	
	/*ofstream log(name,ios::app);
	log<<a<<c<<b<<endl;
	log.close();*/
	
}
void fileout(int a,const char *name)
{

	/*ofstream log(name,ios::app);
	log<<a<<endl;
	log.close();*/
	
}
void fileout(double a,const char *name)
{
	
	/*ofstream log(name,ios::app);
	log<<a<<endl;
	log.close();*/
	
}
void fileoutteaminfo(Info& info)
{/*
	ofstream log("teaminfo.txt",ios::app);
	log<<"round"<<info.round<<endl;
	for (int i = 0; i < 13; i++)
	{
		log<<"way"<<i<<"     "<<_tower_way_index[i]<<endl;
	}
	for (int i = 0; i < 5; i++)
	{
		log<<"biaohao"<<i<<"***********"<<endl;
		log<<"be using"<<squads[i].be_using<<endl;
		log<<"member num"<<squads[i].member_num<<endl;
		log<<"target "<<squads[i].target<<endl;
		for(int j=0;j<14;j++)
		{
			log<<"id  "<<squads[i].members[j]<<endl;
			log<<"id"<<squads[i].members_state[j]<<endl;
		}
	}
	log.close();
	*/
}
/////////�������ĵȼ�
int level(TResourceD towersource)
{
	if(towersource<10)
		return 0;
	if(towersource<40)
		return 1;
	if(towersource<80)
		return 2;
	if(towersource<150)
		return 3;
	else
		return 4;
}
/*
//�ж�һ���������Լ��Ƿ�ռ�������ƣ�1Ϊ��0�񣬱�׼ �������Լ�������������������Դ��������������Դ�������޲��ߣ�������֮��
int is_myquyu(Info& info,int quyu_id)
{
	if(quyu_id==3)
	{
		if(info.towerInfo[12].owner==info.myID)
			return 1;
		else
			return 0;
	}
	int count=0;
	for (int i = 0; i < 12; i++)
	{
		if(info.towerInfo[i].owner==info.myID&&quyu[i]==quyu_id)
			count++;
	}
	if(count>=2&&quyu_resource(info,quyu_id,1)/quyu_resource(info,quyu_id)>0.67)
		return 1;
	else
		return 0;
}
*/
/*
//һ�������޲�������Դ  method Ϊ1 �����ҵı�ֵ
double quyu_resource(Info& info,int quyu_id,int method)
{
	double count=0;
	for(int i=0;i<13;i++)
	{
		if(method==1)
		{
			if(quyu[i]==quyu_id&&info.towerInfo[i].owner==info.myID)
				count+=info.towerInfo[i].resource;
		}
		else	
		{
			if(quyu[i]==quyu_id)
				count+=info.towerInfo[i].resource;
		}
	}
	return count;
}
*/
//  �жϴ�x��i���� �����Ӱ˵�����
double zaqizaba_cut(Info& info,TTowerID x,TTowerID i)
{
	int attacker[4]={0,0,0,0};
	if(i==x)
		return 0.3;
	if(info.towerInfo[x].owner!=info.myID)
		return 0.35;
	if(info.lineInfo[x][i].exist==0)
		return(0.2);
	if(info.lineInfo[x][i].state==AfterCut)
		return(0.1);
	if(info.towerInfo[i].owner==-1)  //�����ٲ�
		return 0;
	//��x����ʵ������ ���޿���  ��fightback׼��
	if(info.towerInfo[x].currLineNum>=info.towerInfo[x].maxLineNum)
	{
		for (int j = 0; j < 13; j++)
		{
			if(info.lineInfo[x][j].exist==1&&info.lineInfo[x][j].state==AfterCut)
				goto next;
		}
		for (int k = 0; k < 13; k++)
		{//Ŀ����Ϊfightback�ṩ����   �����ǲ�fightback���ܱ�bomb���������songle���ǵģ� ������defence ���˲���attackû��Ҫ
			//������attack ����Ϊdefence û��Ҫ  ������grow ������denfence û��Ҫ
			if(k!=x&&info.lineInfo[k][x].exist==1&&info.towerInfo[k].owner!=info.myID&&info.lineInfo[x][k].exist==0&&coming_arrive_round(info,k,x)<2.61)
			{
				if(info.towerInfo[x].strategy==Defence&&info.towerInfo[k].owner!=Attack)
					continue ;
				if(info.towerInfo[x].strategy==Attack&&info.towerInfo[k].owner==Defence)
					continue ;
				if(info.towerInfo[x].strategy==Grow&&info.towerInfo[k].owner!=Defence)
					continue ;
				if(coming_arrive_round(info,k,x)<3)
				{
					if(info.towerInfo[i].owner==info.myID)
						return 95;
					else if(info.lineInfo[i][x].exist==0)
						return 85;
					else
						goto next;
				}
			}
		}
	}
next:
	//�б�ͻȻbomb��Σ�� �ٶȻ��ձ���8
	if(bomb1(info,x)>info.towerInfo[x].resource*2&&(info.lineInfo[i][x].exist==0))
		return 200.3;
	//����ǿ������ж�  �Լ������ж�
	if(info.towerInfo[i].owner==info.myID)
	{
		if(info.towerInfo[i].resource>info.towerInfo[i].maxResource*0.9&&info.towerInfo[x].resource<0.9*info.towerInfo[x].maxResource)
			return((info.towerInfo[i].resource)/5+fence+5);
		int countn=0;
		int countg=0;
		int helpn=0;
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner!=info.myID&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][i].exist==1&&info.lineInfo[j][i].state!=AfterCut)
				countn++;
			if(info.towerInfo[j].owner!=info.myID&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][x].exist==1&&info.lineInfo[j][x].state!=AfterCut&&(info.lineInfo[x][j].exist==1||coming_arrive_round(info,j,x)<6))
				countg++;
			if(info.towerInfo[j].owner==info.myID&&j!=i&&info.lineInfo[j][i].exist==1&&info.lineInfo[j][i].state!=AfterCut)
				helpn++;
		}
		if(countg>0.9&&info.towerInfo[x].resource<0.8*info.towerInfo[x].maxResource)
			return(constrain(100/info.towerInfo[x].resource,0,30)+fence);
		else if(countg>1.9&&info.towerInfo[x].resource<0.9*info.towerInfo[x].maxResource)
			return(constrain(100/info.towerInfo[x].resource,0,30)+fence);
		if(helpn>2.1&&helpn>countn*2-1)
		{
			if(rand()%3==1)
				return((200-info.towerInfo[x].resource)/10.0+75);
		}
		if(info.towerInfo[x].resource<info.towerInfo[i].resource*1.15&&info.towerInfo[x].resource+info.lineInfo[x][i].resource<0.75*info.towerInfo[x].maxResource&&countn==0)
			return 90;
		if(info.towerInfo[x].resource<_danger_line[x]+15)
			return 83.6;


	}
	//�Լ���������
	

	//�ཬ�ж�
	if(info.towerInfo[i].owner!=info.myID&&info.towerInfo[i].owner!=-1)
	{
		for (int j = 0; j < 13; j++)
		{
			if(j!=i&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][i].exist==1&&info.lineInfo[j][i].state!=AfterCut&&info.lineInfo[j][i].resource*10>=info.lineInfo[j][i].maxlength/2.0+10)
				attacker[info.towerInfo[j].owner]+=1;
		}
		double count=0;
		int nitan=0;
		for (int k = 0; k < 4; k++)
		{
			if(attacker[k]>0&&k!=info.myID)
			{
				count+=1;
				if(k==info.towerInfo[i].owner)
					count-=0.5;
			}
			if(attacker[k]>=3&&k!=info.myID&&k!=info.towerInfo[i].owner)
				nitan=1;
		}
		if(count>=1.9)
			return 95;
		if(nitan==1)
			return 94;
	}

	if(info.towerInfo[x].resource>0.99*info.towerInfo[x].maxResource&&info.towerInfo[i].owner!=info.myID&&info.towerInfo[i].owner!=-1)
	{
		if(info.lineInfo[x][i].exist==1&&info.lineInfo[x][i].state==Arrived)
		{
			return (fence+(rand()%100)/10.0);
		}
	}
	//�Լ����� ��û����
	return 0;
}
// ���Է���0  ����һ��Ԥ�ڱ���������1   ������������2  ���б��߷���3 ֻ������״���Ԥ��//state��д ��������  дΪ1 ���ж��ܷ�һ�����(�Կ�)
int addline_ok(Info& info,int from,int to,int state) 
{

	//fileout(info.towerInfo[from].owner,"adsd.txt");
	//fileout(info.towerInfo[to].owner,"adsd.txt");
	double need;
	need=(getDistance(info.towerInfo[from].position,info.towerInfo[to].position)/2)/10;
	if(info.lineInfo[from][to].exist==1)
		return 3;
	if(info.towerInfo[from].maxLineNum<=info.towerInfo[from].currLineNum)
		return 2;
	if(state==1)
	{
		double round=arrive_round(info,from,to)/2;
		double left=info.towerInfo[from].resource-need-round*each_round_consume(info,from);
		if(left<0)
			return 1;
		else
			return 0;
	}
	if(info.lineInfo[to][from].exist==1&&(info.towerInfo[to].owner!=info.myID))  
	{
		double round=arrive_round(info,from,to)/2;
		double left=info.towerInfo[from].resource-need-round*each_round_consume(info,from);
		if(left<0)
			return 1;
	}
	if((info.lineInfo[to][from].exist==1&&info.towerInfo[to].owner==info.myID)||info.lineInfo[to][from].exist==0)  
	{
		double round=arrive_round(info,from,to);
		double left=info.towerInfo[from].resource-need*2-round*each_round_consume(info,from);
		if(left<0)
			return 1;
	}	
	return 0;
}
//������Tʵ�ʻظ�����
double real_recover_speed(Info& info,TTowerID T)
{
	if(info.towerInfo[T].owner==-1)
		return 0;
	double base_cover_speed=BASE_REGENERETION_SPEED[level(info.towerInfo[T].resource)];
	return base_cover_speed*StrategyRegeneratePower[info.towerInfo[T].strategy]*RegenerationSpeedStage[info.playerInfo[info.towerInfo[T].owner].RegenerationSpeedLevel];
}
//������Tÿ�����߻�������//////�õ�real_recover_speed����//method ���1��ָ�����һ������
double base_speed(Info& info,TTowerID T,int method)
{
	if(info.towerInfo[T].owner==-1)
	{
		fileout("sgasdgsdgsdh","error.txt");
		return 0;
	}
	int line_num=info.towerInfo[T].currLineNum;
	double base_cover_speed=real_recover_speed(info,T)/StrategyRegeneratePower[info.towerInfo[T].strategy]; //���ԶԱ��߻�������û��Ӱ��Ҫ����
	if(line_num+method==1)
		return base_cover_speed;
	if(line_num+method==2)
		return base_cover_speed*0.8;
	if(line_num+method==3)
		return base_cover_speed*0.6;
	return 0;
}
//������T��ǰÿ�غϾ�������Դ�������ǻָ���.// ��Դ���� ��������
double each_round_consume(Info& info,TTowerID T)
{
	if(info.round==0)
		return 0;
	if(info.towerInfo[T].owner==-1)
		fileout("saghehyryyy","error.txt");
	return((-1)*(info.towerInfo[T].resource-_last_round_resource[T]));
}
//�������ڶԿ���line����������  ֻ���ڵ�ǰ��Ϣ
double confront_consume(Info& info,LineInfo line)
{
	//fileout(info.towerInfo[line.sourceTower].owner,"tttt.txt");
	//fileout(info.towerInfo[line.targetTower].owner,"tttt.txt");
	if(line.exist==0)
	{
		fileout("safggasgsagastre","error.txt");
		return 0;
	}
	double speed1,speed2;

	double basespeed1=base_speed(info,line.sourceTower);
	TPower confront1=ConfrontPower[info.towerInfo[line.sourceTower].strategy][info.towerInfo[line.targetTower].strategy];
	speed1=confront1*basespeed1;

	double basespeed2=base_speed(info,line.targetTower);
	TPower confront2=ConfrontPower[info.towerInfo[line.targetTower].strategy][info.towerInfo[line.sourceTower].strategy];
	speed2=confront2*basespeed2;
	return (speed1>speed2?speed1:speed2)/confront1;
}

//��T1����T2ÿ�غ���ɵ��˺�///////�õ�base_speed����
double attack_consume(Info& info,TTowerID T1,TTowerID T2,int method)
{
	//fileout(info.towerInfo[T1].owner,"daf.txt");
	//fileout(info.towerInfo[T2].owner,"daf.txt");
	if(info.towerInfo[T1].owner==-1||info.towerInfo[T2].owner==-1)
		return 0;
	TPower supress=SupressPower[info.towerInfo[T1].strategy][info.towerInfo[T2].strategy];//ѹ���˺�����
	return (base_speed(info,T1,method)*supress*attack_hurt_percentage(info,T2));
}
double attack_hurt_percentage(Info &info,TTowerID x)
{
	if(info.towerInfo[x].owner==-1)
	{
		return 1;
	}
	int owner=info.towerInfo[x].owner;
	return(DefenceStage[info.playerInfo[owner].DefenceLevel]/1.5);
}

//�����������t1 �� t2 �Կ� T1��������
double confront_consume(Info& info,TTowerID T1,TTowerID T2) 
{
	//fileout(info.towerInfo[T1].owner,"tttt.txt");
	//fileout(info.towerInfo[T2].owner,"tttt.txt");
	double speed1,speed2;

	double basespeed1=base_speed(info,T1,1);
	TPower confront1=ConfrontPower[info.towerInfo[T1].strategy][info.towerInfo[T2].strategy];
	speed1=confront1*basespeed1;

	double basespeed2=base_speed(info,T2,1);
	TPower confront2=ConfrontPower[info.towerInfo[T2].strategy][info.towerInfo[T1].strategy];
	speed2=confront2*basespeed2;

	return (speed1>speed2?speed1:speed2)/confront1;
}

//��һ����������һ����addline �Ŀ��������� �����ӷ��������Ƕȿ��� 
//Ҳ���ǹ���һ���������������Ƽ��̶ȵ�����  100 Ϊ������⵫����������  200Ϊ����
//���ǵ� ֧Ԯ  �Կ�  ѹ��  �������ذ���  �ܲ��ܷ������� �Ƿ����б���  ���������������ܳŶ೤ʱ�� �����Զ
//ע���������������Ƕȿ���  ������ս������
double addline_evaluate_my(Info &info,TTowerID fromT,TTowerID toT)
{
	if(info.towerInfo[fromT].owner==-1||info.towerInfo[toT].owner==-1)
		return 0;
	//if(info.towerInfo[fromT].owner!=info.myID)
	//{
	//	fileout("addline_evaluate_my use error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	//}
	//fileout(info.towerInfo[fromT].owner,"tttt.txt");
	//fileout(info.towerInfo[toT].owner,"tttt.txt");
	double my_influence_score;
	double d_factor=0.7;//������arrive �о����Ȩ
	double w_factor=0.5;
	double dis=getDistance(info.towerInfo[fromT].position,info.towerInfo[toT].position);
	double need=dis/10;
	double round=arrive_round(info,fromT,toT);
	double myleft=info.towerInfo[fromT].resource-need-round*each_round_consume(info,toT);
	double if_speed;
	double my_now_resource=info.towerInfo[fromT].resource;
	if(info.lineInfo[toT][fromT].exist==0)
	{
		if(addline_ok(info,fromT,toT)!=0)
			return(0);
		if_speed=base_speed(info,toT,1);
	}
	else if(info.towerInfo[toT].owner!=info.towerInfo[fromT].owner)
	{
		if(addline_ok(info,fromT,toT,1)!=0)
			return(0);
		if_speed=confront_consume(info,fromT,toT);                        //��bug �Ȳ���
	}
	else
	{
		if_speed=base_speed(info,toT,1);
		if(addline_ok(info,fromT,toT)!=0)
			return(0);
	}
	double my_then_survive_round=myleft/(each_round_consume(info,fromT)+if_speed);
	if(my_then_survive_round<0.001)
		my_then_survive_round=99;
	double my_now_survive_round=my_now_resource/each_round_consume(info,fromT);

	if(my_now_resource<12||(my_now_survive_round<5&&my_now_survive_round>0)||my_then_survive_round<2.5)
		return 0;
	double waste_score=((849-dis)/9+15)*d_factor+(4*(25-round)+15)*(1-d_factor); //100�����ƶ�
	double my_score;
	if(my_now_survive_round<=0)
		my_score=100;
	else if(my_now_survive_round<10)
		my_score=30;
	else if(my_now_survive_round<15)
		my_score=50;
	else if(my_now_survive_round<23)
		my_score=75;
	else if(my_now_survive_round<30)
		my_score=90;
	else
		my_score=95;
	if(myleft>150)
		my_score*=1.3;
	else if(myleft>130)
		my_score*=1.2;
	else if(myleft>110)
		my_score*=1.1;
	else if(myleft>80)
		my_score*=1.05;
	else if(myleft<11)
		my_score*=0.1;
	else if(myleft<20)
		my_score*=0.55;
	else if(myleft<40)
		my_score*=0.75;
	my_influence_score=my_score*(1-w_factor)+waste_score*w_factor;
	return(my_influence_score);
}

// ���ظ������� ����(���ŵ�����)  �����ж� ��
int his_confront_lines_num(Info& info,TTowerID x)
{
	int count=0;
	for(int i=0;i<13;i++)
	{
		if(i==x)
			continue;
		if(info.lineInfo[x][i].exist==1)
			if(info.lineInfo[i][x].exist==1)
				count++;
	}
	return count;
}
double towerx(Info& info)
{
	double sum=0;
	int num=0;
	double re=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID&&info.towerInfo[i].resource>35)
		{
			sum+=info.towerInfo[i].position.m_x*sqrt(info.towerInfo[i].resource);
			num++;
			re+=sqrt(info.towerInfo[i].resource);
		}
	}
	return(sum/re);
}
double towery(Info& info)
{
	double sum=0;
	int num=0;
	double re=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID&&info.towerInfo[i].resource>35)
		{
			sum+=info.towerInfo[i].position.m_y*sqrt(info.towerInfo[i].resource);
			num++;
			re+=sqrt(info.towerInfo[i].resource);
		}
	}
	return(sum/re);
}
//����1 ����ʹ�� 0������
double fangchapanduan(Info& info,double towerx,double towery)
{
	if(towerx==0||towery==0)
		return 0;
	TPoint aver;
	aver.m_x=towerx;
	aver.m_y=towery;
	double sum=0;
	double re=0;
	int num=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID&&info.towerInfo[i].resource>35)
		{
			sum+=pow(getDistance(aver,info.towerInfo[i].position),2)*sqrt(info.towerInfo[i].resource);
			num++;
			re+=sqrt(info.towerInfo[i].resource);
		}
	}	
	if(num<3)
		return 0;
	sum/=re;
	sum=sqrt(sum);

		/*ofstream log("position.txt",ios::app);
		if(1)
		{
			log<<info.towerInfo[9].position.m_x<<"*"<<info.towerInfo[1].position.m_y<<endl;
		}
		log<<info.round<<"*"<<endl;
		log<<"towerx"<<towerx<<"towery"<<towery<<"sum"<<sum<<endl;
		log.close();*/


	if(sum>329)
		return 0;
	else
		return 1;
		
}
//��T1����T2���ɲ����ԡ�������///////�õ�arrive_round��each_round_consume����//�������ڹ����ҵĵ�++
//����1���ѷ���
double constrain(double x,double a,double b)
{
	if(x>b)
		x=b;
	else if(x<a)
		x=a;
	return(x);
}
int budao_fenpei(Info& info)
{
	//�������俼��
	//1.�ۺϾ���
	//2.ս��Ԯ��  �� ��һ���ƣ���������  �ҷ��������  �з���money  �ཬ�ɷ񷴻�  attack���� resource  ����  ������    �غ���
	int towerfen[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

	if(_my_now_budao_target!=-1)
	{
		fileout("asgsdhtuj","error.txt");
		return 0;
	}
	if(info.round<28)   
	{
		_my_now_budao_target=-1;
		return 0;
	}
	//ji������
	int numm=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
			numm++;
	}
	if(numm<3)
	{
		_my_now_budao_target=-1;
		return 0;
	}
//                                           This is the final release of the zuc5.5 version 6
	//�ۺϾ���
	double y1=towery(info);
	double x1=towerx(info);
	TPoint aver;
	aver.m_x=x1;
	aver.m_y=y1;
	int x=0;
	for (int p = 0; p < 13; p++)
		if(info.towerInfo[p].owner==info.myID)
			x++;	

		//��ʽ����
	for (int T2 = 0; T2 < 13; T2++)
	{
		double distance_socre=0;//20
		double strategyscore=0;//10
		double levelscore=0;//10
		double zhanlue_score_shiwulian=0;
		double zhanlue_score_nijiang=0;
		double zhanlue_score_jiaoji=0;
		double ezhi_score=0;//
		int attacker[4]={0,0,0,0};
		int all[4]={0,0,0,0};
		double scc=0;

		if(info.towerInfo[T2].owner==info.myID||info.towerInfo[T2].owner==-1)
		{
			towerfen[T2]=0;
			continue;
		}
		else
		{
			for (int j = 0; j < 13; j++)
			{
				if(j!=T2&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut&&info.lineInfo[j][T2].resource*10>=info.lineInfo[j][T2].maxlength/2.0+10)
					attacker[info.towerInfo[j].owner]+=1;
				if(j!=T2&&info.towerInfo[j].owner!=-1&&((info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut)||(info.lineInfo[T2][j].exist==1&&info.lineInfo[T2][j].state!=AfterCut)))
				{
					all[info.towerInfo[j].owner]+=1;
					if(info.towerInfo[j].owner==info.myID&&info.lineInfo[T2][j].exist==1&&info.towerInfo[T2].strategy==Attack&&info.towerInfo[j].strategy==Grow&&info.lineInfo[T2][j].state!=AfterCut)
						all[info.towerInfo[j].owner]+=1;
				}
			}
		}
		int count=0;
		int nitan=0;
		int bingxian=0;
		for (int k = 0; k < 4; k++)
		{
			if(attacker[k]>0&&k!=info.myID)
			{
				bingxian+=attacker[k];
				count++;
			}
			if(attacker[k]>=2&&k!=info.myID)
				nitan=1;
		}
		bingxian-=attacker[info.myID];
		bingxian=constrain(bingxian,0,6);
		if(count>=2||nitan==1||bingxian>=4)
		{
			towerfen[T2]=0;
			continue;
		}
		double dis=0;
			//�ۺϾ���
		if(aver.m_x<0.1||aver.m_y<0.1)
		{
			distance_socre=0;
			fileout("sa2f","error.txt");
			fileout(info.round,"error.txt");
			fileout(aver.m_x,"s",aver.m_y,"error.txt");
		}
		else
		{
			dis=getDistance(aver,info.towerInfo[T2].position);
			if(dis>700)
				distance_socre=1;
			else if(dis>601)
				distance_socre=1;
			else if(dis>550)
				distance_socre=3;
			else if(dis>500)
				distance_socre=7;
			else if(dis>450)
				distance_socre=10;
			else if(dis>400)
				distance_socre=13;
			else if(dis>350)
				distance_socre=16;
			else if(dis>300)
				distance_socre=18;
			else
				distance_socre=20;
		}
	
		//level
		double re=info.towerInfo[T2].resource;
		double consume=each_round_consume(info,T2);
		consume=constrain(consume,-30,7);
		double round=dis*0.1/(3.0*SpeedStage[info.playerInfo[info.myID].ExtendingSpeedLevel]);
		re=re-round*(constrain(consume,-55,0));
		re=constrain(re,0.1,200);
		if(re<45)
			levelscore=20;
		else if(re<80)
			levelscore=((-1)*0.1)*re+23;
		else if(re<300)
			levelscore=(-1)*0.08571428571428572*re+17.857142857142858;
		levelscore=constrain(levelscore,0,20);
		if(re>180)
			levelscore-=9;
		else if(re>160)
			levelscore-=5;
		else if(re>140)
			levelscore-=3;
		if(re<0.1)
			levelscore=21;
		//stragey                                                ������
		if(info.towerInfo[T2].strategy==Grow||info.towerInfo[T2].strategy==Normal)
			strategyscore=20;
		if(info.towerInfo[T2].strategy==Attack)
			strategyscore=10;

		//e_zhi
		int uui=0;
		int killyou=-5;
		for (int i = 0; i < 4; i++)
			if(i!=info.myID&&his_to_me(info,i)>uui)
				uui=his_to_me(info,i);
		if(uui>1)
		{
			for (int i = 0; i < 4; i++)
				if(i!=info.myID&&his_to_me(info,i)==uui)
				{
					killyou=i;
					break;
				}
		}
		int tar=-1;  //��ʱ�������ѡ��
		if(info.playerInfo[info.myID].rank==1)
		{
			for (int j = 0; j < 4; j++)
			{
				if(info.playerInfo[j].rank==2)
				{
					tar=j;
					break;
				}
			}
		}
		else if(info.playerInfo[info.myID].rank==2)
		{
			for (int j = 0; j < 4; j++)
			{
				if(info.playerInfo[j].rank==1)
				{
					tar=j;
					break;
				}
			}		
		}
		if(info.towerInfo[T2].owner==tar)
		{
			ezhi_score=13;
		}
		else if(info.towerInfo[T2].owner==killyou)
		{
			ezhi_score=8;
		}
		else 
		{
			for (int i = 0; i < 13; i++)
			{
				if((info.towerInfo[i].owner==killyou||info.towerInfo[i].owner==tar)&&info.lineInfo[T2][i].exist==1&&info.lineInfo[T2][i].state!=AfterCut&&info.towerInfo[T2].resource>info.towerInfo[i].resource)
					ezhi_score-=10;
			}
		}
		ezhi_score+=his_to_me(info,info.towerInfo[T2].owner)*5;
		//most important    zhanlue 
		int jiaoji=0;
		for (int u = 0; u < 13; u++)
		{
			if(info.towerInfo[u].owner==info.myID&&((info.lineInfo[u][T2].exist&&info.lineInfo[u][T2].state!=AfterCut)||
			(info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)))
			{
				jiaoji++;
				if(info.towerInfo[T2].strategy==Attack&&info.towerInfo[u].strategy==Grow&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
				else if(info.towerInfo[T2].strategy==Grow&&info.towerInfo[u].strategy==Defence&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
			}
		}//�����Ǻ��ҵĽ���
		if(jiaoji>=4)
			zhanlue_score_jiaoji=20;
		else if(jiaoji==3)
			zhanlue_score_jiaoji=17;
		else if(jiaoji==2)
			zhanlue_score_jiaoji=14;
		else if(jiaoji==1)
			zhanlue_score_jiaoji=9;
		else
			zhanlue_score_jiaoji=0;


		//�����Ǳ��˴����ı���  ����help
		if(bingxian==0)
			zhanlue_score_nijiang=20;
		else if(bingxian==1)
			zhanlue_score_nijiang=17;
		else if(bingxian<2.6)
			zhanlue_score_nijiang=12;
		else
			zhanlue_score_nijiang=0;


		//ʳ�����ǿ����Ա���  �ر��Ƕ��ҵ����  ʳ������Ҫ�ۺ��ж�
		double shuchu=0;
		for (int r = 0; r < 13; r++)
		{
			if(info.towerInfo[r].owner==info.towerInfo[T2].owner&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
				shuchu+=1;
			if(info.towerInfo[r].owner!=info.towerInfo[T2].owner&&info.towerInfo[r].owner!=info.myID&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
			{
				if(info.lineInfo[r][T2].exist==1)
				{
					if(ezhi_score>15) shuchu+=1.5;
					else shuchu+=1;
				}
				else
				{
					if(ezhi_score>15) shuchu+=1;
					else shuchu+=0.6;
				}		
			}
			if(info.towerInfo[r].owner==info.myID&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
			{
				shuchu+=2;
				if(info.towerInfo[T2].strategy==Attack&&info.towerInfo[r].strategy==Grow)
					shuchu+=1;
				if(info.towerInfo[T2].strategy==Grow&&info.towerInfo[r].strategy==Defence)
					shuchu+=1;
			}
			if(info.towerInfo[r].owner==info.myID&&info.lineInfo[T2][r].exist==0&&info.lineInfo[r][T2].exist==1&&info.lineInfo[r][T2].state!=AfterCut)
				shuchu+=1;
		}
		if(shuchu>=4.6)
			zhanlue_score_shiwulian=20;
		else if(shuchu>=3.9)
			zhanlue_score_shiwulian=18;
		else if(shuchu>1.9)
			zhanlue_score_shiwulian=3.5*shuchu+3.35;
		else if(shuchu>0.8)
			zhanlue_score_shiwulian=5.714*shuchu-1.7142;
		else
			zhanlue_score_shiwulian=0;
		if(numm>=5)
		{
			scc=0.26*levelscore+0.20*distance_socre+0.17*ezhi_score+0.04*strategyscore+0.18*zhanlue_score_shiwulian+0.15*zhanlue_score_nijiang;
			scc*=5;
			if(scc>67.5)
			{
				scc=constrain(scc,60,100)+(rand()%100)/100.0+30;
				goto last;
			}
			else
				scc=0;
		}

		if(zhanlue_score_jiaoji>15)
		{
			if(!(levelscore<5&&distance_socre<5))
			{
				scc=80+0.25*levelscore+0.25*distance_socre;
				goto last;
			}
		}
		if(levelscore>14.5)
		{
			double temp=0;
			temp=0.1*ezhi_score+0.3*distance_socre+0.22*levelscore+0.1*strategyscore+0.15*zhanlue_score_shiwulian+0.13*zhanlue_score_nijiang;
			temp*=5;
			if(temp>60)
			{
				scc=temp*0.1+70;
				goto last;
			}
		}
		if((zhanlue_score_nijiang>15&&zhanlue_score_shiwulian>10)||(zhanlue_score_nijiang>9&&zhanlue_score_shiwulian>14.5)||zhanlue_score_shiwulian>17.5)
		{
			double temp=0;
			temp=0.1*ezhi_score+0.3*distance_socre+0.3*levelscore+0.1*strategyscore+0.1*zhanlue_score_jiaoji;	
			temp*=5;
			if(temp>40)
			{
				scc=temp*0.1+60;
				goto last;
			}
		}
		if(ezhi_score>15&&zhanlue_score_shiwulian>14.5&&distance_socre>14&&levelscore>11&&info.playerInfo[info.myID].rank<=2&&numm>=4.5)
		{
			scc=60.1;
			goto last;
		}
		if(player_towernum(info,info.myID)>=9&&player_resource(info,info.myID)/all_resource(info)>0.65)
		{
			scc=levelscore+distance_socre+100;
			goto last;
		}
last:
		if(numm<5)
		{
			if(scc<55)
			{
				scc=0.32*levelscore+0.26*distance_socre+0.05*ezhi_score+0.04*strategyscore+0.20*zhanlue_score_shiwulian+0.13*zhanlue_score_nijiang;
				scc*=5;
				if(scc>64)
				{
					scc=constrain(scc,60,100)+(rand()%100)/100.0+30;
				}
				else
					scc=0;
			}
		}
		towerfen[T2]=(scc>55)?(scc):0;
		/*ofstream log("budao_fenpei.txt",ios::app);
		log<<info.round<<"*"<<T2<<endl;
		log<<"scc"<<scc<<endl;
		log<<"distance_socre"<<distance_socre<<"strategyscore"<<strategyscore<<"levelscore"<<levelscore<<
			"zhanlue_score_shiwulian"<<zhanlue_score_shiwulian<<"zhanlue_score_jiaoji"<<zhanlue_score_jiaoji<<
			"zhanlue_score_nijiang"<<zhanlue_score_nijiang<<"ezhi_score"<<ezhi_score<<endl;
		log.close();*/
	}

	if(_my_now_budao_target==-1&&_my_now_vice_target!=-1)
	{
		_my_now_budao_target=_my_now_vice_target;
		_budao_attack_round=0;	
		_my_now_vice_target=-1;
		_budao_vice_attack_round=0;
	/*	ofstream log("budao_fenpei_tar2.txt",ios::app);
		log<<info.round<<"*"<<_my_now_budao_target<<endl;
		log.close();*/
		_budao_fenpei_log[info.round]=_my_now_budao_target;
		return 1;
	}
	double com=1;

	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com)
			com=towerfen[p];
	}
	if(com<35)
	{
		_my_now_budao_target=-1;
		return 0;
	}
	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com-0.01&&towerfen[p]<com+0.01)
		{
	/*		ofstream log("budao_fenpei_tar.txt",ios::app);
			log<<info.round<<"*"<<p<<endl;
			log.close();*/
			_budao_fenpei_log[info.round]=p;
			if(_budao_fenpei_log[info.round-1]==p)
			{
				_my_now_budao_target=p;
				return 1;
			}
			else
				break;
		}
	}
	_my_now_budao_target=-1;
	return 0;
}
int budao_fenpei_for2(Info& info)
{
	int towerfen[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	if(_my_now_budao_target!=-1)
	{
		fileout("asgsd258htuj","error.txt");
		return 0;
	}
	int numm=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
			numm++;
	}

	//�ۺϾ���
	double y1=towery(info);
	double x1=towerx(info);
	TPoint aver;
	aver.m_x=x1;
	aver.m_y=y1;
	int x=0;
	for (int p = 0; p < 13; p++)
		if(info.towerInfo[p].owner==info.myID)
			x++;	

		//��ʽ����
	for (int T2 = 0; T2 < 13; T2++)
	{
		double distance_socre=0;//20
		double strategyscore=0;//10
		double levelscore=0;//10
		double zhanlue_score_shiwulian=0;
		double zhanlue_score_jiaoji=0;
		int attacker[4]={0,0,0,0};
		int all[4]={0,0,0,0};
		double scc=0;

		if(info.towerInfo[T2].owner==info.myID||info.towerInfo[T2].owner==-1)
		{
			towerfen[T2]=0;
			continue;
		}
		else
		{
			for (int j = 0; j < 13; j++)
			{
				if(j!=T2&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut)
					attacker[info.towerInfo[j].owner]+=1;
				if(j!=T2&&info.towerInfo[j].owner!=-1&&((info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut)||(info.lineInfo[T2][j].exist==1&&info.lineInfo[T2][j].state!=AfterCut)))
				{
					all[info.towerInfo[j].owner]+=1;
					if(info.towerInfo[j].owner==info.myID&&info.lineInfo[T2][j].exist==1&&info.towerInfo[T2].strategy==Attack&&info.towerInfo[j].strategy==Grow&&info.lineInfo[T2][j].state!=AfterCut)
						all[info.towerInfo[j].owner]+=1;
				}
			}
		}

		int count=0;
		int nitan=0;
		int bingxian=0;
		for (int k = 0; k < 4; k++)
		{
			if(attacker[k]>0&&k!=info.myID)
			{
				bingxian+=attacker[k];
				count++;
			}
			if(attacker[k]>=2&&k!=info.myID)
				nitan=1;
		}
		bingxian-=attacker[info.myID];
		bingxian=constrain(bingxian,0,6);
		double dis=0;
			//�ۺϾ���
		if(aver.m_x<0.1||aver.m_y<0.1)
		{
			distance_socre=0;
			fileout("sa3f","error.txt");			fileout(info.round,"error.txt");
			fileout(aver.m_x,"s",aver.m_y,"error.txt");
		}
		else
		{
			dis=getDistance(aver,info.towerInfo[T2].position);
			if(dis>700)
				distance_socre=1;
			else if(dis>601)
				distance_socre=1;
			else if(dis>550)
				distance_socre=3;
			else if(dis>500)
				distance_socre=7;
			else if(dis>450)
				distance_socre=10;
			else if(dis>400)
				distance_socre=13;
			else if(dis>350)
				distance_socre=16;
			else if(dis>300)
				distance_socre=18;
			else
				distance_socre=20;
		}
		//level
		double re=info.towerInfo[T2].resource;
		double consume=each_round_consume(info,T2);
		consume=constrain(consume,-30,7);
		double round=dis*0.1/(3.0*SpeedStage[info.playerInfo[info.myID].ExtendingSpeedLevel]);
		re=re-round*constrain(consume,-55,0);
		re=constrain(re,0.1,200);
		if(re<45)
			levelscore=20;
		else if(re<80)
			levelscore=((-1)*0.1)*re+23;
		else if(re<300)
			levelscore=(-1)*0.08571428571428572*re+17.857142857142858;
		levelscore=constrain(levelscore,0,20);
		if(re<0.1)
			levelscore=21;

		//stragey                                                ������
		if(info.towerInfo[T2].strategy==Grow||info.towerInfo[T2].strategy==Normal)
			strategyscore=20;
		if(info.towerInfo[T2].strategy==Attack)
			strategyscore=10;


		//most important    zhanlue 
		int jiaoji=0;
		for (int u = 0; u < 13; u++)
		{
			if(info.towerInfo[u].owner==info.myID&&((info.lineInfo[u][T2].exist&&info.lineInfo[u][T2].state!=AfterCut)||
			(info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)))
			{
				jiaoji++;
				if(info.towerInfo[T2].strategy==Attack&&info.towerInfo[u].strategy==Grow&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
				else if(info.towerInfo[T2].strategy==Grow&&info.towerInfo[u].strategy==Defence&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
			}
		}//�����Ǻ��ҵĽ���
		if(jiaoji>=4)
			zhanlue_score_jiaoji=20;
		else if(jiaoji==3)
			zhanlue_score_jiaoji=17;
		else if(jiaoji==2)
			zhanlue_score_jiaoji=14;
		else if(jiaoji==1)
			zhanlue_score_jiaoji=9;
		else
			zhanlue_score_jiaoji=0;

		//ʳ�����ǿ����Ա���  �ر��Ƕ��ҵ����  ʳ������Ҫ�ۺ��ж�
		int shuchu=0;
		for (int r = 0; r < 13; r++)
		{
			if(info.towerInfo[r].owner!=info.myID&&r!=T2)
			{
				if(info.lineInfo[r][T2].exist==1&&info.lineInfo[r][T2].state!=AfterCut)
					shuchu--;
				if(info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
					shuchu++;
			}
		}
		if(shuchu>=3)
			zhanlue_score_shiwulian=21;
		else if(shuchu>=2)
			zhanlue_score_shiwulian=18;
		else if(shuchu>=1)
			zhanlue_score_shiwulian=14;
		else if(shuchu>=0)
			zhanlue_score_shiwulian=11;
		else if(shuchu>=-1)
			zhanlue_score_shiwulian=8;
		else if(shuchu>=-2)
			zhanlue_score_shiwulian=4;
		else
			zhanlue_score_shiwulian=0;

		if(zhanlue_score_jiaoji>15)
		{
				scc=90+0.25*distance_socre+0.25*levelscore;
				goto last;
		}
		if(levelscore>14.5&&zhanlue_score_shiwulian>=8)
		{
			double temp=0;
			temp=distance_socre+zhanlue_score_shiwulian;
			temp*=5;
			if(distance_socre)
			{
				scc=temp*0.1+80;
				goto last;
			}
		}
last:
		if(scc<55)
		{
			scc=0.3*levelscore+0.2*distance_socre+0.2*strategyscore+0.15*zhanlue_score_shiwulian+0.15*zhanlue_score_jiaoji;
			scc*=5;
			if(scc>50)
			{
				scc+=15;
				scc=constrain(scc,50,100);
			}
			else
				scc=0;
		}
		towerfen[T2]=(scc>55)?(scc):0;
		
		/*ofstream log("budao_fenpei2.txt",ios::app);
		log<<info.round<<"*"<<T2<<endl;
		log<<"scc"<<scc<<endl;
		log<<"distance_socre"<<distance_socre<<"strategyscore"<<strategyscore<<"levelscore"<<levelscore<<
			"zhanlue_score_shiwulian"<<zhanlue_score_shiwulian<<"zhanlue_score_jiaoji"<<zhanlue_score_jiaoji<<endl;
		log.close();*/
	}

	if(_my_now_budao_target==-1&&_my_now_vice_target!=-1)
	{
		_my_now_budao_target=_my_now_vice_target;
		_budao_attack_round=0;	
		_my_now_vice_target=-1;
		_budao_vice_attack_round=0;
		/*ofstream log("budao_fenpei_tar2.txt",ios::app);
		log<<info.round<<"*"<<_my_now_budao_target<<endl;
		log.close();*/
		return 1;
	}
	double com=1;

	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com)
			com=towerfen[p];
	}
	if(com<35)
	{
		_my_now_budao_target=-1;
		return 0;
	}
	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com-0.01&&towerfen[p]<com+0.01)
		{
			/*ofstream log("budao_fenpei_tar2.txt",ios::app);
			log<<info.round<<"*"<<p<<endl;
			log.close();*/
			_budao_fenpei_log[info.round]=p;
			if(_budao_fenpei_log[info.round-1]==p)
			{
				_my_now_budao_target=p;
				return 1;
			}
			else
				break;
		}
	}
	_my_now_budao_target=-1;
	return 0;
}
int budao_fenpei_vice(Info& info)
{
	if(_my_now_vice_target!=-1)
	{
		fileout("asgsdtryhdhtuj","error.txt");
		return 0;
	}
	if(_my_now_budao_target==-1)
	{
		fileout("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","error.txt");
		return 0;
	}
	int towerfen[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	if(info.round<55)   
	{
		_my_now_vice_target=-1;
		return 0;
	}
	if(_budao_attack_round<5)
	{
		_my_now_vice_target=-1;
		return 0;	
	}
	if(jizhonggongji_daifenpei[0]!=-1)
		fileout("dattttttttttttttttttttttttta","error.txt");
	jizhonggongji_members_find(info);
	int allnum=0;
	for (int i = 0; i < 13; i++)
	{
		if(jizhonggongji_daifenpei[i]!=-1)
			allnum++;
		else
			break;
	}
	if(allnum<3)
	{
		_my_now_vice_target=-1;
		for (int i = 0; i < 13; i++)
			jizhonggongji_daifenpei[i]=-1;
		return 0;	
	}
	double allre=0;
	for (int i = 0; i < allnum; i++)
		allre+=info.towerInfo[jizhonggongji_daifenpei[i]].resource;
	//1.Э��������  ��֧Ԯ����С͵��    2.��level��disΪ��Ҫ����Ŀ��  �����������  3.ѡ�����������Ϊţ����  4.�������Ӷ��Ʒ�չ����������һ�������׳�н����ѩ�ϼ�˪
	//
	//ji������
	int numm=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
			numm++;
	}
	//�ۺϾ���
	double y1=towery(info);       //����ô�ð�
	double x1=towerx(info);
	TPoint aver;

	aver.m_x=x1;
	aver.m_y=y1;
	int x=0;
	for (int p = 0; p < 13; p++)
		if(info.towerInfo[p].owner==info.myID)
			x++;	

		//��ʽ����
	for (int T2 = 0; T2 < 13; T2++)
	{
		double rebi=info.towerInfo[T2].resource/allre;
		double distance_socre=0;//20
		double strategyscore=0;//10
		double levelscore=0;//10
		double zhanlue_score_shiwulian=0;
		double zhanlue_score_nijiang=0;
		double zhanlue_score_jiaoji=0;
		double ezhi_score=0;//
		int attacker[4]={0,0,0,0};
		int all[4]={0,0,0,0};
		double scc=0;
		if(T2==_my_now_budao_target)
		{
			towerfen[T2]=0;
			continue;
		}
		if(rebi>0.3333)
		{
			towerfen[T2]=0;
			continue;
		}
		if(info.towerInfo[T2].owner==info.myID||info.towerInfo[T2].owner==-1)
		{
			towerfen[T2]=0;
			continue;
		}
		else
		{
			for (int j = 0; j < 13; j++)
			{
				if(j!=T2&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut&&info.lineInfo[j][T2].resource*10>=info.lineInfo[j][T2].maxlength/2.0+10)
					attacker[info.towerInfo[j].owner]+=1;
				if(j!=T2&&info.towerInfo[j].owner!=-1&&((info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut)||(info.lineInfo[T2][j].exist==1&&info.lineInfo[T2][j].state!=AfterCut)))
				{
					all[info.towerInfo[j].owner]+=1;
					if(info.towerInfo[j].owner==info.myID&&info.lineInfo[T2][j].exist==1&&info.towerInfo[T2].strategy==Attack&&info.towerInfo[j].strategy==Grow&&info.lineInfo[T2][j].state!=AfterCut)
						all[info.towerInfo[j].owner]+=1;
				}
			}
		}
		int count=0;
		int nitan=0;
		int bingxian=0;
		for (int k = 0; k < 4; k++)
		{
			if(attacker[k]>0&&k!=info.myID)
			{
				bingxian+=attacker[k];
				count++;
			}
			if(attacker[k]>=2&&k!=info.myID)
				nitan=1;
		}
		bingxian-=attacker[info.myID];
		bingxian=constrain(bingxian,0,6);
		if(count>=2||nitan==1||bingxian>=3)
		{
			towerfen[T2]=0;
			continue;
		}
		double dis=0;
			//�ۺϾ���
		if(aver.m_x<0.1||aver.m_y<0.1)
		{
			distance_socre=0;
			fileout("s6af","error.txt");
		}
		else
		{
			dis=getDistance(aver,info.towerInfo[T2].position);
			if(dis>500)
			{
				towerfen[T2]=0;
				continue;
			}
			if(dis>700)
				distance_socre=1;
			else if(dis>601)
				distance_socre=1;
			else if(dis>550)
				distance_socre=3;
			else if(dis>500)
				distance_socre=7;
			else if(dis>450)
				distance_socre=10;
			else if(dis>400)
				distance_socre=13;
			else if(dis>350)
				distance_socre=16;
			else if(dis>300)
				distance_socre=18;
			else
				distance_socre=20;
		}
	
		//level
		double re=info.towerInfo[T2].resource;
		double consume=each_round_consume(info,T2);
		consume=constrain(consume,-30,7);
		double round=dis*0.1/(3.0*SpeedStage[info.playerInfo[info.myID].ExtendingSpeedLevel]);
		re=re-round*constrain(consume,-55,0);
		re=constrain(re,0.1,200);
		if(re<45)
			levelscore=20;
		else if(re<80)
			levelscore=((-1)*0.1)*re+23;
		else if(re<300)
			levelscore=(-1)*0.08571428571428572*re+17.857142857142858;
		levelscore=constrain(levelscore,0,20);
		if(re>180)
			levelscore-=9;
		else if(re>160)
			levelscore-=5;
		else if(re>140)
			levelscore-=2;
		if(re<0.1)
			levelscore=21;
		//stragey                                                ������
		if(info.towerInfo[T2].strategy==Grow||info.towerInfo[T2].strategy==Normal)
			strategyscore=20;
		if(info.towerInfo[T2].strategy==Attack)
			strategyscore=10;

		//e_zhi
		int tar=-1;  //��ʱ�������ѡ��
		if(info.playerInfo[info.myID].rank==1)
		{
			for (int j = 0; j < 4; j++)
			{
				if(info.playerInfo[j].rank==2)
				{
					tar=j;
					break;
				}
			}
		}
		else if(info.playerInfo[info.myID].rank==2)
		{
			for (int j = 0; j < 4; j++)
			{
				if(info.playerInfo[j].rank==1)
				{
					tar=j;
					break;
				}
			}		
		}
		if(info.towerInfo[T2].owner==tar&&player_resource(info,info.towerInfo[T2].owner)/all_resource(info)<0.55)
			ezhi_score=20;

		//most important    zhanlue 
		int jiaoji=0;
		for (int u = 0; u < 13; u++)
		{
			if(info.towerInfo[u].owner==info.myID&&((info.lineInfo[u][T2].exist&&info.lineInfo[u][T2].state!=AfterCut)||
			(info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)))
			{
				jiaoji++;
				if(info.towerInfo[T2].strategy==Attack&&info.towerInfo[u].strategy==Grow&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
				else if(info.towerInfo[T2].strategy==Grow&&info.towerInfo[u].strategy==Defence&&info.lineInfo[T2][u].exist&&info.lineInfo[T2][u].state!=AfterCut)
					jiaoji+=1;
			}
		}//�����Ǻ��ҵĽ���
		if(jiaoji>=4)
			zhanlue_score_jiaoji=20;
		else if(jiaoji==3)
			zhanlue_score_jiaoji=17;
		else if(jiaoji==2)
			zhanlue_score_jiaoji=14;
		else if(jiaoji==1)
			zhanlue_score_jiaoji=9;
		else
			zhanlue_score_jiaoji=0;

//                                           This is the final release of the zuc5.5 version 7
		//�����Ǳ��˴����ı���  ����help
		if(bingxian==0)
			zhanlue_score_nijiang=20;
		else if(bingxian==1)
			zhanlue_score_nijiang=18;
		else if(bingxian<2.6)
			zhanlue_score_nijiang=13;
		else
			zhanlue_score_nijiang=0;


		//ʳ�����ǿ����Ա���  �ر��Ƕ��ҵ����  ʳ������Ҫ�ۺ��ж�
		double shuchu=0;
		for (int r = 0; r < 13; r++)
		{
			if(info.towerInfo[r].owner==info.towerInfo[T2].owner&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
				shuchu+=1;
			if(info.towerInfo[r].owner!=info.towerInfo[T2].owner&&info.towerInfo[r].owner!=info.myID&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
			{
				if(info.lineInfo[r][T2].exist==1)
				{
					if(ezhi_score>15) shuchu+=1.5;
					else shuchu+=1;
				}
				else
				{
					if(ezhi_score>15) shuchu+=1;
					else shuchu+=0.6;
				}		
			}
			if(info.towerInfo[r].owner==info.myID&&info.lineInfo[T2][r].exist==1&&info.lineInfo[T2][r].state!=AfterCut)
			{
				shuchu+=2;
				if(info.towerInfo[T2].strategy==Attack&&info.towerInfo[r].strategy==Grow)
					shuchu+=1;
				if(info.towerInfo[T2].strategy==Grow&&info.towerInfo[r].strategy==Defence)
					shuchu+=1;
			}
			if(info.towerInfo[r].owner==info.myID&&info.lineInfo[T2][r].exist==0&&info.lineInfo[r][T2].exist==1&&info.lineInfo[r][T2].state!=AfterCut)
				shuchu+=1;
		}
		if(shuchu>=4.6)
			zhanlue_score_shiwulian=20;
		else if(shuchu>=3.9)
			zhanlue_score_shiwulian=18;
		else if(shuchu>1.9)
			zhanlue_score_shiwulian=3.5*shuchu+3.35;
		else if(shuchu>0.8)
			zhanlue_score_shiwulian=5.714*shuchu-1.7142;
		else
			zhanlue_score_shiwulian=0;
		
		if(zhanlue_score_jiaoji>15)
		{
			if(!(levelscore<5&&distance_socre<5))
			{
				scc=90+0.25*levelscore+0.25*distance_socre;
				goto last;
			}
		}	
		//1.Э��������  ��֧Ԯ����С͵��    2.��level��disΪ��Ҫ����Ŀ��  �����������  3.ѡ�����������Ϊţ����  4.�������Ӷ��Ʒ�չ����������һ�������׳�н����ѩ�ϼ�˪
		if(info.lineInfo[T2][_my_now_budao_target].exist==1&&info.lineInfo[T2][_my_now_budao_target].state!=AfterCut&&ezhi_score>10&&levelscore>3.3&&dis<500)
		{
			double yy=0.25*distance_socre+0.35*levelscore+0.1*zhanlue_score_nijiang+0.1*strategyscore+0.2*zhanlue_score_nijiang;
			scc=80+0.45*yy;
			goto last;
		}
		if(T2==12&&zhanlue_score_nijiang>16)
		{
			scc=70+0.5*(0.5*zhanlue_score_shiwulian+0.5*ezhi_score);
			goto last;
		}

last:
		if(scc<55)
		{
			if(levelscore>5&&dis<400&&ezhi_score>10)
				scc=65+0.25*(0.25*levelscore+0.2*distance_socre+0.3*ezhi_score+0.15*zhanlue_score_nijiang+0.1*20*(info.lineInfo[T2][_my_now_budao_target].exist==1&&info.lineInfo[T2][_my_now_budao_target].state!=AfterCut));
			else if(levelscore>14.5&&dis<400)
				scc=65+0.25*(0.15*levelscore+0.35*distance_socre+0.3*zhanlue_score_nijiang+0.2*20*(info.lineInfo[T2][_my_now_budao_target].exist==1&&info.lineInfo[T2][_my_now_budao_target].state!=AfterCut));
			if(scc>65)
			{
				int test=((int)(time(0)))%12;
				if(test<0||test>12||test%1!=0)
					fileout("shit","error.txt");
				scc=constrain(scc,60,70)+info.towerInfo[test].resource/100;
			}
			else
				scc=0;
		}
		if(scc<50)
		{
			if(numm>=10)
			{
				scc=fence+10+(rand()%100);
			}
			else
				scc=0;
		}
		towerfen[T2]=(scc>55)?(scc):0;
		/*ofstream log("budao_fenpei_vice.txt",ios::app);
		log<<info.round<<"*"<<T2<<endl;
		log<<"scc"<<scc<<endl;
		log<<"distance_socre"<<distance_socre<<"strategyscore"<<strategyscore<<"levelscore"<<levelscore<<
			"zhanlue_score_shiwulian"<<zhanlue_score_shiwulian<<"zhanlue_score_jiaoji"<<zhanlue_score_jiaoji<<
			"zhanlue_score_nijiang"<<zhanlue_score_nijiang<<"ezhi_score"<<ezhi_score<<endl;
		log.close();*/
	}

	double com=1;

	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com)
			com=towerfen[p];
	}
	if(com<35)
	{
		_my_now_vice_target=-1;
		return 0;
	}
	for (int p = 0; p < 13; p++)
	{
		if(towerfen[p]>com-0.01&&towerfen[p]<com+0.01)
		{
		/*	ofstream log("budao_vice_fenpei_tar.txt",ios::app);
			log<<info.round<<"*"<<p<<endl;
			log.close();*/
			_budao_vice_fenpei_log[info.round]=p;
			if(_budao_vice_fenpei_log[info.round-1]==p)
			{
				_my_now_vice_target=p;
				return 1;
			}
			else
				break;
		}
	}
	_my_now_vice_target=-1;
	return 0;
}
int gamebegin(Info& info)
{
	if(_begin==1)
		return 1;
	if(info.round<30)
		return 0;
	if(info.round>55)
		return 1;
	double myre=0;
	int mytnum=0;
	double lre=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
		{
			myre+=info.towerInfo[i].resource;
			lre+=_last_round_resource[i];
			mytnum++;
		}
	}
	if(myre>455)
		return 1;
	int cccc=0;
	for (int i = 0; i < 12; i++)
	{
		if(info.towerInfo[i].owner!=info.myID)
			continue;
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner==info.myID||info.towerInfo[j].owner==-1)
				continue;
			if(info.lineInfo[j][i].exist==1&&info.lineInfo[j][i].state!=AfterCut&&(info.lineInfo[i][j].exist==1||(info.lineInfo[j][i].state==Arrived||coming_arrive_round(info,j,i)<6)))
				cccc++;
		}
	}
	if(cccc>=2)
		return 1;
	int oo[4]={0,0,0,0};
	if(info.towerInfo[12].owner==info.myID)
	{
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner==info.myID||info.towerInfo[j].owner==-1)
				continue;
			if(info.lineInfo[j][12].exist==1&&info.lineInfo[j][12].state!=AfterCut&&(info.lineInfo[j][12].state==Arrived||coming_arrive_round(info,j,12)<3.7))
				oo[info.towerInfo[j].owner]++;
		}
	}
	int bla=0;
	for (int i = 0; i < 4; i++)
	{
		if(bla>0)
			bla-=oo[i];
		else
			bla+=oo[i];
	}
	if(bla>=3||bla<=-3)
		return 1;
	//��Ҫʧȥս����ʼ����
	return 0;

}
void budao_brain(Info& info)
{
	if(info.round<30)    //�������ɶ�̬��
		return ;
	if(gamebegin(info)==0)
		return ;
	else
	{
		fileout(info.round,"begin.txt");
		_begin=1;
	}
	double gap=0;

	if(_my_now_budao_target==-1)
	{
			int n;//Ŀǰֻ��Ϊ-1ʱ���ܽ���
			if(info.playerAlive==2)
				n=budao_fenpei_for2(info);
			else
				n=budao_fenpei(info);

			if(n==1)
				_budao_attack_round=0;
	}
	else
	{
		if(_budao_attack_round>35)
		{
			_my_now_budao_target=-1;
			_budao_attack_round=0;
		}
		else
		{
			if(info.towerInfo[_my_now_budao_target].owner==info.myID)
			{
				_my_now_budao_target=-1;
				_budao_attack_round=0;
			}
		}		
	}
	//vice ����
	if(_my_now_budao_target!=-1&&_my_now_vice_target==-1&&_budao_attack_round>=5)
	{
		int n;//Ŀǰֻ��Ϊ-1ʱ���ܽ���
		n=budao_fenpei_vice(info);
		if(n==1)
			_budao_vice_attack_round=0;	
	}
	else if(_my_now_budao_target!=-1&&_my_now_vice_target!=-1&&_budao_attack_round>=5)
	{
		if(_budao_vice_attack_round>30)
		{
			_my_now_vice_target=-1;
			_budao_vice_attack_round=0;
		}
		else if(info.towerInfo[_my_now_vice_target].owner==info.myID)
			{
				_my_now_vice_target=-1;
				_budao_vice_attack_round=0;
			}		
	}

	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner!=info.myID)
			continue;
		gap=0;
		for(int j=0;j<13;j++)
			if(_added_lines_round[i][j][2]>gap)		
				gap=_added_lines_round[i][j][2];
		gap=info.round-gap;
		double consume=0;
		consume=each_round_consume(info,i);
		switch(_tower_way_index[i])
		{
		case jijin:
		case xiyinhuoli:
			for (int j = 0; j < 13; j++)
			{
				if(info.towerInfo[j].owner==-1||info.towerInfo[j].owner==info.myID||info.lineInfo[i][j].exist==1)
					continue;
				budao_evaluate_plus(info,i,j);
			}
			break;
		case baoshou:
		case touzhongta:
			for (int j = 0; j < 13; j++)
			{
				if(info.towerInfo[j].owner==-1||info.towerInfo[j].owner==info.myID||info.lineInfo[i][j].exist==1)
					continue;
				if(info.round<BUDAO_BEGIN_ROUND)
					continue;
				//�ڴ˴����з���������gap�ж�
				if(info.towerInfo[i].resource>=_budao_line[i]&&(gap>3||(info.towerInfo[i].resource>_danger_line[i]&&consume<2)))
					budao_evaluate_plus(info,i,j);
			}
			break;
		//����indexզ�죿����
		}
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if(j!=_my_now_budao_target&&j!=_my_now_vice_target)
			{
				_budao_evaluate_reference[i][j][0]=0;
				_budao_evaluate_reference[i][j][1]=0;
			}
		}		
	}
		//��ȫ�ֱ��������ֽ���
		//����Ƿ��ȡȺ��ģʽ������Ⱥ��ģʽ����΢��
	    //��׺Ϊ1������
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{//fence ����
			_budao_brain_outcome[i][j]=((_budao_evaluate_reference[i][j][0]>55)?(_budao_evaluate_reference[i][j][0]):0);
		}
	}
	int will_be_attacker_num=0;
	int will_be_attacker[13];
	double resourcebi=0;
	if(_my_now_budao_target!=-1)
	{
		//�ж���Щ����������
		//��ȷ����
		for (int m = 0; m < 13; m++)
		{
			if(_budao_brain_outcome[m][_my_now_budao_target]>56)
				_budao_brain_outcome[m][_my_now_budao_target]=80+(rand()%100)/33.0;   //����
		}

		for (int m = 0; m < 13; m++)
		{
			if(info.towerInfo[m].owner!=info.myID)
				continue;
			if(info.lineInfo[m][_my_now_budao_target].exist==1&&info.lineInfo[m][_my_now_budao_target].state!=AfterCut&&info.towerInfo[m].resource>35)
			{
				will_be_attacker[will_be_attacker_num]=m;
				will_be_attacker_num++;
				resourcebi+=info.towerInfo[m].resource+info.lineInfo[m][_my_now_budao_target].resource;
				continue;
			}
			if(_budao_brain_outcome[m][_my_now_budao_target]<50)
				continue;
			int o=0;
			for (o = 0; o < 13; o++)
			{
				if(_budao_brain_outcome[m][_my_now_budao_target]<_budao_brain_outcome[m][o]-0.04)
					break;
			}
			if(o!=13)
				continue;
			will_be_attacker[will_be_attacker_num]=m;
			will_be_attacker_num++;
			resourcebi+=info.towerInfo[m].resource;
		}
		//�ж��Ƿ���У�
		resourcebi=resourcebi/info.towerInfo[_my_now_budao_target].resource;
		if((will_be_attacker_num<(info.towerInfo[_my_now_budao_target].maxLineNum+1)&&resourcebi<2.8)||(will_be_attacker_num<(info.towerInfo[_my_now_budao_target].maxLineNum)&&resourcebi<2.2))
		{
			if(_budao_attack_round==0)
			{
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 13; j++)
					{
						_budao_brain_outcome[i][j]=((_budao_evaluate_reference[i][j][1]>55)?_budao_evaluate_reference[i][j][1]:0);
						if(j==_my_now_budao_target)
							_budao_brain_outcome[i][j]+=5;
					}
				}
				_tar_giveup_log[info.round]=_my_now_budao_target;
				_my_now_budao_target=-1;
				//��ȡһ���ж�    ���ǻ��Ǹ����target�ӳ�һ��������
			}
			else if(will_be_attacker_num<info.towerInfo[_my_now_budao_target].maxLineNum&&resourcebi<1.8)
			{
				_tar_giveup_log[info.round]=_my_now_budao_target;
				if(_tar_giveup_log[info.round-1]==_my_now_budao_target&&_tar_giveup_log[info.round-2]==_my_now_budao_target)
					_my_now_budao_target=-1;
			}

		}
		//���оͽ�����  ��ʱȥ����target���ķ����Ѿ�����30�� Ӧ������û������ ���������ʱ���빥����̫����Ҫ΢��ȥ��һ����
	}
	else//��û��ͳһ�Ƽ���ʱ��  Ҫ������ֹ������������
	{
	      ////////////////////////////

	}

	//vice bufen easy

	return;
}
double line_resource(Info &info,int tower)
{
	double resource=0;
	for(int i=0;i<info.towerNum;i++)
	{
		if(info.lineInfo[tower][i].exist)
		{
			if(info.lineInfo[tower][i].state==AfterCut)
				resource+=info.lineInfo[tower][i].backResource;
			else resource+=info.lineInfo[tower][i].resource;
		}
	}
	return resource;
}
int player_towernum(Info& info,int id)
{
	int bla=0;
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner==id)
			bla++;
	}
	return(bla);
}
double player_resource(Info& info,int id)
{
	double resource=0;
	for(int i=0;i<info.towerNum;i++)
	{
		if(info.towerInfo[i].owner==id)
			resource+=(info.towerInfo[i].resource+line_resource(info,i));
	}
	return resource;
}

double all_resource(Info& info)
{
	return player_resource(info,0)+player_resource(info,1)+player_resource(info,2)+player_resource(info,3);
}
void budao_evaluate_plus(Info& info,TTowerID T1,TTowerID T2,int method)       //������t2 �ڴ������  
{ 
	//fileout("*****",info.round,"hh","budao.txt");
	//fileout(T1,"budao",T2,"budao.txt");
	if(info.towerInfo[T1].owner==-1||info.towerInfo[T2].owner==-1)
	{
		_budao_evaluate_reference[T1][T2][0]=0;
		_budao_evaluate_reference[T1][T2][1]=0;
		return ;
	}
	if(info.lineInfo[T2][T1].exist==1)
	{
		_budao_evaluate_reference[T1][T2][0]=0;
		_budao_evaluate_reference[T1][T2][1]=0;
		return ;
	}
	if(method!=1)
	{
		if(info.lineInfo[T1][T2].exist==1)
		{
			_budao_evaluate_reference[T1][T2][0]=0;
			_budao_evaluate_reference[T1][T2][1]=0;
			return ;
		}
		if(addline_ok(info,T1,T2)!=0)
		{
			_budao_evaluate_reference[T1][T2][0]=0;
			_budao_evaluate_reference[T1][T2][1]=0;
			return ;
		}
	}
	double consume=each_round_consume(info,T1);
	if(consume>8.1)
	{
		_budao_evaluate_reference[T1][T2][0]=0;
		_budao_evaluate_reference[T1][T2][1]=0;
		return ;
	}
	//��̶׼��
	int attacker[4]={0,0,0,0};
	int all[4]={0,0,0,0};
	if(info.towerInfo[T2].owner!=info.myID&&info.towerInfo[T2].owner!=-1)
	{
		for (int j = 0; j < 13; j++)
		{
			if(j!=T2&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut&&info.lineInfo[j][T2].resource*10>=info.lineInfo[j][T2].maxlength/2.0+10)
				attacker[info.towerInfo[j].owner]+=1;
			if(j!=T2&&info.towerInfo[j].owner!=-1&&((info.lineInfo[j][T2].exist==1&&info.lineInfo[j][T2].state!=AfterCut)||(info.lineInfo[T2][j].exist==1&&info.lineInfo[T2][j].state!=AfterCut)))
			{
				all[info.towerInfo[j].owner]+=1;
				if(info.towerInfo[j].owner==info.myID&&info.lineInfo[T2][j].exist==1&&info.towerInfo[T2].strategy==Attack&&info.towerInfo[T2].strategy==Grow)
					all[info.towerInfo[j].owner]+=1;
			}
		}
	}
	int count=0;
	int nitan=0;
	int bingxian=0;
	for (int k = 0; k < 4; k++)
	{
		if(attacker[k]>0&&k!=info.myID)
		{
			bingxian+=attacker[k];
			count++;
		}
		if(attacker[k]>=3&&k!=info.myID)
			nitan=1;
	}
	bingxian-=attacker[info.myID];
	bingxian=constrain(bingxian,0,6);
	if(count>=2||nitan==1||bingxian>=4)
	{
		_budao_evaluate_reference[T1][T2][0]=0;
		_budao_evaluate_reference[T1][T2][1]=0;
		return ;
	}
	//����һֱ�ӱ���
	int temp=0;
	for (int k = 0; k < 13; k++)
	{
		if(info.lineInfo[k][T1].exist==1&&info.towerInfo[k].owner!=info.myID&&info.lineInfo[k][T1].state!=AfterCut)
			temp++;
	}
	if(temp>=info.towerInfo[T1].maxLineNum)
	{
		_budao_evaluate_reference[T1][T2][0]=0;
		_budao_evaluate_reference[T1][T2][1]=0;
		return;
	}
	//��ʽ����
	double dis=getDistance(info.towerInfo[T1].position,info.towerInfo[T2].position);
	double power=info.towerInfo[T2].resource/info.towerInfo[T1].resource;
	double money1=money(info,T2);
	double possible_fightback_socre=0;
	double resource_score=0;
	double distance_socre=0;
	double money_score=0;
	double lianxi_socre=0;
	double score=0;

		// possible_fight
		if(addline_ok(info,T2,T1,1)==0)
		{
			if(info.towerInfo[T1].strategy==info.towerInfo[T2].strategy)
				possible_fightback_socre=20;
			else if(info.towerInfo[T1].strategy==Attack&&info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=30;
			else if(info.towerInfo[T1].strategy==Attack&&info.towerInfo[T2].strategy==Defence)
				possible_fightback_socre=9;			
			else if(info.towerInfo[T1].strategy==Defence&&info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=7;
			else if(info.towerInfo[T1].strategy==Defence&&info.towerInfo[T2].strategy==Attack)
				possible_fightback_socre=20;
			else if(info.towerInfo[T1].strategy==Grow&&info.towerInfo[T2].strategy==Defence)
				possible_fightback_socre=25;
			else if(info.towerInfo[T1].strategy==Grow&&info.towerInfo[T2].strategy==Attack)
				possible_fightback_socre=0;
			else if(info.towerInfo[T1].strategy==Normal)
				possible_fightback_socre=6;
			else if(info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=23;
		}
		else
		{
			if(info.towerInfo[T1].strategy==info.towerInfo[T2].strategy)
				possible_fightback_socre=23;
			else if(info.towerInfo[T1].strategy==Attack&&info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=34;
			else if(info.towerInfo[T1].strategy==Attack&&info.towerInfo[T2].strategy==Defence)
				possible_fightback_socre=14;			
			else if(info.towerInfo[T1].strategy==Defence&&info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=10;
			else if(info.towerInfo[T1].strategy==Defence&&info.towerInfo[T2].strategy==Attack)
				possible_fightback_socre=25;
			else if(info.towerInfo[T1].strategy==Grow&&info.towerInfo[T2].strategy==Defence)
				possible_fightback_socre=30;
			else if(info.towerInfo[T1].strategy==Grow&&info.towerInfo[T2].strategy==Attack)
				possible_fightback_socre=7;		
			else if(info.towerInfo[T1].strategy==Normal)
				possible_fightback_socre=10;
			else if(info.towerInfo[T2].strategy==Grow)
				possible_fightback_socre=27;
		}
		//һ������
		possible_fightback_socre*=0.7;
		//distance_score
		if(dis>700)
			distance_socre=0;
		else if(dis>601)
			distance_socre=5;
		else if(dis>500)
			distance_socre=10;
		else
			distance_socre=15;


	if(1)
	{
		if(each_round_consume(info,T2)<-7&&_my_now_budao_target!=T2)
		{
			_budao_evaluate_reference[T1][T2][0]=0;
			_budao_evaluate_reference[T1][T2][1]=0;			
			return;
		}
		//resource_score
			resource_score=25*power-30;
			if(resource_score<0)
				resource_score=0;
			else if(resource_score>20)
				resource_score=20;
		//money
		if(money1>59)
			money_score=15;
		else if(money1>40)
			money_score=11;
		else if(money1>20)
			money_score=7;
		else
			money_score=0;
		//lianxi
		if(all[info.myID]>0.98)
			lianxi_socre=15;
		else if(all[info.myID]>=1.98)
			lianxi_socre=23;
		else
			lianxi_socre=0;
		//  num1 ����
		if(info.playerInfo[info.towerInfo[T2].owner].rank==1)            //����������
			lianxi_socre+=6;
		if(lianxi_socre>23)
			lianxi_socre=23;

		score=possible_fightback_socre+distance_socre+lianxi_socre+money_score+resource_score;
		if(each_round_consume(info,T2)<-7&&_my_now_budao_target==T2)
		{
			score=0;
		}
		if(info.towerInfo[T2].strategy==Attack)
		{
			for (int m = 0; m <13; m++)
			{
				if(info.towerInfo[m].owner==info.myID&&info.towerInfo[m].strategy==Grow&&info.lineInfo[T2][m].exist==1)
				{
					score+=9;
					break;
				}
			}
		}
	}
	double score0=0;
	if(_my_now_budao_target==T2)
	{
		double need=dis/10;
		double myleft=info.towerInfo[T1].resource-need-arrive_round(info,T1,T2)*each_round_consume(info,T1);
		if(myleft<_danger_line[T1]*0.8)
		{
			_budao_evaluate_reference[T1][T2][0]=0;
			_budao_evaluate_reference[T1][T2][1]=0;
			return;
		}
		// resourece  
		double cha=0.9*info.towerInfo[T1].maxResource-_budao_line[T1];
		resource_score=15*(info.towerInfo[T1].resource-_budao_line[T1])/cha;
		possible_fightback_socre*=0.5;
		score0=45+possible_fightback_socre+distance_socre+resource_score;
	}
	else
	{
		score0=score;
	}
	if(_my_now_vice_target==T2)
	{
		int flag=0;
		int p=0;
		while(jizhonggongji_daifenpei[p]!=-1)
		{
			if(T1==jizhonggongji_daifenpei[p])
				flag=1;
			p++;
		}
		if(flag==1)
		{
			score=80+(rand()%100)/50.0;
			score0=81+(rand()%100)/50.0;
		}
	}
	/*ofstream log("budao_plus.txt",ios::app);
	log<<info.round<<"*"<<T1<<"*"<<T2<<endl;
	log<<"possible_fightback_socre"<<possible_fightback_socre<<"resource_score"<<resource_score<<"distance_socre"<<distance_socre<<
		"money_score"<<money_score<<"lianxi_socre"<<lianxi_socre<<endl;
	log<<"score"<<score<<"score0"<<score0<<endl;
	log.close();*/
	_budao_evaluate_reference[T1][T2][0]=score0;
	_budao_evaluate_reference[T1][T2][1]=score;
	return;
}
double budao_evaluate_new(Info& info,TTowerID T1,TTowerID T2)
{
	return(_budao_brain_outcome[T1][T2]+fence-55);
}
void lines_for_towers_init(Info& info)
{
	const int times=2;
	double power=0;
	double dis=0;
	double sum=0;
	double dangerline=0;
	double budaoline=0;
	for (int i = 0; i < 13; i++)
	{
		_danger_line[i]=0;
		_budao_line[i]=0;
	}
//                                           This is the final release of the zuc5.5 version 8
	for (int i = 0; i < 13; i++)
	{
		if(info.towerInfo[i].owner!=info.myID)
			continue;
		for (int j = 0; j < 13; j++)
		{
			if(info.towerInfo[j].owner==info.myID||info.towerInfo[j].owner==-1)
				continue;
			dis=getDistance(info.towerInfo[i].position,info.towerInfo[j].position);
			dis/=100;
			power+=pow(dis,times);
			sum+=pow(dis,times)*info.towerInfo[j].resource;
		}	
		dangerline=sum/power;
		dangerline=(dangerline>0.15*info.towerInfo[i].maxResource)?dangerline:0.15*info.towerInfo[i].maxResource;
		if(dangerline>0.3*info.towerInfo[i].maxResource)
			dangerline=0.3*info.towerInfo[i].maxResource;
		dangerline=constrain(dangerline,15,50);
		if(info.towerInfo[i].strategy==Grow||info.towerInfo[i].strategy==Normal)
			dangerline+=10;
		else if(info.towerInfo[i].strategy==Defence)
			dangerline-=5;
		budaoline=dangerline+0.3*info.towerInfo[i].maxResource;
		int nn=0;
		for (int w = 0; w < 13; w++)
			if(info.towerInfo[w].owner==info.myID)
				nn++;
		if(nn>=11&&stage==houqi)
		{
			dangerline=0.15*info.towerInfo[i].maxResource;
			budaoline=0.2*info.towerInfo[i].maxResource;		
		}
		else if(nn>=9&&stage==houqi)
		{
			dangerline*=0.7;
			budaoline*=0.7;
		}
		else if(nn>=7&&stage==houqi)
		{
			dangerline*=0.85;
			budaoline*=0.80;		
		}
		_danger_line[i]=dangerline;
		_budao_line[i]=budaoline;
		dangerline=0;
		budaoline=0;
		/*ofstream log("linefortower.txt",ios::app);
		log<<info.round<<"*"<<i<<endl;
		log<<"budaoline"<<_budao_line[i]<<"dangerline"<<_danger_line[i]<<endl;
		log.close();*/

	}

}

//һ������attack ����ȫ���칥 ����ɶ���˺�
double bomb(Info& info,TTowerID a)
{
	double sum=0;
	for (int i = 0; i < 13; i++)
	{
		if(i==a||info.towerInfo[i].owner==-1)
			continue;
		if(info.lineInfo[a][i].exist==0&&info.lineInfo[i][a].exist==1&&(info.lineInfo[i][a].state==Arrived||coming_arrive_round(info,i,a)<2)&&info.towerInfo[a].owner!=info.myID&&info.towerInfo[i].owner==info.myID)
		{
			TPower supress=SupressPower[info.towerInfo[i].strategy][info.towerInfo[a].strategy];
			supress=(supress-1)/2.0+1;
			sum+=(info.lineInfo[i][a].resource*supress*attack_hurt_percentage(info,a));
		}			
	}
	return(sum);

}
//һ������attack ����ȫ���칥 ����ɶ���˺�  �������Ƕ��ҵ���������
double bomb1(Info& info,TTowerID a)
{
	double sum=0;
	if(info.towerInfo[a].owner!=info.myID)
	{
		fileout("aiddd                   serious!!!!","error.txt");
		return 0;
	}
	for (int i = 0; i < 13; i++)
	{
		if(i==a||info.towerInfo[i].owner==-1)
			continue;
		if(info.lineInfo[a][i].exist==0&&info.lineInfo[i][a].exist==1&&(info.lineInfo[i][a].state==Arrived||coming_arrive_round(info,i,a)<2)&&info.towerInfo[i].owner!=info.myID)
		{
			TPower supress=SupressPower[info.towerInfo[i].strategy][info.towerInfo[a].strategy];
			supress=(supress-1)/2.0+1;
			sum+=(info.lineInfo[i][a].resource*supress*attack_hurt_percentage(info,a));
		}			
	}
	return(sum);

}
//�Ѻõ�bomb  ����ҷ���ʹ��
double bomb2(Info& info,TTowerID a)
{
	double sum=0;
	if(info.towerInfo[a].owner!=info.myID)
	{
		fileout("aiddd   56                serious!!!!","error.txt");
		return 0;
	}
	for (int i = 0; i < 13; i++)
	{
		if(i==a||info.towerInfo[i].owner==-1)
			continue;
		if(info.lineInfo[a][i].exist==0&&info.lineInfo[i][a].exist==1&&(info.lineInfo[i][a].state==Arrived||coming_arrive_round(info,i,a)<2)&&info.towerInfo[i].owner==info.myID)
		{
			TPower supress=SupressPower[info.towerInfo[i].strategy][info.towerInfo[a].strategy];
			supress=(supress-1)/2.0+1;
			sum+=(info.lineInfo[i][a].resource*supress*attack_hurt_percentage(info,a));
		}			
	}
	return(sum);

}
//һ��Ҫ��֤line��source ���Լ�
double song_le(Info& info,LineInfo line)
{
	songle_cengci+=0.011;
	int towerid=line.sourceTower;
	if(line.exist==0||info.towerInfo[towerid].owner!=info.myID)
	{
		fileout("wrong use songle","error.txt");
		return 0;
	}
	if(line.targetTower==-1||line.targetTower==-1)
	{
		fileout("wrong ussfgsatwqt","error.txt");
		return 0;
	}
	double self_state_score=0;  //������״�����
	//�Ƿ��б���������  �������ж��ܸɵ������̳��ش��� ��30�ӳ�
	double bomb_left=info.towerInfo[towerid].resource-bomb1(info,towerid);
	double consume=each_round_consume(info,line.sourceTower);
	if(bomb_left<10)//�����Σ 300
	{
		fileout(info.round,"danger pull back!",towerid);
		return(200+songle_cengci);
	}
	if(consume>0&&info.towerInfo[line.sourceTower].resource<=10) //����ڼ�Ѫ����Ѫ��С��5�����100��
		return(100+songle_cengci);
	double left_round=info.towerInfo[line.sourceTower].resource/each_round_consume(info,line.sourceTower);
	if(left_round<0.001)
	{
	//	fileout("still strong");
		return(0+songle_cengci);
	}
	else if(left_round<2)
		self_state_score=100;
	else if(left_round<3)
		self_state_score=75;
	else if(left_round<4)
		self_state_score=50;
	else if(left_round<5)
		self_state_score=45.5;
	else if(left_round<7)
		self_state_score=35.5;
	else if(left_round<10)
		self_state_score=20;
	else if(left_round<15)
		self_state_score=10;
	else
		self_state_score=0.7;

	int attack_me_num=0;
	for(TTowerID tnum=0;tnum<13;tnum++)
	{
		if(info.towerInfo[tnum].owner==-1)
			continue;
		if(info.lineInfo[tnum][line.sourceTower].exist&&info.towerInfo[tnum].owner!=info.towerInfo[line.sourceTower].owner)
			attack_me_num++;
	}
	if(attack_me_num==0)
		self_state_score*=0.1;
	else if(attack_me_num!=1)
		self_state_score*=(1+0.1*(attack_me_num-1));

	if(info.towerInfo[line.targetTower].owner!=info.myID&&info.lineInfo[line.targetTower][line.sourceTower].exist==1)
		self_state_score-=20;
//	char output2[200];
//	sprintf_s(output2,"self_state_score:%.2lf  ",self_state_score);
//	fileout("tower",towerid,"cut evluate blabla");
//	fileout(output2);
	return(self_state_score+songle_cengci);
}

//���Ѵ��ڵ��ҷ����ߣ�Ԯ��/�ù����£��Ƿ��жϵ�����
double helporattack_line_cut(Info& info,LineInfo line)
{
	if(info.towerInfo[line.sourceTower].owner!=info.myID||!line.exist)
		return 0;

	//*************Ԯ����������********����˫��Ѫ����eachroundconsume,�͵з���������ı��ߣ��������ѵ���ı��ߣ���Ϊ������eachroundconsume�Ŀ����У�
	if(info.towerInfo[line.targetTower].owner==info.myID)
	{
		double target_resource=info.towerInfo[line.targetTower].resource;
		double my_resource=info.towerInfo[line.sourceTower].resource;

		double target_consume=each_round_consume(info,line.targetTower);
		double my_consume=each_round_consume(info,line.sourceTower);

		int target_extending_line=0;
		//������������û�е���sourceTower��line
		for(TTowerID tnum=0;tnum<info.towerNum;tnum++)
		{

			if(info.lineInfo[tnum][line.targetTower].exist&&info.lineInfo[tnum][line.targetTower].state==Extending&&info.towerInfo[tnum].owner!=info.myID)
			{
				target_extending_line++;
			}
		}

		int my_extending_line=0;
		//������������û�е���sourceTower��line
		for(TTowerID tnum=0;tnum<info.towerNum;tnum++)
		{

			if(info.lineInfo[tnum][line.sourceTower].exist&&info.lineInfo[tnum][line.sourceTower].state==Extending&&info.towerInfo[tnum].owner!=info.myID)
			{
				my_extending_line++;
			}
		}

		double resource_score=(target_resource-my_resource)*100/25;  //Ѫ�����50��resource_score�����֣���ͬ
		double K_resource=0.5;
		double consume_score=(my_consume-target_consume)*100/3;
		double K_consume=0.33;
		double line_score=(target_extending_line-my_extending_line)*100/2;
		double K_line=0.5;
		double score=resource_score*K_resource+consume_score*K_consume+line_score*K_line;
		//double score=resource_score*K_resource+line_score*K_line;
		//char output1[100];
	//	sprintf_s(output1,"helporattack_line_cut:tower %d to %d:",line.sourceTower,line.targetTower);


		if(my_resource<target_resource&&my_consume>0&&target_consume<=0) //�����������ǿ�������ڵ�Ѫ������û����������
		{
		//	char output2[30]="definately full score!";
	//		fileout(strcat(output1,output2));
			return 100;
		}

		else if(score>=0&&score<=100)
		{	
		//	char output2[100];
	//		sprintf(output2,"score=resource(%.2lf)+line_score(%.2lf)",resource_score*K_resource,line_score*K_line);	
			//fileout(output1);
			//fileout(output2);
			return score;
		}
		else if(score<0)
		{
			//char output2[20]="0 score!";
		//	fileout(strcat(output1,output2));
			//char output3[100];
		//	sprintf(output3,"score=resource(%.2lf)+line_score(%.2lf)",resource_score*K_resource,line_score*K_line);	
			//fileout(output3);
			return score;
		}
		else 
		{
			//char output2[20]="full score!";
			//fileout(strcat(output1,output2));
			//char output3[100];
			//sprintf(output3,"score=resource(%.2lf)+line_score(%.2lf)",resource_score*K_resource,line_score*K_line);	
			//fileout(output3);
			return 100;
		}
	}

	else
	{
		TTowerID target=line.targetTower;
		TTowerID source=line.sourceTower;
		if(info.round-_added_lines_round[source][target][0]>30&&(_added_lines_round[source][target][1]-info.towerInfo[target].resource)<10&&line.state==Arrived)
		{
			//char output[40];
			//sprintf(output,"tower %d cannot defeat tower %d",source,target);
			//fileout(output);
			return 100;
		}
		else
		{
			return 0;
		}
	}
}

// �ж�һ���з����ܲ��ܱ���ը��  ����0��Ϊ��ʱû�п���  ���򷵻�1
//�������Ҫ�����˶෽��   �෽�����Ҳ�Ҫ
int can_it_be_bombed(Info& info,TTowerID x)
{
	double mine=0;
	int couw=0;
	int others_attack_flag=0;
	if(info.towerInfo[x].owner==info.myID||info.towerInfo[x].owner==-1)
		return 0;

	double bb=bomb(info,x);
			for (int j = 0; j < 13; j++)
			{
				if(j!=x&&info.towerInfo[j].owner!=-1&&info.towerInfo[j].owner!=info.myID&&info.lineInfo[j][x].exist==1&&info.lineInfo[j][x].state!=AfterCut)
					couw++;
			}
	int a=10;
	if(couw==0)
		a=15;
	else
		a=27;
	if((bb>info.towerInfo[x].resource+10&&info.towerInfo[x].currLineNum>0)||(bb>info.towerInfo[x].resource+a))
	{

		return 1;
	}
	else
		return 0;
		
}
double kuai_gong(Info& info,TTowerID from,TTowerID to)
{
	if(info.towerInfo[from].owner!=info.myID||info.towerInfo[to].owner==info.myID)
	{
		fileout("error use use kuaigong","error.txt");
		return 0;
	}

	int attacker[4]={0,0,0,0};
	if(info.towerInfo[to].owner!=info.myID&&info.towerInfo[to].owner!=-1)
	{
		for (int j = 0; j < 13; j++)
		{
			if(j!=to&&info.towerInfo[j].owner!=-1&&info.lineInfo[j][to].exist==1&&info.lineInfo[j][to].state!=AfterCut&&info.lineInfo[j][to].resource*10>=info.lineInfo[j][to].maxlength/2.0+10)
				attacker[info.towerInfo[j].owner]+=1;
		}
	}
	int count=0;
	int nitan=0;
	for (int k = 0; k < 4; k++)
	{
		if(attacker[k]>0&&k!=info.myID)
			count++;
		if(attacker[k]>=3&&k!=info.myID&&k!=info.towerInfo[to].owner)
			nitan=1;
	}
	if(count>=2)
		return 0;
	if(nitan==1)
		return 0;

	double score=_kuaigong_recommend[from][to];
	if(score>fence)
	{
	//	fileout(from, "  to" ,to);
	//	fileout("kuaigong score",score);
	}
	if(score<fence)
		score=0.2333;
	return(score);
}
double money(Info& info,TTowerID x)
{
	double money=0;
	for(int i=0;i<13;i++)
	{
		if(i==x)
			continue;
		if(info.lineInfo[x][i].exist==1&&info.lineInfo[x][i].state!=AfterCut)
			money+=info.lineInfo[x][i].resource;
	}
	return money;
}
void kuai_gong(Info& info,TTowerID hisT)
{
	kuaigong_cengci+=0.02;
	//һЩ�뷨  �ڵ�ǰ���߿���ֱ�Ӹɵ�����ʱ�칥
	// �ܲ��ܿ칥 ��ʱһ���칥 �������أ���̬���ƿ칥��ɺ�����ܷ��£�
	//�칥����  �ȱ�֤�칥���з��б��߱�ɱ���ٶ�10��  ��+����Դ�������� level�ڵ�+��
	//�Ϸ��Լ��  ���Ƕ���Э��
	if(info.towerInfo[hisT].owner==info.myID)
		return;
	else if(can_it_be_bombed(info,hisT)==0)
	{
		//fileout("hold!!!!!!");
		return;
	}
	//ִ��
	if(info.towerInfo[hisT].strategy==Defence||money(info,hisT)>0.5*info.towerInfo[hisT].resource||info.towerInfo[hisT].resource<80)
	{
		for (int i = 0; i < 13; i++)
		{
			if(info.towerInfo[i].owner!=info.myID)
				continue;
			if(info.lineInfo[i][hisT].exist==0||info.lineInfo[i][hisT].state!=Arrived)
				continue;
			_kuaigong_recommend[i][hisT]=100+kuaigong_cengci;
		}
	}
	return;

}

//strategyΪ�����������Ĳ������ࣻ
double strategychange(Info& info,TTowerID id,int afterstrategy)
{

	//ȷ�����²���
	int nowstrategy=info.towerInfo[id].strategy ;
	//fileout("technology",info.playerInfo[info.towerInfo[id].owner].technologyPoint);
	double score=0;
	double rate=1.2;
	int mytowernumber=0;
	int i;
	for(i=0;i<13;i++)
		if(info.towerInfo[i].owner==info.myID)
			mytowernumber++;
	//ά��strategy
	if(info.round==0)
	{
		if(info.towerInfo[id].owner==info.myID)
		{
			stragtegy[id][0]=info.towerInfo[id].strategy;
			stragtegy[id][1]=-1;stragtegy[id][2]=-1;stragtegy[id][3]=-1;
		}
		else
		{
			stragtegy[id][0]=-1;
			stragtegy[id][1]=-1;stragtegy[id][2]=-1;stragtegy[id][3]=-1;
		}
	}
	else 
	{
		if(info.towerInfo[id].owner==info.myID)
		{
			stragtegy[id][3]=stragtegy[id][2];
			stragtegy[id][2]=stragtegy[id][1];
			stragtegy[id][1]=stragtegy[id][0];
			stragtegy[id][0]=info.towerInfo[id].strategy;
		}
	}
	//
	if(nowstrategy==afterstrategy)
		return 0;
	if(info.round!=0)
		if(stragtegy[id][0]!=stragtegy[id][1]&&stragtegy[id][0]==stragtegy[id][2])
			if(stragtegy[id][1]==afterstrategy&&info.playerInfo[info.myID].technologyPoint<25)
				return 0;
	switch(afterstrategy)
	{	
	case 0:
		score+=strategychange0(info,id,nowstrategy);
		break;
	case 1:
		{
			score+=strategychange1(info,id,nowstrategy);
			if(mytowernumber>6)
				score*=1.2;
			break;
		}
	case 2:
		score+=strategychange2(info,id,nowstrategy);
		break;
	case 3:
		{
			score+=strategychange3(info,id,nowstrategy);
			if(info.round<20)
				score*=1.2;
			break;
		}
	}
	if(score>350)
		score=350;
	return score;
}
double strategychange0(Info& info,TTowerID id,int nowstrategy)
{
	int me=info.towerInfo[id].owner;
	int i,j;
	int d=0,d1=0,d2=0,d3=0;//�����ҵ����ĸ�����Ŀͳ��
	double score=0;
	int who_is_attacking_me[13][2]={0};
	//�����Լ�飬�Ƿ�����㹻�Ƽ�������
	if(info.towerInfo[id].owner!=info.myID||info.playerInfo[me].technologyPoint<StrategyChangeCost[nowstrategy][0])
	{
		return 0;
	}
	//�Դ��Һͱ��Ҵ�������ʼ��
	for(i=0;i<13;i++)
	{
		who_is_attacking_me[i][1]=-1;
	}
	//�Դ��Һͱ��Ҵ�����鸳ֵ
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacking_me[j][0]=i;
		who_is_attacking_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	//�Թ����ҵ�������ϸ��
	for(i=0;who_is_attacking_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[who_is_attacking_me[i][0]][id].state==Arrived||info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation||coming_arrive_round(info,who_is_attacking_me[i][0],id)<2||(info.lineInfo[who_is_attacking_me[i][0]][id].exist&&info.lineInfo[id][who_is_attacking_me[i][0]].exist))
		{
			d++;
			if(who_is_attacking_me[i][1]==1)
				d1++;
			else if(who_is_attacking_me[i][1]==2&&info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation)
				d2++;
			else
				d3++;
		}
	}
	if(nowstrategy==Grow)
	{
		if(d1>0&&info.playerInfo[me].technologyPoint<5)
			score+=80;
	}
	if(nowstrategy==Defence)
	{
		if(d==0&&info.playerInfo[me].technologyPoint<5)
			score+=80;
	}
	return score;
}
//�ı䱾���Ĳ���ֵ
double strategychange1(Info& info,TTowerID id,int nowstrategy)
{
	int me=info.towerInfo[id].owner;
	int i,j;
	int d=0,d1=0,d2=0,d3=0;//�����ҵ����ĸ�����Ŀͳ��
	int c=0,c1=0,c2=0,c3=0;//���ҹ������ĸ�����Ŀͳ��
	double score=0;
	int who_is_attacking_me[13][2]={0};
	int who_is_attacked_by_me[13][2]={0};
	//�����Լ�飬�Ƿ�����㹻�Ƽ�������
	if(info.towerInfo[id].owner!=info.myID||info.playerInfo[me].technologyPoint<StrategyChangeCost[nowstrategy][1])
	{
		return 0;
	}
	int mytowernumber=0;             
	for(i=0;i<13;i++)
		if(info.towerInfo[i].owner==info.myID)
			mytowernumber++;
	//�Դ��Һͱ��Ҵ�������ʼ��
	for(i=0;i<13;i++)
	{
		who_is_attacking_me[i][1]=-1;
		who_is_attacked_by_me[i][1]=-1;
	}
	//�Դ��Һͱ��Ҵ�����鸳ֵ
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacking_me[j][0]=i;
		who_is_attacking_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacked_by_me[j][0]=i;
		who_is_attacked_by_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	//�������
	for(i=0;who_is_attacking_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[who_is_attacking_me[i][0]][id].state==Arrived||info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation||coming_arrive_round(info,who_is_attacking_me[i][0],id)<2||(info.lineInfo[who_is_attacking_me[i][0]][id].exist&&info.lineInfo[id][who_is_attacking_me[i][0]].exist))
		{
			d++;
			if(who_is_attacking_me[i][1]==1)
				d1++;
			else if(who_is_attacking_me[i][1]==2&&info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation)
				d2++;
			else
				d3++;
		}
	}
	for(i=0;who_is_attacked_by_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[id][who_is_attacked_by_me[i][0]].state==Arrived||info.lineInfo[id][who_is_attacked_by_me[i][0]].state==Confrontation)
		{
			c++;
			if(who_is_attacked_by_me[i][1]==1)
				c1++;
			else if(who_is_attacked_by_me[i][1]==2&&info.lineInfo[id][who_is_attacked_by_me[i][0]].state==Confrontation)
				c2++;
			else if(who_is_attacked_by_me[i][1]==3||who_is_attacked_by_me[i][1]==0)
				c3++;
		}
	}
	//ǰ��ս��
	if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
	{
		if(nowstrategy==Grow||nowstrategy==Normal)
		{
			if(d>0&&d1<2)
				score+=150;
			if(d1>2)
				score-=80;
			if(id%3!=0)
			{
				if(info.towerInfo[id].resource>130)
					score+=50;
				else if(info.towerInfo[id].resource>100)
					score+=30;
			}
			if(info.towerInfo[id].resource>80&&c3>0)
				score+=100*c3;
			if(c2>0)
				score-=200*c2;
			if(info.towerInfo[id].resource>80&&c1>0)
				score+=30*c1;
			if(id==12&&d==0&&info.towerInfo[id].resource>45)
				score+=80*c;
		}
		else
		{
			if(d>0&&d1<2)
				score+=100;
			if(d1>1||d2>0)
				score-=50*(d1+d2);
			else if(d3>0)
				score+=30*d3;
			if(id%3!=0)
			{
				if(info.towerInfo[id].resource>100)
					score+=100;
			}
			if(info.towerInfo[id].resource>80&&c3>0)
				score+=100*c3;
			if(c2>0)
				score-=200*c2;
			if(id==12&&d==0&&info.towerInfo[id].resource>40)
				score+=80+40*c;
		}
	}
	//����ս��
	else
	{ 
		score-=100*(d2+c2);
		score+=100*c3;
		score+=20*c;
		if(d>0&&d1<2)
			score+=100;
		if(d1>2)
			score-=80;
		if(id%3!=0)
		{
			if(info.towerInfo[id].resource>120)
				score+=100;
			else if(info.towerInfo[id].resource>100)
				score+=80;
			else if(info.towerInfo[id].resource>80)
				score+=30;
			else if(info.towerInfo[id].resource<40)
				score-=80;
		}
		if(id==12&&d==0)
			score+=80+40*c;
	}
	return score;
}
double strategychange2(Info& info,TTowerID id,int nowstrategy)
{
	int me=info.towerInfo[id].owner;
	int i,j;
	int d=0,d1=0,d2=0,d3=0;//�����ҵ����ĸ�����Ŀͳ��
	double score=0;
	int who_is_attacking_me[13][2]={0};
	int who_is_attacked_by_me[13][2]={0};
	//�����Լ�飬�Ƿ�����㹻�Ƽ�������
	if(info.towerInfo[id].owner!=info.myID||info.playerInfo[me].technologyPoint<StrategyChangeCost[nowstrategy][2])
	{
		return 0;
	}
	//�Դ��Һͱ��Ҵ�������ʼ��
	for(i=0;i<13;i++)
	{
		who_is_attacking_me[i][1]=-1;
		who_is_attacked_by_me[i][1]=-1;
	}
	//�Դ��Һͱ��Ҵ�����鸳ֵ
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacking_me[j][0]=i;
		who_is_attacking_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacked_by_me[j][0]=i;
		who_is_attacked_by_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	//�Թ����ҵ�������ϸ��
	for(i=0;who_is_attacking_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[who_is_attacking_me[i][0]][id].state==Arrived||info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation||coming_arrive_round(info,who_is_attacking_me[i][0],id)<2||(info.lineInfo[who_is_attacking_me[i][0]][id].exist&&info.lineInfo[id][who_is_attacking_me[i][0]].exist))
		{
			d++;
			if(who_is_attacking_me[i][1]==1)
			{
				d1++;
				if(info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation)
					d2++;
			}
			else
				d3++;
		}
	}
	if(nowstrategy==Grow||nowstrategy==Normal)
	{
		if(info.playerInfo[me].technologyPoint>25)
		{
			if(d1==1&&d2==1)
				score+=150;
		}
		if(d1>1)
			score+=250*d1;
		else if(d<3&&id!=12)
			score-=d3*50;
	}
	else
	{
		if(info.playerInfo[me].technologyPoint>25)
		{
			if(d1==1&&d2==1)
				score+=150;
		}
		if(d1>1)
			score+=250*d1;
		else if(d<3&&id!=12)
			score-=d3*100;
	}
	return score;
}
double strategychange3(Info& info,TTowerID id,int nowstrategy)
{
	int me=info.towerInfo[id].owner;
	int i,j;
	int d=0,d1=0,d2=0,d3=0;//�����ҵ����ĸ�����Ŀͳ��
	int c=0,c1=0,c2=0,c3=0;//���ҹ������ĸ�����Ŀͳ��
	double score=0;
	int who_is_attacking_me[13][2]={0};
	int who_is_attacked_by_me[13][2]={0};
	//�����Լ�飬�Ƿ�����㹻�Ƽ�������
	if(info.towerInfo[id].owner!=info.myID||info.playerInfo[me].technologyPoint<StrategyChangeCost[nowstrategy][3])
	{
		return 0;
	}
	int mytowernumber=0;             
	for(i=0;i<13;i++)
		if(info.towerInfo[i].owner==info.myID)
			mytowernumber++;
	//�Դ��Һͱ��Ҵ�������ʼ��
	for(i=0;i<13;i++)
	{
		who_is_attacking_me[i][1]=-1;
		who_is_attacked_by_me[i][1]=-1;
	}
	//�Դ��Һͱ��Ҵ�����鸳ֵ
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacking_me[j][0]=i;
		who_is_attacking_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	for(i=0,j=0;i<13;i++)
	{
		if(info.towerInfo[i].owner==info.myID||info.lineInfo[i][id].exist==0||info.lineInfo[i][id].state==AfterCut)
			continue;
		who_is_attacked_by_me[j][0]=i;
		who_is_attacked_by_me[j][1]=info.towerInfo[i].strategy;
		j++;
	}
	//�������
	for(i=0;who_is_attacking_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[who_is_attacking_me[i][0]][id].state==Arrived||info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation||coming_arrive_round(info,who_is_attacking_me[i][0],id)<2||(info.lineInfo[who_is_attacking_me[i][0]][id].exist&&info.lineInfo[id][who_is_attacking_me[i][0]].exist))
		{
			d++;
			if(who_is_attacking_me[i][1]==1)
				d1++;
			else if(who_is_attacking_me[i][1]==2&&info.lineInfo[who_is_attacking_me[i][0]][id].state==Confrontation)
				d2++;
			else
				d3++;
		}
	}
	for(i=0;who_is_attacked_by_me[i][1]!=-1;i++)
	{
		if(info.lineInfo[id][who_is_attacked_by_me[i][0]].state==Arrived||info.lineInfo[id][who_is_attacked_by_me[i][0]].state==Confrontation)
		{
			c++;
			if(who_is_attacked_by_me[i][1]==1)
				c1++;
			else if(who_is_attacked_by_me[i][1]==2)
				c2++;
			else if(who_is_attacked_by_me[i][1]==3||who_is_attacked_by_me[i][1]==0)
				c3++;
		}
	}
	if(id==12)
		return 0;
	//ǰ��ս��
	if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
	{
		if(info.round<10&&id%3==2)
			return 200;
		if(d==0)
		{
			if(id%3==0)
			{
				score+=60;
				score+=80*c2;
				if(info.towerInfo[id].resource<50)
					score+=100;
				else if(info.towerInfo[id].resource<100)
					score+=80;
				else if(info.towerInfo[id].resource<150)
					score+=70;
				else if(info.towerInfo[id].resource<180)
					score+=50;
			}
			else
			{
				if(info.towerInfo[id].resource<50)
					score+=100;
				else if(info.towerInfo[id].resource<100)
					score+=60;
			}
			if(nowstrategy==0)
				score*=1.2;
			else if(nowstrategy==2)
				score*=1.5;
		}
		else if(d1>0)
			score-=200*d1;
		else if(d2>0)
			score+=80*d2;
	}
	else
	{
		if(d==0)
		{
			if(id%3==0)
			{
				score+=60;
				score+=80*c2;
				if(info.towerInfo[id].resource<180)
					score+=100;
			}
			else
			{
				if(info.towerInfo[id].resource<80)
					score+=100;
			}
			if(nowstrategy==0)
				score*=1.2;
			else if(nowstrategy==2)
				score*=1.5;
		}
		else if(d1>0)
		{
			score-=200*d1;
		}
		else if(d2>0)
			score+=80*d2;
	}
	if(nowstrategy==1)
		score*=0.9;
	return score;
}

double propertychange(Info& info,int upgradetype)
{
	int me=info.myID;
	int i,mytowernumber=0;
	double score=0;
	int level=0;
	for(i=0;i<13;i++)
		if(info.towerInfo[i].owner==info.myID)
			mytowernumber++;
	switch(upgradetype)
	{
	case 0:
		level=info.playerInfo[me].RegenerationSpeedLevel;
		if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
			if(info.playerInfo[me].technologyPoint<RegenerationSpeedUpdateCost[level]+3)
				return 0;
		if(level!=5)	
			score=80+(5-level)*3;
		else
			score=0;
		break;
	case 1:
		level=info.playerInfo[me].ExtendingSpeedLevel;
		if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
			if(info.playerInfo[me].technologyPoint<ExtendingSpeedUpdateCost[level]+3)
				return 0;
//                                           This is the final release of the zuc5.5 version 9
		if(level!=5)
		{
			if(info.playerInfo[me].ExtraControlLevel<3)
				score=0;
			else 
				score=score=75+(5-level)*3;
		}
		else
			score=0;
		break;
	case 2:
		level=info.playerInfo[me].ExtraControlLevel;
		if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
			if(info.playerInfo[me].technologyPoint< ExtraControlStageUpdateCost[level]+2)
				return 0;
		if(level!=3)
		{
			if(info.playerInfo[me].DefenceLevel<2)
				score=0;
			else 
				score=73+(3-level)*7;
			if(level==2&&info.playerInfo[me].RegenerationSpeedLevel!=5)
				score=0;
		}
		else
			score=0;
		break;
	case 3:
		level=info.playerInfo[me].DefenceLevel;
		if(mytowernumber<6||info.playerInfo[me].technologyPoint<10)
			if(info.playerInfo[me].technologyPoint< DefenceStageUpdateCost[level]+2)
				return 0;
		if(level!=3)
		{
			if(info.playerInfo[me].RegenerationSpeedLevel<4)
				score=0;
			else 
				score=74+(3-level)*7;
			if(level==2&&info.playerInfo[me].RegenerationSpeedLevel!=5)
				score=0;
		}
		else
			score=0;
		break;
	}
	return score;
}


	//�ж���tnum�Ƿ��Ƿ��ҷ��������ڹ�����ѹ��/���ţ���T,���ǹ��� ����1�����Ƕ��ţ�����2�����򷵻�0
int others_attacking_judge(Info& info,TTowerID T,TTowerID tnum)
{
	//fileout("others attacking judge start");
	int judge1=info.lineInfo[tnum][T].exist;

	int judge2=(info.lineInfo[tnum][T].state==Arrived);
	int judge3_1=(info.lineInfo[tnum][T].state==Attacking);
	int judge3_2=(info.lineInfo[tnum][T].state==Backing);
	int judge3_3=(info.lineInfo[tnum][T].state==Confrontation);

	int judge4=(info.towerInfo[tnum].owner!=info.towerInfo[T].owner);
	int judge5=(info.towerInfo[tnum].owner!=info.myID);

	if(judge1&&judge2&&judge4&&judge5)
	{
		//fileout("others attacking judge end");
		return 1;
	}
	else if(judge1&&(judge3_1||judge3_2||judge3_3)&&judge4&&judge5)
	{
		//fileout("others attacking judge end");
		return 2;
	}
	else 
	{
		//fileout("others attacking judge end");
		return 0;
	}
}

	//�������ڹ�����ѹ��/���ţ���T�ķ��ҷ�������
int others_attacking(Info& info,TTowerID T)
{
	//fileout("others attacking start");
	int result=0;

	for(TTowerID tnum=0;tnum<info.towerNum;tnum++)
	{
		if(others_attacking_judge(info,T,tnum))
		{
			result++;
		}
	}
	//fileout("others attacking end");
	return result;
}

//����:T1�Ƿ��ж�Ԯ���߰���T2
double help_bomb_evaluate(Info& info,TTowerID T1,TTowerID T2)
{
	if(info.towerInfo[T1].owner==-1||info.towerInfo[T2].owner==-1)
	{
		fileout("ddsd","error.txt");
		return 0;
	}
	if(info.towerInfo[T1].owner!=info.myID||info.towerInfo[T2].owner!=info.myID)
	{
		fileout("ddssagd","error.txt");
		return 0;
	}
	if(info.lineInfo[T1][T2].exist==0||info.lineInfo[T1][T2].state!=Arrived)
	{
		return 0;
	}
	
	if((info.towerInfo[T2].resource+info.lineInfo[T1][T2].resource)>info.towerInfo[T2].maxResource)
	{
		return 0;
	}
	double sum=bomb2(info,T2);	
	if((sum+info.towerInfo[T2].resource)<_budao_line[T2]+10)
		return 0.65;
	if(info.towerInfo[T2].resource>info.towerInfo[T1].resource)
		return 0.33;
	return(80);

}

//�ҵ����й������ô�����
void jizhonggongji_members_find(Info& info)
{
	int daifenpei_count=0;
	int flag=0;
	for(TTowerID tnum=0;tnum<info.towerNum;tnum++)
	{
		if(info.towerInfo[tnum].owner!=info.myID)
			continue;
		if(_tower_way_index[tnum]==0||_tower_way_index[tnum]==1)
		{
			double resource_propertion=info.towerInfo[tnum].resource/info.towerInfo[tnum].maxResource;
			double consume=each_round_consume(info,tnum);
			flag=0;
			for (int k = 0; k < 13; k++)
			{
				if(info.towerInfo[k].owner!=info.myID&&info.lineInfo[k][tnum].exist==1&&info.lineInfo[k][tnum].state!=AfterCut)
					flag++;
			}
			if(resource_propertion>0.8&&info.towerInfo[tnum].resource>125&&info.lineInfo[tnum][_my_now_budao_target].exist==1&&((flag==0&&info.towerInfo[tnum].currLineNum<info.towerInfo[tnum].maxLineNum)||(flag==1&&info.towerInfo[tnum].currLineNum<info.towerInfo[tnum].maxLineNum-1)))
			{
				jizhonggongji_daifenpei[daifenpei_count]=tnum;
				daifenpei_count++;
			}
		}
	}
	jizhonggongji_daifenpei[daifenpei_count]=-1;
}

void commandcheck(Info &info)
{
int i,j;
for(i=0;i<13;i++)
for(j=0;j<13;j++)
{
//��ӱ�����
//�ӷ���������ӱ���
if(info.towerInfo[i].owner!=info.myID&&_evaluate[addLine][i][j]>fence)
_evaluate[addLine][i][j]=0;
//	fileout("error!!!adding the line that is not from my tower!!","error.txt");
//����������ӱ���
if(i==j&&_evaluate[addLine][i][j]>fence)
_evaluate[addLine][i][j]=0;
//	fileout("error!!!addline to myself!!","error.txt");
//�����ڵı�����ӱ���
if(info.lineInfo[i][j].exist&&_evaluate[addLine][i][j]>fence)
_evaluate[addLine][i][j]=0;
//	fileout("error!!!addline to existing line!!!","error.txt");

//�жϱ�����
//�жϷ�����ı���
if(info.towerInfo[i].owner!=info.myID&&_evaluate[cutLine][i][j]>fence)
_evaluate[cutLine][i][j]=0,
fileout("error!!!cutting the line that is not from my tower!!","error.txt");
//�ж����������ı���
if(info.lineInfo[i][j].exist&&info.lineInfo[i][j].state==AfterCut&&_evaluate[cutLine][i][j]>fence)
_evaluate[cutLine][i][j]=0,
fileout("error!!!cutting the line that is AfterCut!!","error.txt");
//�жϲ����ڵı���
if(info.lineInfo[i][j].exist==0&&_evaluate[cutLine][i][j]>fence)
_evaluate[cutLine][i][j]=0,
fileout("error!!!cutline that is not existed!!","error.txt");

//�ı������
//�����ڸò���
if(j>3&&_evaluate[changeStrategy][i][j]>fence)
_evaluate[changeStrategy][i][j]=0,
fileout("error!!!stragety that is not existed!!","error.txt");
//�ı���Լ����Ĳ���
if(info.towerInfo[i].owner!=info.myID&&_evaluate[changeStrategy][i][j]>fence)
_evaluate[changeStrategy][i][j]=0,
fileout("error!!!changestragtegy that is not mine!!","error.txt");

//����״̬��
//����������״̬
if(i>3&&_evaluate[upgrade][i][0]>fence)
_evaluate[upgrade][i][0]=0,
fileout("error!!!that property is not existed!!!","error.txt");
}

//����������״̬
if(info.playerInfo[info.myID].RegenerationSpeedLevel==5&&_evaluate[upgrade][0][0]>fence)
_evaluate[upgrade][0][0]=0,
fileout("error!!!regenerationspeedlevel is full!!!","error.txt");
if(info.playerInfo[info.myID].ExtendingSpeedLevel==5&&_evaluate[upgrade][1][0]>fence)
_evaluate[upgrade][1][0]=0,
fileout("error!!!extendingspeedlevel is full!!!","error.txt");
if(info.playerInfo[info.myID].ExtraControlLevel==3&&_evaluate[upgrade][2][0]>fence)
_evaluate[upgrade][2][0]=0,
fileout("error!!!extracontrollevel is full!!!","error.txt");
if(info.playerInfo[info.myID].DefenceLevel==3&&_evaluate[upgrade][3][0]>fence)
_evaluate[upgrade][3][0]=0,
fileout("error!!!defencelevel is full!!!","error.txt");
}

//����cutline����,ͬʱά��lines_index���fightback
double fightback_lines_control(Info& info,TTowerID t,TTowerID target)
{
	if(info.towerInfo[t].owner!=info.myID||info.towerInfo[target].owner==info.myID||info.towerInfo[target].owner==-1)
	{
		fileout("bugbug","error.txt");
		return 0;
	}
	if(info.lineInfo[t][target].exist==0)
		return 0;
	if(info.lineInfo[t][target].state==AfterCut)
		return 0;
	if(_lines_index[t][target]!=fightback_score)
	{
		return 0;
	}

	int tar_to_me=info.lineInfo[target][t].exist;
	int me_to_tar=info.lineInfo[t][target].exist;
	int he_cut=(info.lineInfo[target][t].state==AfterCut);
	int confronting=(info.lineInfo[t][target].state==Confrontation);

	if(((!tar_to_me)&&me_to_tar)||(he_cut&&me_to_tar))
	{
		//fileout("fightback cut ",info.round);
		//fileout(t);
		//fileout(target);
		return 100;
	}
	else if(confronting)
	{
		fileout("fightback cut ",info.round);
		fileout("shen suo",info.round);
		fileout(t);
		fileout(target);
		return 100;
	}
	else if(info.lineInfo[t][target].exist&&info.lineInfo[t][target].resource>info.lineInfo[t][target].maxlength/20-1.5)
	{
		return 100;
	}
	else
	{
		return 0;
	}
}



double tiaodou_addline(Info& info,TTowerID t,TTowerID target)
{
	if(info.towerInfo[t].owner!=info.myID||info.towerInfo[target].owner==info.myID||info.towerInfo[target].owner==-1)
		return 0.7;
	if(target==12)
		return 0.69;
	if(info.lineInfo[target][t].exist==1&&info.lineInfo[target][t].state!=AfterCut)
		return 1.06;
	//����1 �������
	if(info.towerInfo[t].currLineNum>=info.towerInfo[t].maxLineNum||addline_ok(info,t,target)!=0)
		return 0.9;

	//����2 ��Դ��                                                            ����
	if((t!=12&&info.towerInfo[t].resource<info.towerInfo[t].maxResource*0.8)||(t==12&&info.towerInfo[t].resource<32))
		return 0.78;
	if(each_round_consume(info,t)>4)
		return 0.11;
	if(info.towerInfo[target].resource>info.towerInfo[t].resource+35)
		return 0.33;
	//����2 attack��grow
	if(info.towerInfo[t].strategy!=Attack||info.towerInfo[target].strategy!=Grow)
		return 0.34;

	//����3 ûtiaodou����
	int flag=0;
	for(int i=0;i<13;i++)
	{
		if(i==t)
			continue;
		if(_lines_index[t][i]==tiaodou)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		return 0.96;

	//����4 û�˴�
	int flag2=0;
	for(int i=0;i<13;i++)
	{
		if(i==t||info.towerInfo[i].owner==info.myID||info.towerInfo[i].owner==-1)
			continue;
		if(info.lineInfo[i][t].exist==1&&info.lineInfo[i][t].state!=AfterCut)
		{
			flag2=1;
			break;
		}
	}
	if(flag2==1)
		return 0.42;

	//����5 rank��һ��rank2��Ŀ����rank1��
	int pan1=(info.playerInfo[info.towerInfo[t].owner].rank==1);
	int pan2=(info.playerInfo[info.towerInfo[target].owner].rank==1);
	int pan3=(info.playerInfo[info.towerInfo[t].owner].rank==2);
	if(pan1||(pan2&&pan3))
	{}
	else
		return 0.77;

	//����6 info.round>100   
	if(info.round<=90)
		return 0.55;

	//����7 distance<420
	if(getDistance(info.towerInfo[t].position,info.towerInfo[target].position)>420)
		return 0.44;
	//����9û��attack�ڴ������ҷ�������
	double em=0;
	for (int i = 0; i < 13; i++)
	{
		if(i!=t&&i!=target&&info.towerInfo[i].strategy==Attack&&info.towerInfo[i].owner!=info.towerInfo[target].owner&&info.lineInfo[i][target].exist==1&&info.lineInfo[i][target].state!=AfterCut)
		{
			if(info.towerInfo[i].owner==info.myID)
				em+=0.7;
			else
				em+=1.1;
		}
	}
	if(em>=1)
		return 1.11;
	//***********************************************************

	double dis=getDistance(info.towerInfo[t].position,info.towerInfo[target].position);
	double tar_resource=info.towerInfo[target].resource;
	double tar_rank=info.playerInfo[info.towerInfo[target].owner].rank;

	double score=(900-dis)*0.1+(info.towerInfo[target].maxResource-tar_resource)*0.4+(4-tar_rank)*10+fence;

	/*ofstream log("tiaodou.txt",ios::app);
	log<<"round"<<info.round<<endl;
	log<<t<<target<<endl;
	log.close();*/

	return score;
}
double tiaodou_cut(Info& info,TTowerID t,TTowerID target)
{
	if(info.lineInfo[t][target].exist==0||(info.lineInfo[t][target].exist==1&&info.lineInfo[t][target].state==AfterCut))
	{
		_lines_index[t][target]=noline;
		return 0;
	}

	if(_lines_index[t][target]!=tiaodou)
		return 0.1;

	if(info.towerInfo[t].owner!=info.myID)
		return 0;

	if(info.towerInfo[target].owner==info.myID)
		return fence+55+(rand()%100)/100.0;
	if(!(t==12&&info.round<50))
	{
		if(info.towerInfo[t].resource<_danger_line[t]+20||(t==12&&info.towerInfo[t].resource<10))
			return fence+100+(rand()%100)/100.0;
	}
	if(info.towerInfo[target].strategy!=Grow||info.towerInfo[t].strategy!=Attack)
		return fence+15+(rand()%100)/100.0+20;
	if((info.playerInfo[info.myID].rank>=3)&&(!(info.round<50&&t==12)))
		return fence+95+(rand()%100)/100.0;
	//������  ������ֹ����� �򽩳־��� ��̽������ 
	//ǰ��ͳ��fightback����   ��������
	return 0;
}

//����_evaluate_detail�ж� t �� target��line��ʲôline ������fightback_score��tiaodou��0�����߶����ǣ�
int panduan_lineindex(Info& info,TTowerID j,TTowerID k)
{
	int pan1=_evaluate_detail[addLine][j][k][fightback_score]>fence;
	int pan2=_evaluate_detail[addLine][j][k][fightback_score]>_evaluate_detail[addLine][j][k][budao_score];
	int pan3=_evaluate_detail[addLine][j][k][fightback_score]>_evaluate_detail[addLine][j][k][help_score];
	int pan4=_evaluate_detail[addLine][j][k][fightback_score]>_evaluate_detail[addLine][j][k][tiaodou];

	if(pan1&&pan2&&pan3&&pan4)
		return fightback_score;

	int pan2_1=_evaluate_detail[addLine][j][k][tiaodou]>fence;
	int pan2_2=_evaluate_detail[addLine][j][k][tiaodou]>_evaluate_detail[addLine][j][k][budao_score];
	int pan2_3=_evaluate_detail[addLine][j][k][tiaodou]>_evaluate_detail[addLine][j][k][help_score];
	int pan2_4=_evaluate_detail[addLine][j][k][tiaodou]>_evaluate_detail[addLine][j][k][fightback_score];

	if(pan2_1&&pan2_2&&pan2_3&&pan2_4)
		return tiaodou;

	return 0;
}
//�����ϣ������0,���򷵻�1��
int rank_judge(Info& info)
{
	if(info.playerInfo[info.myID].alive==0)
		return 1;
	int numm=0;
	for (int i = 0; i < 12; i++)
	{
		if(info.towerInfo[i].owner==info.myID)
			numm++;
	}
	if(numm>=3)
		return 1;
	else if(numm==2&&player_resource(info,info.myID)<200&&info.round>120)
		return 0;
	else if(numm==1)
		return 0;

	int i,j;
	int max;
	//�ĸ���ң���һ��Ϊѡ��ID���ڶ���ӵ��������Ŀ��������ĳһѡ������Դ��
	int playermessage[4][3];
	//�����ʣ���Һ�һ�����ˣ�Ӳ��
	if(info.playerAlive<3)
		return 1;
	//ʣ�೬������
	for(i=0;i<4;i++)
	{
		playermessage[i][0]=i;
		playermessage[i][1]=0;
		playermessage[i][2]=player_resource(info,i);
	}
	for(j=0;j<4;j++)
     	for(i=0;i<13;i++)
	    	if(info.towerInfo[i].owner==playermessage[j][0])
		   {
			  playermessage[j][1]++;
		    }
	for(i=0;i<4;i++)
		if(info.playerInfo[i].rank==1)
			break;
	max=i;
	//��һ������������8����Դ������80%
	int pan1=(playermessage[max][1]>8&&playermessage[max][2]>0.6*all_resource(info))&&(info.playerAlive==4);
	int pan2=(playermessage[max][1]>8&&playermessage[max][2]>0.7*all_resource(info))&&(info.playerAlive==3);
	if(pan1||pan2)
	{
		 //�ҵ�����С��4����Դ��С��15%
	   if(playermessage[info.myID][1]<4&&playermessage[info.myID][2]<0.15*all_resource(info))
		   return 0;
	   else 
		   return 1;
	}
	else 
		return 1;
}
void gou_xingwei(Info& info,int i)
{
	if(info.towerInfo[i].owner!=info.myID)
		return;

	//����*******************************
	if(info.towerInfo[i].resource>0.9*info.towerInfo[i].maxResource)
	{
		if(info.towerInfo[i].strategy!=Defence)
			_evaluate[changeStrategy][i][Defence]+=(fence+32);
	}
	else
	{
		for (int u = 0; u < 4; u++)
		{
			_evaluate[changeStrategy][i][u]+=strategychange(info,i,u);
		}	
	}
	//cutline***************************
	for(int j=0;j<13;j++)
	{
		if(info.lineInfo[i][j].exist==0)
			continue;
		
		if(_lines_index[i][j]!=fightback_score)
			_evaluate[cutLine][i][j]+=((fence+45)*_times_song_le);

		if(_lines_index[i][j]==fightback_score)
			_evaluate[cutLine][i][j]+=((fightback_lines_control(info,i,j))*_times_fightback_cut);
	}

	//addline  *******************  fightback
	for(int j=0;j<13;j++)
	{
		if(info.lineInfo[i][j].exist==1||info.towerInfo[j].owner==info.myID)
			continue;
		if(info.towerInfo[j].owner!=info.myID&&info.lineInfo[i][j].exist==0&&info.lineInfo[j][i].exist==1)
			_evaluate_detail[addLine][i][j][fightback_score]=(fightback(info,i,j)*_times_fightback);
		_evaluate[addLine][i][j]+=(_evaluate_detail[addLine][i][j][fightback_score]);
	}
}
//                                           This is the final release of the zuc5.5 version 10