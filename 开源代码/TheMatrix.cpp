#include "ai.h"
#include "definition.h"
#include "user_toolbox.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

//���б�����Ϣ
struct tower_information{
	int its_id;
	int its_type;
	int its_owner;
	int its_strategy;
	double its_resource;
	double its_occupyPoint;
	double its_occupyOwner;
	TPoint its_position;
	double its_maxResource;
	int its_maxLineNum;
	int its_currentLineNum;
	double its_techSpeed;
};

//���������Ϣ
struct my_tower_information{
	int myTower_id;
	int myTower_type;
	int myTower_owner;
	int myTower_strategy;
	double myTower_resource;
	double myTower_occupyPoint;
	double myTower_occupyOwner;
	TPoint myTower_position;
	double myTower_maxResource;
	int myTower_maxLineNum;
	int myTower_currentLineNum;
	double myTower_techSpeed;
	int myTower_state;//defencing/attacking/growing/supporting
};

//�з�������Ϣ
struct enemy_tower_information{
	int enemyTower_id;
	int enemyTower_type;
	int enemyTower_owner;
	int enemyTower_strategy;
	double enemyTower_resource;
	double enemyTower_occupyPoint;
	double enemyTower_occupyOwner;
	TPoint enemyTower_position;
	double enemyTower_maxResource;
	int enemyTower_maxLineNum;
	int enemyTower_currentLineNum;
	double enemyTower_techSpeed;
};
struct enemy_information{
	enemy_tower_information enemy_tower_info[13];
	bool enemy_alive;
	int enemy_tower_TotalNum;
	double enemy_totalResource;
};

//���б�����Ϣ
struct line_information{
	bool line_exist;
	int line_sourceTower;
	int line_targetTower;
	int line_state;
	double line_maxlength;
	double line_resource;
	double line_frontResource;
	double line_backResource;
};

//�����¼
tower_information tower_info[13];
my_tower_information my_tower_info[13];
enemy_information enemy_info[3];
line_information line_info[13][13];

//ȷ��������Ϣ
//������
int my_id = 0;
//����������
int my_tower_TotalNumber = 0;
//����Ŀǰ������
int my_current_control_number = 0;
//����ʣ��Ƽ�����
double my_current_tech = 0;

//��¼���ߴ��ڵĻغ���
int lineExistRound[13][13];

//��������
//���ߵ���غϣ�Դ��id��Ŀ����id��info�������ر��ߵ���Ŀ�����Ļغ���
double LineArriveRound(int, int, Info&);
//���ߵ����ܻغ�����Դ��id��Ŀ����id��info�������شӷ�����������ܻغ���
double LineTotalRound(int, int, Info&);
//�ռ����б�����Ϣ
void TowerInformationCollect(Info&);
//ȷ�����������Ϣ
void myTowerInformationCollect(Info&);
//ȷ�ϵз�������Ϣ
void enemyInformationCollect(Info&);
//�ռ����б�����Ϣ
void LineInformationCollect(Info&);
//�ж���������״̬
void towerStateJudge(Info&);
//����ģʽ��ʹ�ã��������ʱ������Դ̫�٣��������б��ߣ���id��info��
void ifFallback(int, Info&);
//������Сֵ����
double minimum(double, double);
//�������ֵ����
double maximum(double, double);
//������������
void upgradeLevel(Info&);
//�����������յ�Ŀ�����ľ��������������Ŀ�����������������ġ���������������ߡ�������id
int myTowerSort(int, Info&);
//Debug
void Debug(Info&);



//������
void player_ai(Info& info){
	//ȷ��������Ϣ
	//������
	my_id = info.myID;
	//����������
	my_tower_TotalNumber = 0;
	//����Ŀǰ������
	my_current_control_number = 0;
	//����ʣ��Ƽ�����
	my_current_tech = info.playerInfo[my_id].technologyPoint;

	//�ռ����б�����Ϣ
	TowerInformationCollect(info);

	//ȷ�����������Ϣ
	myTowerInformationCollect(info);

	//ȷ�ϵз�������Ϣ
	enemyInformationCollect(info);

	//�ռ����б�����Ϣ
	LineInformationCollect(info);

	//�ж���������״̬
	towerStateJudge(info);

	//�ж�ÿ�����ű��ߴ��ڵĻغ���
	for (int x = 0; x < 13; x++){
		for (int y = 0; y < 13; y++){
			if (line_info[x][y].line_exist == true && line_info[x][y].line_state == Confrontation){
				lineExistRound[x][y]++;
			}
			else{
				lineExistRound[x][y] = 0;
			}
		}
	}
	//Debug
	/*cout << "Round" << info.round << endl;
	for (int x = 0; x < 13; x++){
		for (int y = 0; y < 13; y++){
			if (line_info[x][y].line_exist == true && line_info[x][y].line_state == Confrontation){
				for (int t = 0; t < my_tower_TotalNumber; t++){
					if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id){
						cout << line_info[x][y].line_sourceTower << '\t' << line_info[x][y].line_targetTower << '\t' << lineExistRound[x][y] << endl;
					}
				}
			}
		}
	}
	system("pause");*/

	//��Ϸ����
	int towerLeft = 13;
	for (int i = 0; i < 13; i++){
		if (info.towerInfo[i].owner == my_id || info.towerInfo[i].owner == -1){
			towerLeft--;
		}
	}
	if (towerLeft == 0){
		return;
	}

	//ֻʣһ��������ס
	if (my_tower_TotalNumber == 1){
		//�ж����б���
		for (int x = 0; x < 13; x++){
			for (int y = 0; y < 13; y++){
				if (line_info[x][y].line_sourceTower == my_tower_info[0].myTower_id && line_info[x][y].line_exist == true){
					double sourceTower_resourceNeed = my_tower_info[0].myTower_maxResource - my_tower_info[0].myTower_resource;
					int devideTroops = (int)sourceTower_resourceNeed;
					info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
					//my_current_control_number++;
				}
			}
		}
		//ת������
		if (my_tower_info[0].myTower_strategy != Defence){
			info.myCommandList.addCommand(changeStrategy, my_tower_info[0].myTower_id, Defence);
			//my_current_control_number++;
		}
		return;
	}

	//�ж�ÿ�������Ƿ���Ҫ���ر���
	for (int i = 0; i < my_tower_TotalNumber; i++){
		ifFallback(my_tower_info[i].myTower_id, info);
	}

	//Debug
	/*cout << "Round" << info.round << endl;
	for (int i = 0; i < my_tower_TotalNumber; i++){
		cout << my_tower_info[i].myTower_id << '\t';
	}
	cout << endl;
	for (int r = 0; r < 3; r++){
		cout << r << '\t' << enemy_info[r].enemy_alive << endl;
		for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
			cout << enemy_info[r].enemy_tower_info[m].enemyTower_id << '\t';
		}
		cout << endl;
	}
	system("pause");*/

	//�Ƿ���������defencing״̬
	bool isdefencing = false;
	for (int i = 0; i < my_tower_TotalNumber; i++){
		if (my_tower_info[i].myTower_state == 0){
			isdefencing = true;
			break;
		}
	}

	//��û����defencing��״̬���Ƿ���������attacking״̬
	bool isattacking = false;
	if (!isdefencing){
		for (int i = 0; i < my_tower_TotalNumber; i++){
			if (my_tower_info[i].myTower_state == 1){
				isattacking = true;
				break;
			}
		}
	}

	//����ģʽ
	if (isdefencing){
		while (my_current_control_number < info.myMaxControl){
			//1.ת��������defence��grow
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 0){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
								for (int r = 0; r < 3; r++){
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											double arriveTime = LineArriveRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
											double totalTime = LineTotalRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
											if ((arriveTime / totalTime) <= 0.4 || line_info[x][y].line_state == 1 || line_info[x][y].line_state == 2 || line_info[x][y].line_state == 3){
												//�������������ǹ���״̬���������ĳ�defence
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy == 1){
													if (my_tower_info[t].myTower_strategy != 2){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 3){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 2);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 2);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												else{
													//��������������grow���������ĳ�attack
													if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy == 3){
														if (my_tower_info[t].myTower_strategy != 1){
															if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 3){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
																my_current_tech -= 3;
																//my_current_control_number++;
															}
															if ((my_tower_info[t].myTower_strategy == 3 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 5){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
																my_current_tech -= 5;
																//my_current_control_number++;
															}
														}
													}
													else{
														if (my_tower_info[t].myTower_strategy != 3){
															if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 4){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
																my_current_tech -= 3;
																//my_current_control_number++;
															}
															if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 6){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
																my_current_tech -= 5;
																//my_current_control_number++;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//2.�ջر�������֧Ԯ����
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 0 && my_tower_info[t].myTower_resource <= (0.8 * my_tower_info[t].myTower_maxResource)){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
								for (int r = 0; r < my_tower_TotalNumber; r++){
									//�������ж���growing��supporting��֮��ı���
									if (line_info[x][y].line_targetTower == my_tower_info[r].myTower_id && line_info[x][y].line_exist == true && (my_tower_info[r].myTower_state == 2 || my_tower_info[r].myTower_state == 3)){
										double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
										int devideTroops = (int)sourceTower_resourceNeed;
										info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
										//my_current_control_number++;
									}
									//��ʱ�ж���attacking��defencing��֮��ı���
									if (line_info[x][y].line_targetTower == my_tower_info[r].myTower_id && line_info[x][y].line_exist == true && (my_tower_info[r].myTower_state == 0 || my_tower_info[r].myTower_state == 1)){
										for (int p = 0; p < 13; p++){
											for (int q = 0; q < 13; q++){
												if (line_info[p][q].line_targetTower == my_tower_info[t].myTower_id && line_info[p][q].line_exist == true){
													for (int e = 0; e < 3; e++){
														for (int m = 0; m < enemy_info[e].enemy_tower_TotalNum; m++){
															double arriveTime = LineArriveRound(enemy_info[e].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
															double totalTime = LineTotalRound(enemy_info[e].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
															if ((arriveTime / totalTime) <= 0.3){
																double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
																int devideTroops = (int)sourceTower_resourceNeed;
																info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
																//my_current_control_number++;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//3.�������߶���
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 0){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
								for (int r = 0; r < 3; r++){
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											double arriveTime = LineArriveRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
											double totalTime = LineTotalRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
											if ((arriveTime / totalTime) <= 0.5 && (my_tower_info[t].myTower_currentLineNum <= my_tower_info[t].myTower_maxLineNum)){
												if (line_info[my_tower_info[t].myTower_id][enemy_info[r].enemy_tower_info[m].enemyTower_id].line_exist == false){
													info.myCommandList.addCommand(addLine, my_tower_info[t].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id);
													//my_current_control_number++;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//4.֧Ԯ
			for (int i = 0; i < my_tower_TotalNumber; i++){
				for (int j = 0; j < my_tower_TotalNumber; j++){
					if (my_tower_info[j].myTower_state == 0 && (my_tower_info[j].myTower_resource <= (0.7 * my_tower_info[j].myTower_maxResource))){
						for (int x = 0; x < 13; x++){
							for (int y = 0; y < 13; y++){
								if (line_info[x][y].line_targetTower == my_tower_info[j].myTower_id && line_info[x][y].line_exist == true){
									if ((my_tower_info[i].myTower_state == 2) || (my_tower_info[i].myTower_state == 3) || ((my_tower_info[i].myTower_state == 1) && (((my_tower_info[i].myTower_resource >= (0.4 * my_tower_info[i].myTower_maxResource)) || (my_tower_info[j].myTower_resource <= (0.5 * my_tower_info[j].myTower_maxResource)))))){
										for (int r = 0; r < 3; r++){
											if (enemy_info[r].enemy_alive == false){
												continue;
											}
											for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
												if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
													double arriveTime = LineArriveRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[j].myTower_id, info);
													double totalTime = LineTotalRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[j].myTower_id, info);
													if (((arriveTime / totalTime) <= 0.7) && (my_tower_info[i].myTower_currentLineNum <= my_tower_info[i].myTower_maxLineNum)){
														if (line_info[my_tower_info[i].myTower_id][my_tower_info[j].myTower_id].line_exist == false){
															info.myCommandList.addCommand(addLine, my_tower_info[i].myTower_id, my_tower_info[j].myTower_id);
															//my_current_control_number++;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//���defenceתgrow���ȼ�
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if ((my_tower_info[i].myTower_state == 2 || my_tower_info[i].myTower_state == 3) && my_tower_info[i].myTower_strategy != 3){
					if (my_tower_info[i].myTower_strategy == 0 && my_current_tech >= 7){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 3;
						//my_current_control_number++:
					}
					if ((my_tower_info[i].myTower_strategy == 2 || my_tower_info[i].myTower_strategy == 1) && (my_current_tech >= 10)){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 5;
						//my_current_control_number++:
					}
				}
			}
			//֧Ԯ��ʽ��Ϊ�б���
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if (my_tower_info[i].myTower_state == 0){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
								for (int j = 0; j < my_tower_TotalNumber; j++){
									if (line_info[x][y].line_sourceTower == my_tower_info[j].myTower_id && line_info[x][y].line_state == Arrived){
										if (my_tower_info[j].myTower_resource >= 0.7 * my_tower_info[j].myTower_maxResource){
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											int devideTroops = (int)(line_info[x][y].line_resource - targetTower_resourceNeed);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, 0));
											//my_current_control_number++;
										}
										else{
											double sourceTower_resourceNeed = my_tower_info[j].myTower_maxResource - my_tower_info[j].myTower_resource;
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											double troops = line_info[x][y].line_resource;
											double devideResource_sourceTower = (0.2 * sourceTower_resourceNeed) / (sourceTower_resourceNeed + targetTower_resourceNeed);
											int devideTroops = (int)(troops * devideResource_sourceTower);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, line_info[x][y].line_resource - targetTower_resourceNeed));
											//my_current_control_number++;
										}
									}
								}
							}
						}
					}
				}
			}
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if (my_tower_info[i].myTower_state == 1){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
								for (int j = 0; j < my_tower_TotalNumber; j++){
									if (line_info[x][y].line_sourceTower == my_tower_info[j].myTower_id && line_info[x][y].line_state == Arrived){
										if (my_tower_info[j].myTower_resource >= 0.7 * my_tower_info[j].myTower_maxResource){
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											int devideTroops = (int)(line_info[x][y].line_resource - targetTower_resourceNeed);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, 0));
											//my_current_control_number++;
										}
										else{
											double sourceTower_resourceNeed = my_tower_info[j].myTower_maxResource - my_tower_info[j].myTower_resource;
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											double troops = line_info[x][y].line_resource;
											double devideResource_sourceTower = (0.2 * sourceTower_resourceNeed) / (sourceTower_resourceNeed + targetTower_resourceNeed);
											int devideTroops = (int)(troops * devideResource_sourceTower);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, line_info[x][y].line_resource - targetTower_resourceNeed));
											//my_current_control_number++;
										}
									}
								}
							}
						}
					}
				}
			}
			//5.���ط���
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 1 || my_tower_info[t].myTower_state == 0){
					ifFallback(my_tower_info[t].myTower_id, info);
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true && (line_info[x][y].line_state == 4)){
								for (int r = 0; r < 3; r++){
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											//������ֱ�������Դ���ڶԷ�������Դ����ʼ����
											double attackingResource = 0.0;
											for (int p = 0; p < 13; p++){
												for (int q = 0; q < 13; q++){
													if (line_info[p][q].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[p][q].line_exist == true){
														for (int w = 0; w < my_tower_TotalNumber; w++){
															if (line_info[p][q].line_sourceTower == my_tower_info[w].myTower_id){
																attackingResource += (my_tower_info[w].myTower_resource - (line_info[p][q].line_maxlength / 10));
															}
														}
													}
												}
											}
											if (attackingResource >= (2 * enemy_info[r].enemy_tower_info[m].enemyTower_resource)){
												//ת������
												//�Է�������defenceʱ��תattack
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
													if (my_tower_info[t].myTower_strategy != 1){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�Է�����defenceʱ��תgrow
												else{
													if (my_tower_info[t].myTower_strategy != 3){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && (my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource))){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}

											/*if ((tower_info[t].its_resource - (line_info[x][y].line_maxlength / 10)) >= (0.6 * my_tower_info[t].myTower_maxResource) && ((enemy_info[r].enemy_tower_info[m].enemyTower_resource <= 50) || (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.8 * enemy_info[r].enemy_tower_info[m].enemyTower_maxResource)))){
												//ת������
												//�Է�������defenceʱ��תattack
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
													if (my_tower_info[t].myTower_strategy != 1){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�Է�����defenceʱ��תgrow
												else{
													if (my_tower_info[t].myTower_strategy != 3){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && (my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource))){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}*/
										}
									}
								}
							}
						}
					}
				}
			}
			//6.��������
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 1){
					ifFallback(my_tower_info[t].myTower_id, info);
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true && line_info[x][y].line_state == 0){
								for (int r = 0; r < 3; r++){
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											//������ֱ�������Դ���ڶԷ�������Դ����ʼ����
											double attackingResource = 0.0;
											for (int p = 0; p < 13; p++){
												for (int q = 0; q < 13; q++){
													if (line_info[p][q].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[p][q].line_exist == true){
														for (int w = 0; w < my_tower_TotalNumber; w++){
															if (line_info[p][q].line_sourceTower == my_tower_info[w].myTower_id){
																attackingResource += (my_tower_info[w].myTower_resource - (line_info[p][q].line_maxlength / 10));
															}
														}
													}
												}
											}
											if (attackingResource >= (2 * enemy_info[r].enemy_tower_info[m].enemyTower_resource)){
												//ת������
												//�Է�������defenceʱ��תattack
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
													if (my_tower_info[t].myTower_strategy != 1){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�Է�����defenceʱ��תgrow
												else{
													if (my_tower_info[t].myTower_strategy != 3){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && (my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource))){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}
											
											//���������Դ�㹻����ʼ����
											/*if ((my_tower_info[t].myTower_resource - (line_info[x][y].line_maxlength / 10)) >= (0.6 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && ((enemy_info[r].enemy_tower_info[m].enemyTower_resource <= 50) || (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.8 * enemy_info[r].enemy_tower_info[m].enemyTower_maxResource)))){
												//��ʱ
												double arriveTime = LineArriveRound(my_tower_info[t].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id, info);
												double totalTime = LineTotalRound(my_tower_info[t].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id, info);
												if ((arriveTime / totalTime) <= 0.2){
													//ת������
													//�Է�������defenceʱ��תattack
													if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
														if (my_tower_info[t].myTower_strategy != 1){
															if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
																my_current_tech -= 3;
																//my_current_control_number++;
															}
															if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
																my_current_tech -= 5;
																//my_current_control_number++;
															}
														}
													}
													//�Է�����defenceʱ��תgrow
													else{
														if (my_tower_info[t].myTower_strategy != 3){
															if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
																my_current_tech -= 3;
																//my_current_control_number++;
															}
															if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
																info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
																my_current_tech -= 5;
																//my_current_control_number++;
															}
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource) && line_info[x][y].line_state == 4){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}*/
										}
									}
								}
							}
						}
					}
				}
			}
			//7.Χκ����
			for (int t = 0; t < my_tower_TotalNumber; t++){
				/*if (my_tower_info[t].myTower_state == 0){
					int attackingLineNum = 0;
					enemy_tower_information enemy_attacking_tower_info[13];
					int countAttackingTower = 0;
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
								for (int r = 0; r < 3; r++){
									if (enemy_info[r].enemy_alive == false){
										continue;
									}
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											attackingLineNum++;
											enemy_attacking_tower_info[countAttackingTower].enemyTower_id = enemy_info[r].enemy_tower_info[m].enemyTower_id;
											enemy_attacking_tower_info[countAttackingTower].enemyTower_position = enemy_info[r].enemy_tower_info[m].enemyTower_position;
											countAttackingTower++;
										}
									}
								}
							}
						}
					}
					if (attackingLineNum > my_tower_info[t].myTower_maxLineNum){
						for (int f = 0; f < attackingLineNum; f++){
							for (int x = 0; x < 13; x++){
								for (int y = 0; y < 13; y++){
									if (line_info[x][y].line_sourceTower == enemy_attacking_tower_info[f].enemyTower_id && line_info[x][y].line_exist == true && line_info[x][y].line_targetTower == my_tower_info[t].myTower_id){
										bool ifRescue = false;
										for (int a = 0; a < 13; a++){
											for (int b = 0; b < 13; b++){
												if (line_info[a][b].line_targetTower == enemy_attacking_tower_info[f].enemyTower_id && line_info[x][y].line_exist == true){
													for (int p = 0; p < my_tower_TotalNumber; p++){
														if (line_info[a][b].line_sourceTower == my_tower_info[p].myTower_id){
															ifRescue = true;
															break;
														}
													}
												}
											}
										}
										if (ifRescue == false){
											double minAttackingDistance = 10000000.0;
											int myTowerRescueID = -1;
											for (int e = 0; e < my_tower_TotalNumber; e++){
												if ((my_tower_info[e].myTower_id != my_tower_info[t].myTower_id) && (my_tower_info[e].myTower_state == 2 || my_tower_info[e].myTower_state == 3) && (my_tower_info[e].myTower_currentLineNum < my_tower_info[e].myTower_maxLineNum) && (my_tower_info[e].myTower_resource >= (0.4 * my_tower_info[e].myTower_maxResource))){
													double currentAttackingDistance = getDistance(my_tower_info[e].myTower_position, enemy_attacking_tower_info[f].enemyTower_position);
													if (minAttackingDistance >= currentAttackingDistance){
														minAttackingDistance = currentAttackingDistance;
														myTowerRescueID = e;
													}
												}
											}
											if (myTowerRescueID != -1){
												double arriveTime = LineArriveRound(enemy_attacking_tower_info[f].enemyTower_id, my_tower_info[t].myTower_id, info);
												double totalTime = LineTotalRound(enemy_attacking_tower_info[f].enemyTower_id, my_tower_info[t].myTower_id, info);
												if ((((arriveTime / totalTime) <= 0.4) || line_info[x][y].line_state == 4) && (line_info[my_tower_info[myTowerRescueID].myTower_id][enemy_attacking_tower_info[f].enemyTower_id].line_exist == false)){
													info.myCommandList.addCommand(addLine, my_tower_info[myTowerRescueID].myTower_id, enemy_attacking_tower_info[f].enemyTower_id);
													//my_current_control_number++;
												}
											}
										}
									}
								}
							}
						}
					}
				}*/
				//��һ�ֲ���
				if (my_tower_info[t].myTower_state == 0){
					int attackingLineNum = 0;
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
								for (int r = 0; r < 3; r++){
									if (enemy_info[r].enemy_alive == false){
										continue;
									}
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											attackingLineNum++;
										}
									}
								}
							}
						}
					}
					if (attackingLineNum > my_tower_info[t].myTower_maxLineNum){
						int supportTowerID = myTowerSort(my_tower_info[t].myTower_id, info);
						if (supportTowerID != -1){
							for (int w = 0; w < my_tower_TotalNumber; w++){
								if (my_tower_info[w].myTower_id == supportTowerID){
									for (int x = 0; x < 13; x++){
										for (int y = 0; y < 13; y++){
											if (line_info[x][y].line_targetTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
												for (int r = 0; r < 3; r++){
													for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
														if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
															bool ifrescue = false;
															for (int p = 0; p < 13; p++){
																for (int q = 0; q < 13; q++){
																	if (line_info[p][q].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
																		for (int e = 0; e < my_tower_TotalNumber; e++){
																			if (line_info[p][q].line_sourceTower == my_tower_info[e].myTower_id){
																				ifrescue = true;
																				break;
																			}
																		}
																	}
																}
															}
															if (!ifrescue){
																double arriveTime = LineArriveRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
																double totalTime = LineTotalRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[t].myTower_id, info);
																if (((arriveTime / totalTime) <= 1) && (line_info[my_tower_info[w].myTower_id][enemy_info[r].enemy_tower_info[m].enemyTower_id].line_exist == false)){
																	info.myCommandList.addCommand(addLine, my_tower_info[w].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id);
																	//my_current_control_number++;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//8.����ס���������Դ�������������
			for (int i = 0; i < my_tower_TotalNumber; i++){
				for (int j = 0; j < my_tower_TotalNumber; j++){
					if (my_tower_info[j].myTower_state == 0 && (my_tower_info[j].myTower_resource > (0.7 * my_tower_info[j].myTower_maxResource))){
						for (int x = 0; x < 13; x++){
							for (int y = 0; y < 13; y++){
								if (line_info[x][y].line_targetTower == my_tower_info[j].myTower_id && line_info[x][y].line_exist == true){
									if ((my_tower_info[i].myTower_state == 2) || (my_tower_info[i].myTower_state == 3) || ((my_tower_info[i].myTower_state == 1) && ((my_tower_info[i].myTower_resource >= (0.4 * my_tower_info[i].myTower_maxResource))))){
										for (int r = 0; r < 3; r++){
											if (enemy_info[r].enemy_alive == false){
												continue;
											}
											for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
												if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
													double arriveTime = LineArriveRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[j].myTower_id, info);
													double totalTime = LineTotalRound(enemy_info[r].enemy_tower_info[m].enemyTower_id, my_tower_info[j].myTower_id, info);
													if (((arriveTime / totalTime) <= 0.7) && (my_tower_info[i].myTower_currentLineNum <= my_tower_info[i].myTower_maxLineNum)){
														if (line_info[my_tower_info[i].myTower_id][enemy_info[r].enemy_tower_info[m].enemyTower_id].line_exist == false){
															info.myCommandList.addCommand(addLine, my_tower_info[i].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id);
															//my_current_control_number++;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//8.�ж϶���ʱ��̫���ı���
			for (int x = 0; x < 13; x++){
				for (int y = 0; y < 13; y++){
					if (line_info[x][y].line_exist == true && line_info[x][y].line_state == Confrontation){
						for (int t = 0; t < my_tower_TotalNumber; t++){
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id){
								for (int r = 0; r < 3; r++){
									if (enemy_info[r].enemy_alive == false){
										continue;
									}
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && (0.8 * enemy_info[r].enemy_tower_info[m].enemyTower_resource >= ((my_tower_info[t].myTower_resource - (line_info[x][y].line_maxlength / 10))))){
											if (lineExistRound[x][y] >= 5){
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//9.�ж϶������
			for (int x = 0; x < 13; x++){
				for (int y = 0; y < 13; y++){
					if (line_info[x][y].line_exist == true){
						for (int t = 0; t < my_tower_TotalNumber; t++){
							if ((line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id) && (my_tower_info[t].myTower_state == 2 || my_tower_info[t].myTower_state == 3)){
								for (int r = 0; r < my_tower_TotalNumber; r++){
									if ((line_info[x][y].line_targetTower == my_tower_info[r].myTower_id) && (my_tower_info[r].myTower_state == 2 || my_tower_info[r].myTower_state == 3)){
										double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
										double targetTower_resourceNeed = my_tower_info[r].myTower_maxResource - my_tower_info[r].myTower_resource;
										double troops = line_info[x][y].line_resource;
										double devideResource_sourceTower = sourceTower_resourceNeed / (sourceTower_resourceNeed + targetTower_resourceNeed);
										int devideTroops = (int)(troops * devideResource_sourceTower);
										info.myCommandList.addCommand(cutLine, x, y, devideTroops);
										//my_current_control_number++;
									}
								}
							}
						}
					}
				}
			}
			//10.ת������������
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if ((my_tower_info[i].myTower_state == 2 || my_tower_info[i].myTower_state == 3) && my_tower_info[i].myTower_strategy != 3){
					if (my_tower_info[i].myTower_strategy == 0 && my_current_tech >= 7){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 3;
						//my_current_control_number++:
					}
					if ((my_tower_info[i].myTower_strategy == 2 || my_tower_info[i].myTower_strategy == 1) && (my_current_tech >= 10)){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 5;
						//my_current_control_number++:
					}
				}
			}
			//11.������������
			upgradeLevel(info);
			my_current_control_number++;
		}
	}
	//����ģʽ
	if (isattacking){
		while (my_current_control_number < info.myMaxControl){
			//1.�ѷ����ı����ж��Ƿ�Ӧ���ж�
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if (my_tower_info[t].myTower_state == 1){
					ifFallback(my_tower_info[t].myTower_id, info);
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true && line_info[x][y].line_state == 4){
								for (int r = 0; r < 3; r++){
									for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
										if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
											//������ֱ�������Դ���ڶԷ�������Դ����ʼ����
											double attackingResource = 0.0;
											for (int p = 0; p < 13; p++){
												for (int q = 0; q < 13; q++){
													if (line_info[p][q].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[p][q].line_exist == true){
														for (int w = 0; w < my_tower_TotalNumber; w++){
															if (line_info[p][q].line_sourceTower == my_tower_info[w].myTower_id){
																attackingResource += (my_tower_info[w].myTower_resource - (line_info[p][q].line_maxlength / 10));
															}
														}
													}
												}
											}
											if (attackingResource >= (2 * enemy_info[r].enemy_tower_info[m].enemyTower_resource)){
												//ת������
												//�Է�������defenceʱ��תattack
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
													if (my_tower_info[t].myTower_strategy != 1){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�Է�����defenceʱ��תgrow
												else{
													if (my_tower_info[t].myTower_strategy != 3){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && (my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource))){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}


											//����������������Դ���㣬��ʼ����
											/*if ((my_tower_info[t].myTower_resource - (line_info[x][y].line_maxlength / 10)) >= (0.6 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && ((enemy_info[r].enemy_tower_info[m].enemyTower_resource <= 50) || (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.8 * enemy_info[r].enemy_tower_info[m].enemyTower_maxResource)))){
												//ת������
												//�Է�������defenceʱ��תattack
												if (enemy_info[r].enemy_tower_info[m].enemyTower_strategy != 2){
													if (my_tower_info[t].myTower_strategy != 1){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 2 || my_tower_info[t].myTower_strategy == 3) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 1);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�Է�����defenceʱ��תgrow
												else{
													if (my_tower_info[t].myTower_strategy != 3){
														if (my_tower_info[t].myTower_strategy == 0 && my_current_tech >= 5){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 3;
															//my_current_control_number++;
														}
														if ((my_tower_info[t].myTower_strategy == 1 || my_tower_info[t].myTower_strategy == 2) && my_current_tech >= 8){
															info.myCommandList.addCommand(changeStrategy, my_tower_info[t].myTower_id, 3);
															my_current_tech -= 5;
															//my_current_control_number++;
														}
													}
												}
												//�жϱ���ͻ������
												if (line_info[x][y].line_resource >= (1.3 * enemy_info[r].enemy_tower_info[m].enemyTower_resource) && my_tower_info[t].myTower_resource >= (0.4 * my_tower_info[t].myTower_maxResource)){
													info.myCommandList.addCommand(cutLine, x, y, 0);
													//my_current_control_number++;
												}
											}
											//�жϴ򲻹������ر���
											else{
												double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
												int devideTroops = (int)sourceTower_resourceNeed;
												info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
												//my_current_control_number++;
											}*/
										}
									}
								}
							}
						}
					}
				}
			}
			//2.֧Ԯ���ڽ�����
			for (int t = 0; t < my_tower_TotalNumber; t++){
				bool ifattacking = false;
				for (int x = 0; x < 13; x++){
					for (int y = 0; y < 13; y++){
						if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true && (line_info[x][y].line_state == 0 || line_info[x][y].line_state == 4)){
							for (int r = 0; r < 3; r++){
								for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
									if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id){
										ifattacking = true;
										break;
									}
								}
							}
						}
					}
				}
				if (ifattacking){
					for (int m = 0; m < my_tower_TotalNumber; m++){
						if ((my_tower_info[m].myTower_state == 2 || my_tower_info[m].myTower_state == 3) && (my_tower_info[t].myTower_resource < (0.7 * my_tower_info[t].myTower_maxResource))){
							if ((my_tower_info[m].myTower_currentLineNum < my_tower_info[m].myTower_maxLineNum) && (my_tower_info[m].myTower_resource >= (0.3* my_tower_info[m].myTower_maxResource))){
								info.myCommandList.addCommand(addLine, my_tower_info[m].myTower_id, my_tower_info[t].myTower_id);
								//my_current_control_number++;
							}
						}
					}
				}
			}
			//֧Ԯ��ʽ��Ϊ�б���
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if (my_tower_info[i].myTower_state == 1){
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
								for (int j = 0; j < my_tower_TotalNumber; j++){
									if (line_info[x][y].line_sourceTower == my_tower_info[j].myTower_id && line_info[x][y].line_state == Arrived){
										if (my_tower_info[j].myTower_resource >= 0.7 * my_tower_info[j].myTower_maxResource){
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											int devideTroops = (int)(line_info[x][y].line_resource - targetTower_resourceNeed);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, 0));
											//my_current_control_number++;
										}
										else{
											double sourceTower_resourceNeed = my_tower_info[j].myTower_maxResource - my_tower_info[j].myTower_resource;
											double targetTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
											double troops = line_info[x][y].line_resource;
											double devideResource_sourceTower = (0.2 * sourceTower_resourceNeed) / (sourceTower_resourceNeed + targetTower_resourceNeed);
											int devideTroops = (int)(troops * devideResource_sourceTower);
											info.myCommandList.addCommand(cutLine, x, y, (int)maximum(devideTroops, line_info[x][y].line_resource - targetTower_resourceNeed));
											//my_current_control_number++;
										}
									}
								}
							}
						}
					}
				}
			}
			//3.Эͬ����
			for (int r = 0; r < 3; r++){
				if (enemy_info[r].enemy_alive == false){
					continue;
				}
				if (enemy_info[r].enemy_alive == true){
					for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
						bool ifBeingAttacked = false;
						for (int x = 0; x < 13; x++){
							for (int y = 0; y < 13; y++){
								for (int e = 0; e < my_tower_TotalNumber; e++){
									if (line_info[x][y].line_sourceTower == my_tower_info[e].myTower_id && line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[x][y].line_exist == true){
										ifBeingAttacked = true;
									}
								}
							}
						}
						if (ifBeingAttacked){
							for (int w = 0; w < my_tower_TotalNumber; w++){
								bool ifSupporting = false;
								for (int i = 0; i < 13; i++){
									for (int j = 0; j < 13; j++){
										if (line_info[i][j].line_sourceTower == my_tower_info[w].myTower_id && line_info[i][j].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[i][j].line_exist == true){
											ifSupporting = true;
										}
									}
								}
								if (ifSupporting == false && (my_tower_info[w].myTower_state == 2 || my_tower_info[w].myTower_state == 3) && my_tower_info[w].myTower_currentLineNum < (my_tower_info[w].myTower_maxLineNum)){
									info.myCommandList.addCommand(addLine, my_tower_info[w].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id);
									//my_current_control_number++;
								}
							}
						}
					}
				}
			}
			//4.�б���ͻ��
			for (int r = 0; r < 3; r++){
				if (enemy_info[r].enemy_alive == false){
					continue;
				}
				for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
					double totalAttackingLineResource = 0.0;
					my_tower_information myAttackingTower[13];
					int totalAttackingTower = 0;
					for (int x = 0; x < 13; x++){
						for (int y = 0; y < 13; y++){
							if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[x][y].line_exist == true){
								for (int e = 0; e < my_tower_TotalNumber; e++){
									if (line_info[x][y].line_sourceTower == my_tower_info[e].myTower_id && line_info[x][y].line_state == 4 && (my_tower_info[e].myTower_resource >= (0.3 * my_tower_info[e].myTower_maxResource))){
										totalAttackingLineResource += line_info[x][y].line_resource;
										myAttackingTower[totalAttackingTower].myTower_id = my_tower_info[e].myTower_id;
										totalAttackingTower++;
									}
								}
							}
						}
					}
					if (totalAttackingLineResource >(40 + enemy_info[r].enemy_tower_info[m].enemyTower_resource)){
						for (int w = 0; w < totalAttackingTower; w++){
							info.myCommandList.addCommand(cutLine, myAttackingTower[w].myTower_id, enemy_info[r].enemy_tower_info[m].enemyTower_id, 0);
							//my_current_control_number++;
						}
					}
				}
			}
			//5.�ж����ñ���
			for (int t = 0; t < my_tower_TotalNumber; t++){
				ifFallback(my_tower_info[t].myTower_id, info);
				for (int x = 0; x < 13; x++){
					for (int y = 0; y < 13; y++){
						if (line_info[x][y].line_exist == true){
							//�жϷ����������֧Ԯ����
							if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && my_tower_info[t].myTower_state == 1){
								for (int r = 0; r < my_tower_TotalNumber; r++){
									if (line_info[x][y].line_targetTower == my_tower_info[r].myTower_id){
										double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
										double targetTower_resourceNeed = my_tower_info[r].myTower_maxResource - my_tower_info[r].myTower_resource;
										double troops = line_info[x][y].line_resource;
										double devideResource_sourceTower = sourceTower_resourceNeed / (sourceTower_resourceNeed + targetTower_resourceNeed);
										int devideTroops = (int)(troops * devideResource_sourceTower);
										info.myCommandList.addCommand(cutLine, x, y, devideTroops);
										//my_current_control_number++;
									}
								}
							}
							//�жϳɳ���֮��ı���
							if ((line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id) && (my_tower_info[t].myTower_state == 2 || my_tower_info[t].myTower_state == 3)){
								for (int r = 0; r < my_tower_TotalNumber; r++){
									if ((line_info[x][y].line_targetTower == my_tower_info[r].myTower_id) && (my_tower_info[r].myTower_state == 2 || my_tower_info[r].myTower_state == 3)){
										double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
										double targetTower_resourceNeed = my_tower_info[r].myTower_maxResource - my_tower_info[r].myTower_resource;
										double troops = line_info[x][y].line_resource;
										double devideResource_sourceTower = sourceTower_resourceNeed / (sourceTower_resourceNeed + targetTower_resourceNeed);
										int devideTroops = (int)(troops * devideResource_sourceTower);
										info.myCommandList.addCommand(cutLine, x, y, devideTroops);
										//my_current_control_number++;
									}
								}
							}
						}
					}
				}
			}
			//6.ת������������
			for (int i = 0; i < my_tower_TotalNumber; i++){
				if ((my_tower_info[i].myTower_state == 2 || my_tower_info[i].myTower_state == 3) && my_tower_info[i].myTower_strategy != 3){
					if (my_tower_info[i].myTower_strategy == 0 && my_current_tech >= 7){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 3;
						//my_current_control_number++:
					}
					if ((my_tower_info[i].myTower_strategy == 2 || my_tower_info[i].myTower_strategy == 1) && (my_current_tech >= 10)){
						info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
						my_current_tech -= 5;
						//my_current_control_number++:
					}
				}
			}
			//7.������������
			upgradeLevel(info);
			my_current_control_number++;
		}
	}

	//�ɳ�ģʽ
	if (!isattacking){
		while (my_current_control_number < info.myMaxControl){
			//1.�ж϶������
			for (int t = 0; t < my_tower_TotalNumber; t++){
				for (int x = 0; x < 13; x++){
					for (int y = 0; y < 13; y++){
						if (line_info[x][y].line_sourceTower == my_tower_info[t].myTower_id && line_info[x][y].line_exist == true){
							for (int r = 0; r < my_tower_TotalNumber; r++){
								if (line_info[x][y].line_targetTower == my_tower_info[r].myTower_id){
									double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
									double targetTower_resourceNeed = my_tower_info[r].myTower_maxResource - my_tower_info[r].myTower_resource;
									double troops = line_info[x][y].line_resource;
									double devideResource_sourceTower = sourceTower_resourceNeed / (sourceTower_resourceNeed + targetTower_resourceNeed);
									int devideTroops = (int)(troops * devideResource_sourceTower);
									info.myCommandList.addCommand(cutLine, x, y, devideTroops);
									//my_current_control_number++;
								}
							}
							for (int r = 0; r < 3; r++){
								for (int e = 0; e < enemy_info[r].enemy_tower_TotalNum; e++){
									if (line_info[x][y].line_targetTower == enemy_info[r].enemy_tower_info[e].enemyTower_id){
										double sourceTower_resourceNeed = my_tower_info[t].myTower_maxResource - my_tower_info[t].myTower_resource;
										int devideTroops = (int)sourceTower_resourceNeed;
										info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
										//my_current_control_number++;
									}
								}
							}
						}
					}
				}
			}
			//2.�ж��Ƿ��𹥻�
			//��������ĵ���
			/*int ableAttackTowerNum = 0;
			my_tower_information ableAttackTower[13];
			double ableAttackTowerResource = 0.0;
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if ((my_tower_info[t].myTower_state == 2) && (my_tower_info[t].myTower_resource >= (0.7 * my_tower_info[t].myTower_maxResource)) && (my_tower_info[t].myTower_currentLineNum < my_tower_info[t].myTower_maxLineNum)){
					ableAttackTower[ableAttackTowerNum].myTower_id = my_tower_info[t].myTower_id;
					ableAttackTower[ableAttackTowerNum].myTower_position = my_tower_info[t].myTower_position;
					ableAttackTowerNum++;
					ableAttackTowerResource += my_tower_info[t].myTower_resource;
				}
			}
			if (ableAttackTowerNum >= 2){
				int attackTargetId = -1;
				double minDistance = 10000000.0;
				tower_information targetEnemyTower;
				targetEnemyTower.its_id = -1;
				for (int r = 0; r < 3; r++){
					if (enemy_info[r].enemy_alive == false){
						continue;
					}
					for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
						if (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource) && enemy_info[r].enemy_alive == true){
							double totalDistance = 0.0;
							for (int q = 0; q < ableAttackTowerNum; q++){
								totalDistance += getDistance(ableAttackTower[q].myTower_position, enemy_info[r].enemy_tower_info[m].enemyTower_position);
							}
							if (totalDistance < minDistance){
								minDistance = totalDistance;
								targetEnemyTower.its_id = enemy_info[r].enemy_tower_info[m].enemyTower_id;
								targetEnemyTower.its_currentLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_currentLineNum;
								targetEnemyTower.its_maxLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_maxLineNum;
								targetEnemyTower.its_maxResource = enemy_info[r].enemy_tower_info[m].enemyTower_maxResource;
								targetEnemyTower.its_occupyOwner = enemy_info[r].enemy_tower_info[m].enemyTower_occupyOwner;
								targetEnemyTower.its_occupyPoint = enemy_info[r].enemy_tower_info[m].enemyTower_occupyPoint;
								targetEnemyTower.its_owner = enemy_info[r].enemy_tower_info[m].enemyTower_owner;
								targetEnemyTower.its_position = enemy_info[r].enemy_tower_info[m].enemyTower_position;
								targetEnemyTower.its_resource = enemy_info[r].enemy_tower_info[m].enemyTower_resource;
								targetEnemyTower.its_strategy = enemy_info[r].enemy_tower_info[m].enemyTower_strategy;
								targetEnemyTower.its_techSpeed = enemy_info[r].enemy_tower_info[m].enemyTower_techSpeed;
								targetEnemyTower.its_type = enemy_info[r].enemy_tower_info[m].enemyTower_type;
							}
						}
					}
				}
				if (minDistance != 1000000.0 && targetEnemyTower.its_id != -1 && info.round > 100){
						info.myCommandList.addCommand(addLine, ableAttackTower[0].myTower_id, targetEnemyTower.its_id);
				}
			}*/
			//���������ĵ���
			/*int ableAttackTowerNum = 0;
			my_tower_information ableAttackTower[13];
			double ableAttackTowerResource = 0.0;
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if ((my_tower_info[t].myTower_state == 2) && (my_tower_info[t].myTower_resource >= (0.7 * my_tower_info[t].myTower_maxResource)) && (my_tower_info[t].myTower_currentLineNum < my_tower_info[t].myTower_maxLineNum)){
					ableAttackTower[ableAttackTowerNum].myTower_id = my_tower_info[t].myTower_id;
					ableAttackTower[ableAttackTowerNum].myTower_position = my_tower_info[t].myTower_position;
					ableAttackTowerNum++;
					ableAttackTowerResource += my_tower_info[t].myTower_resource;
				}
			}
			if (ableAttackTowerNum >= 2){
				int attackTargetId = -1;
				double minDistance = 10000000.0;
				tower_information targetEnemyTower;
				targetEnemyTower.its_id = -1;
				enemy_information targetEnemy;
				targetEnemy.enemy_totalResource = 100000000.0;
				int targetEnemyID = -1;
				for (int r = 0; r < 3; r++){
					if (enemy_info[r].enemy_alive == false){
						continue;
					}
					if (enemy_info[r].enemy_totalResource <= targetEnemy.enemy_totalResource){
						targetEnemy.enemy_totalResource = enemy_info[r].enemy_totalResource;
						targetEnemyID = r;
					}
				}
				if (targetEnemyID != -1){
					for (int m = 0; m < enemy_info[targetEnemyID].enemy_tower_TotalNum; m++){
						if (enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource)){
							double totalDistance = 0.0;
							for (int q = 0; q < ableAttackTowerNum; q++){
								totalDistance += getDistance(ableAttackTower[q].myTower_position, enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_position);
							}
							if (totalDistance < minDistance){
								minDistance = totalDistance;
								targetEnemyTower.its_id = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_id;
								targetEnemyTower.its_currentLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_currentLineNum;
								targetEnemyTower.its_maxLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxLineNum;
								targetEnemyTower.its_maxResource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxResource;
								targetEnemyTower.its_occupyOwner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyOwner;
								targetEnemyTower.its_occupyPoint = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyPoint;
								targetEnemyTower.its_owner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_owner;
								targetEnemyTower.its_position = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_position;
								targetEnemyTower.its_resource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource;
								targetEnemyTower.its_strategy = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_strategy;
								targetEnemyTower.its_techSpeed = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_techSpeed;
								targetEnemyTower.its_type = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_type;
							}
						}
					}
				}
				if (minDistance != 1000000.0 && targetEnemyTower.its_id != -1 && info.round > 100){
					info.myCommandList.addCommand(addLine, ableAttackTower[0].myTower_id, targetEnemyTower.its_id);
				}
			}*/
			//���������ĵ��˵�û�˴����
			/*int ableAttackTowerNum = 0;
			my_tower_information ableAttackTower[13];
			double ableAttackTowerResource = 0.0;
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if ((my_tower_info[t].myTower_state == 2) && (my_tower_info[t].myTower_resource >= (0.7 * my_tower_info[t].myTower_maxResource)) && (my_tower_info[t].myTower_currentLineNum < my_tower_info[t].myTower_maxLineNum)){
					ableAttackTower[ableAttackTowerNum].myTower_id = my_tower_info[t].myTower_id;
					ableAttackTower[ableAttackTowerNum].myTower_position = my_tower_info[t].myTower_position;
					ableAttackTowerNum++;
					ableAttackTowerResource += my_tower_info[t].myTower_resource;
				}
			}
			if (ableAttackTowerNum >= 2){
				int attackTargetId = -1;
				double minDistance = 10000000.0;
				tower_information targetEnemyTower;
				tower_information targetChoices[13];
				int targetNum = 0;
				targetEnemyTower.its_id = -1;
				enemy_information targetEnemy;
				targetEnemy.enemy_totalResource = 100000000.0;
				int targetEnemyID = -1;
				for (int r = 0; r < 3; r++){
					if (enemy_info[r].enemy_alive == false){
						continue;
					}
					if (enemy_info[r].enemy_totalResource <= targetEnemy.enemy_totalResource){
						targetEnemy.enemy_totalResource = enemy_info[r].enemy_totalResource;
						targetEnemyID = r;
					}
				}
				bool firstTargetFound = false;
				if (targetEnemyID != -1){
					for (int m = 0; m < enemy_info[targetEnemyID].enemy_tower_TotalNum; m++){
						if (enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource)){
							bool ifbeingAttacked = false;
							for (int x = 0; x < 13; x++){
								for (int y = 0; y < 13; y++){
									if (line_info[x][y].line_targetTower == enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_id && line_info[x][y].line_exist == true){
										for (int p = 0; p < 13; p++){
											if (line_info[x][y].line_sourceTower == tower_info[p].its_id && tower_info[p].its_owner != my_id && tower_info[p].its_owner != enemy_info[targetEnemyID].enemy_tower_info[0].enemyTower_owner){
												ifbeingAttacked = true;
											}
										}
									}
								}
							}
							if (ifbeingAttacked == false){
								targetChoices[targetNum].its_id = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_id;
								targetChoices[targetNum].its_currentLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_currentLineNum;
								targetChoices[targetNum].its_maxLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxLineNum;
								targetChoices[targetNum].its_maxResource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxResource;
								targetChoices[targetNum].its_occupyOwner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyOwner;
								targetChoices[targetNum].its_occupyPoint = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyPoint;
								targetChoices[targetNum].its_owner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_owner;
								targetChoices[targetNum].its_position = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_position;
								targetChoices[targetNum].its_resource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource;
								targetChoices[targetNum].its_strategy = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_strategy;
								targetChoices[targetNum].its_techSpeed = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_techSpeed;
								targetChoices[targetNum].its_type = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_type;
								targetNum++;
								firstTargetFound = true;
							}
						}
					}
				}
				if (firstTargetFound == true){
					for (int e = 0; e < targetNum; e++){
						double totalDistance = 0.0;
						for (int q = 0; q < ableAttackTowerNum; q++){
							totalDistance += getDistance(ableAttackTower[q].myTower_position, targetChoices[e].its_position);
						}
						if (totalDistance < minDistance){
							minDistance = totalDistance;
							targetEnemyTower.its_id = targetChoices[targetNum].its_id;
							targetEnemyTower.its_currentLineNum = targetChoices[targetNum].its_currentLineNum;
							targetEnemyTower.its_maxLineNum = targetChoices[targetNum].its_maxLineNum;
							targetEnemyTower.its_maxResource = targetChoices[targetNum].its_maxResource;
							targetEnemyTower.its_occupyOwner = targetChoices[targetNum].its_occupyOwner;
							targetEnemyTower.its_occupyPoint = targetChoices[targetNum].its_occupyPoint;
							targetEnemyTower.its_owner = targetChoices[targetNum].its_owner;
							targetEnemyTower.its_position = targetChoices[targetNum].its_position;
							targetEnemyTower.its_resource = targetChoices[targetNum].its_resource;
							targetEnemyTower.its_strategy = targetChoices[targetNum].its_strategy;
							targetEnemyTower.its_techSpeed = targetChoices[targetNum].its_techSpeed;
							targetEnemyTower.its_type = targetChoices[targetNum].its_type;
						}
					}
				}
				else{
					for (int m = 0; m < enemy_info[targetEnemyID].enemy_tower_TotalNum; m++){
						if (enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource)){
							double totalDistance = 0.0;
							for (int q = 0; q < ableAttackTowerNum; q++){
								totalDistance += getDistance(ableAttackTower[q].myTower_position, enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_position);
							}
							if (totalDistance < minDistance){
								minDistance = totalDistance;
								targetEnemyTower.its_id = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_id;
								targetEnemyTower.its_currentLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_currentLineNum;
								targetEnemyTower.its_maxLineNum = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxLineNum;
								targetEnemyTower.its_maxResource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_maxResource;
								targetEnemyTower.its_occupyOwner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyOwner;
								targetEnemyTower.its_occupyPoint = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_occupyPoint;
								targetEnemyTower.its_owner = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_owner;
								targetEnemyTower.its_position = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_position;
								targetEnemyTower.its_resource = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_resource;
								targetEnemyTower.its_strategy = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_strategy;
								targetEnemyTower.its_techSpeed = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_techSpeed;
								targetEnemyTower.its_type = enemy_info[targetEnemyID].enemy_tower_info[m].enemyTower_type;
							}
						}
					}
				}
				if (minDistance != 1000000.0 && targetEnemyTower.its_id != -1 && info.round > 100){
					info.myCommandList.addCommand(addLine, ableAttackTower[0].myTower_id, targetEnemyTower.its_id);
				}
			}*/
			//�������뼺����������ڹ�������
			int ableAttackTowerNum = 0;
			my_tower_information ableAttackTower[13];
			double ableAttackTowerResource = 0.0;
			for (int t = 0; t < my_tower_TotalNumber; t++){
				if ((my_tower_info[t].myTower_state == 2) && (my_tower_info[t].myTower_resource >= (0.7 * my_tower_info[t].myTower_maxResource)) && (my_tower_info[t].myTower_currentLineNum < my_tower_info[t].myTower_maxLineNum)){
					ableAttackTower[ableAttackTowerNum].myTower_id = my_tower_info[t].myTower_id;
					ableAttackTower[ableAttackTowerNum].myTower_position = my_tower_info[t].myTower_position;
					ableAttackTowerNum++;
					ableAttackTowerResource += my_tower_info[t].myTower_resource;
				}
			}
			if (ableAttackTowerNum >= 2){
				double minDistance = 1000000000.0;
				tower_information targetEnemyTower;
				tower_information targetChoices[13];
				int targetNum = 0;
				targetEnemyTower.its_id = -1;
				bool firstTargetFound = false;
				for (int r = 0; r < 3; r++){
					if (enemy_info[r].enemy_alive == false){
						continue;
					}
					for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
						bool ifattacking = false;
						for (int x = 0; x < 13; x++){
							for (int y = 0; y < 13; y++){
								if (line_info[x][y].line_sourceTower == enemy_info[r].enemy_tower_info[m].enemyTower_id && line_info[x][y].line_exist == true && (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource))){
									ifattacking = true;
								}
							}
						}
						if (ifattacking){
							targetChoices[targetNum].its_id = enemy_info[r].enemy_tower_info[m].enemyTower_id;
							targetChoices[targetNum].its_currentLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_currentLineNum;
							targetChoices[targetNum].its_maxLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_maxLineNum;
							targetChoices[targetNum].its_maxResource = enemy_info[r].enemy_tower_info[m].enemyTower_maxResource;
							targetChoices[targetNum].its_occupyOwner = enemy_info[r].enemy_tower_info[m].enemyTower_occupyOwner;
							targetChoices[targetNum].its_occupyPoint = enemy_info[r].enemy_tower_info[m].enemyTower_occupyPoint;
							targetChoices[targetNum].its_owner = enemy_info[r].enemy_tower_info[m].enemyTower_owner;
							targetChoices[targetNum].its_position = enemy_info[r].enemy_tower_info[m].enemyTower_position;
							targetChoices[targetNum].its_resource = enemy_info[r].enemy_tower_info[m].enemyTower_resource;
							targetChoices[targetNum].its_strategy = enemy_info[r].enemy_tower_info[m].enemyTower_strategy;
							targetChoices[targetNum].its_techSpeed = enemy_info[r].enemy_tower_info[m].enemyTower_techSpeed;
							targetChoices[targetNum].its_type = enemy_info[r].enemy_tower_info[m].enemyTower_type;
							targetNum++;
							firstTargetFound = true;
						}
					}
				}
				if (firstTargetFound == true){
					for (int e = 0; e < targetNum; e++){
						double totalDistance = 0.0;
						for (int q = 0; q < ableAttackTowerNum; q++){
							totalDistance += getDistance(ableAttackTower[q].myTower_position, targetChoices[e].its_position);
						}
						if (totalDistance < minDistance){
							minDistance = totalDistance;
							targetEnemyTower.its_id = targetChoices[e].its_id;
							targetEnemyTower.its_currentLineNum = targetChoices[e].its_currentLineNum;
							targetEnemyTower.its_maxLineNum = targetChoices[e].its_maxLineNum;
							targetEnemyTower.its_maxResource = targetChoices[e].its_maxResource;
							targetEnemyTower.its_occupyOwner = targetChoices[e].its_occupyOwner;
							targetEnemyTower.its_occupyPoint = targetChoices[e].its_occupyPoint;
							targetEnemyTower.its_owner = targetChoices[e].its_owner;
							targetEnemyTower.its_position = targetChoices[e].its_position;
							targetEnemyTower.its_resource = targetChoices[e].its_resource;
							targetEnemyTower.its_strategy = targetChoices[e].its_strategy;
							targetEnemyTower.its_techSpeed = targetChoices[e].its_techSpeed;
							targetEnemyTower.its_type = targetChoices[e].its_type;
						}
					}
				}
				else{
					for (int r = 0; r < 3; r++){
						if (enemy_info[r].enemy_alive == false){
							continue;
						}
						for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
							if (enemy_info[r].enemy_tower_info[m].enemyTower_resource <= (0.4 * ableAttackTowerResource) && enemy_info[r].enemy_alive == true){
								double totalDistance = 0.0;
								for (int q = 0; q < ableAttackTowerNum; q++){
									totalDistance += getDistance(ableAttackTower[q].myTower_position, enemy_info[r].enemy_tower_info[m].enemyTower_position);
								}
								if (totalDistance < minDistance){
									minDistance = totalDistance;
									targetEnemyTower.its_id = enemy_info[r].enemy_tower_info[m].enemyTower_id;
									targetEnemyTower.its_currentLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_currentLineNum;
									targetEnemyTower.its_maxLineNum = enemy_info[r].enemy_tower_info[m].enemyTower_maxLineNum;
									targetEnemyTower.its_maxResource = enemy_info[r].enemy_tower_info[m].enemyTower_maxResource;
									targetEnemyTower.its_occupyOwner = enemy_info[r].enemy_tower_info[m].enemyTower_occupyOwner;
									targetEnemyTower.its_occupyPoint = enemy_info[r].enemy_tower_info[m].enemyTower_occupyPoint;
									targetEnemyTower.its_owner = enemy_info[r].enemy_tower_info[m].enemyTower_owner;
									targetEnemyTower.its_position = enemy_info[r].enemy_tower_info[m].enemyTower_position;
									targetEnemyTower.its_resource = enemy_info[r].enemy_tower_info[m].enemyTower_resource;
									targetEnemyTower.its_strategy = enemy_info[r].enemy_tower_info[m].enemyTower_strategy;
									targetEnemyTower.its_techSpeed = enemy_info[r].enemy_tower_info[m].enemyTower_techSpeed;
									targetEnemyTower.its_type = enemy_info[r].enemy_tower_info[m].enemyTower_type;
								}
							}
						}
					}
				}
				if (minDistance != 1000000000.0 && targetEnemyTower.its_id != -1 && info.round > 100){
					info.myCommandList.addCommand(addLine, ableAttackTower[0].myTower_id, targetEnemyTower.its_id);
				}
			}
			//3.��Ϊgrow
			//�غ������٣�����grow
			int currentRound = info.round;
			if (currentRound <= 20){
				for (int i = 0; i < my_tower_TotalNumber; i++){
					if ((my_tower_info[i].myTower_state == 2 || my_tower_info[i].myTower_state == 3) && my_tower_info[i].myTower_strategy != 3){
						if (my_tower_info[i].myTower_strategy == 0 && my_current_tech >= 3){
							info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
							my_current_tech -= 3;
							//my_current_control_number++:
						}
						if ((my_tower_info[i].myTower_strategy == 2 || my_tower_info[i].myTower_strategy == 1) && (my_current_tech >= 5)){
							info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
							my_current_tech -= 5;
							//my_current_control_number++:
						}
					}
				}
			}
			//�غ����϶࣬����grow
			else{
				for (int i = 0; i < my_tower_TotalNumber; i++){
					if ((my_tower_info[i].myTower_state == 2 || my_tower_info[i].myTower_state == 3) && my_tower_info[i].myTower_strategy != 3){
						if (my_tower_info[i].myTower_strategy == 0 && my_current_tech >= 7){
							info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
							my_current_tech -= 3;
							//my_current_control_number++:
						}
						if ((my_tower_info[i].myTower_strategy == 2 || my_tower_info[i].myTower_strategy == 1) && (my_current_tech >= 10)){
							info.myCommandList.addCommand(changeStrategy, my_tower_info[i].myTower_id, 3);
							my_current_tech -= 5;
							//my_current_control_number++:
						}
					}
				}
			}
			//4.������������
			upgradeLevel(info);
			my_current_control_number++;
		}
	}

	//Debug
	//Debug(info);
}


//��������
//�ռ����б�����Ϣ
void TowerInformationCollect(Info &info){
	for (int i = 0; i < 13; i++){
		tower_info[i].its_id = info.towerInfo[i].id;
		tower_info[i].its_type = info.towerInfo[i].type;
		tower_info[i].its_owner = info.towerInfo[i].owner;
		tower_info[i].its_strategy = info.towerInfo[i].strategy;
		tower_info[i].its_resource = info.towerInfo[i].resource;
		tower_info[i].its_occupyPoint = info.towerInfo[i].occupyPoint;
		tower_info[i].its_occupyOwner = info.towerInfo[i].occupyOwner;
		tower_info[i].its_position.m_x = info.towerInfo[i].position.m_x;
		tower_info[i].its_position.m_y = info.towerInfo[i].position.m_y;
		tower_info[i].its_maxResource = info.towerInfo[i].maxResource;
		tower_info[i].its_maxLineNum = info.towerInfo[i].maxLineNum;
		tower_info[i].its_currentLineNum = info.towerInfo[i].currLineNum;
		tower_info[i].its_techSpeed = info.towerInfo[i].techSpeed;
	}
}

//ȷ�����������Ϣ
void myTowerInformationCollect(Info &info){
	//�����������
	for (int i = 0; i < 13; i++){
		if (tower_info[i].its_owner == my_id){
			my_tower_TotalNumber++;
		}
	}
	//���������Ϣ
	int count = 0;
	for (int i = 0; i < 13; i++){
		if (tower_info[i].its_owner == my_id){
			my_tower_info[count].myTower_id = info.towerInfo[i].id;
			my_tower_info[count].myTower_type = info.towerInfo[i].type;
			my_tower_info[count].myTower_owner = info.towerInfo[i].owner;
			my_tower_info[count].myTower_strategy = info.towerInfo[i].strategy;
			my_tower_info[count].myTower_resource = info.towerInfo[i].resource;
			my_tower_info[count].myTower_occupyPoint = info.towerInfo[i].occupyPoint;
			my_tower_info[count].myTower_occupyOwner = info.towerInfo[i].occupyOwner;
			my_tower_info[count].myTower_position.m_x = info.towerInfo[i].position.m_x;
			my_tower_info[count].myTower_position.m_y = info.towerInfo[i].position.m_y;
			my_tower_info[count].myTower_maxLineNum = info.towerInfo[i].maxLineNum;
			my_tower_info[count].myTower_currentLineNum = info.towerInfo[i].currLineNum;
			my_tower_info[count].myTower_state = -1;
			my_tower_info[count].myTower_maxResource = info.towerInfo[i].maxResource;
			my_tower_info[count].myTower_techSpeed = info.towerInfo[i].techSpeed;
			count++;
		}
	}
}

//ȷ�ϵз�������Ϣ
void enemyInformationCollect(Info& info){
	int current_enemy_id = 0;
	for (int r = 0; r < 4; r++){
		if (info.playerInfo[r].id == my_id){
			continue;
		}
		else{
			if (info.playerInfo[r].alive == true){
				enemy_info[current_enemy_id].enemy_alive = true;
				int tower_num = 0;
				for (int i = 0; i < 13; i++){
					if (info.towerInfo[i].owner == info.playerInfo[r].id){
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_id = info.towerInfo[i].id;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_type = info.towerInfo[i].type;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_owner = info.towerInfo[i].owner;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_strategy = info.towerInfo[i].strategy;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_resource = info.towerInfo[i].resource;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_occupyPoint = info.towerInfo[i].occupyPoint;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_occupyOwner = info.towerInfo[i].occupyOwner;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_position.m_x = info.towerInfo[i].position.m_x;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_position.m_y = info.towerInfo[i].position.m_y;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_maxLineNum = info.towerInfo[i].maxLineNum;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_currentLineNum = info.towerInfo[i].currLineNum;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_maxResource = info.towerInfo[i].maxResource;
						enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_techSpeed = info.towerInfo[i].techSpeed;
						tower_num++;
					}
				}
				enemy_info[current_enemy_id].enemy_tower_TotalNum = tower_num;
				current_enemy_id++;
			}
			else{
				enemy_info[current_enemy_id].enemy_alive = false;
				enemy_info[current_enemy_id].enemy_tower_TotalNum = 0;
				current_enemy_id++;
			}
		}
	}
	for (int r = 0; r < 3; r++){
		enemy_info[r].enemy_totalResource = 0;
		if (enemy_info[r].enemy_alive == false){
			enemy_info[r].enemy_totalResource = 10000000000;
		}
		else{
			for (int m = 0; m < enemy_info[r].enemy_tower_TotalNum; m++){
				enemy_info[r].enemy_totalResource += enemy_info[r].enemy_tower_info[m].enemyTower_resource;
			}
		}
	}
	/*int current_enemy_id = 0;
	for (int k = 0; k < 4; k++){
		if (k != my_id){
			int tower_num = 0;
			for (int i = 0; i < 13; i++){
				if (tower_info[i].its_owner == k){
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_id = info.towerInfo[i].id;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_type = info.towerInfo[i].type;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_owner = info.towerInfo[i].owner;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_strategy = info.towerInfo[i].strategy;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_resource = info.towerInfo[i].resource;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_occupyPoint = info.towerInfo[i].occupyPoint;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_occupyOwner = info.towerInfo[i].occupyOwner;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_position.m_x = info.towerInfo[i].position.m_x;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_position.m_y = info.towerInfo[i].position.m_y;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_maxLineNum = info.towerInfo[i].maxLineNum;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_currentLineNum = info.towerInfo[i].currLineNum;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_maxResource = info.towerInfo[i].maxResource;
					enemy_info[current_enemy_id].enemy_tower_info[tower_num].enemyTower_techSpeed = info.towerInfo[i].techSpeed;
					tower_num++;
					enemy_info[current_enemy_id].enemy_tower_TotalNum = tower_num;
				}
			}
			current_enemy_id++;
		}
	}*/
}

//�ռ����б�����Ϣ
void LineInformationCollect(Info& info){
	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 13; j++){
			line_info[i][j].line_exist = info.lineInfo[i][j].exist;
			line_info[i][j].line_sourceTower = info.lineInfo[i][j].sourceTower;
			line_info[i][j].line_targetTower = info.lineInfo[i][j].targetTower;
			line_info[i][j].line_state = info.lineInfo[i][j].state;
			line_info[i][j].line_maxlength = info.lineInfo[i][j].maxlength;
			line_info[i][j].line_resource = info.lineInfo[i][j].resource;
			line_info[i][j].line_frontResource = info.lineInfo[i][j].frontResource;
			line_info[i][j].line_backResource = info.lineInfo[i][j].backResource;
		}
	}
}

//�ж���������״̬
void towerStateJudge(Info& info){
	for (int i = 0; i < my_tower_TotalNumber; i++){
		//����
		int if_attacked = 0;//��ʼ��
		for (int x = 0; x < 13; x++){
			for (int y = 0; y < 13; y++){
				if (line_info[x][y].line_targetTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
					for (int m = 0; m < 3; m++){
						for (int n = 0; n < enemy_info[m].enemy_tower_TotalNum; n++){
							if (line_info[x][y].line_sourceTower == enemy_info[m].enemy_tower_info[n].enemyTower_id){
								if_attacked = 1;//�������
								break;
							}
						}
						if (if_attacked == 1){
							break;
						}
					}
				}
				if (if_attacked == 1){
					break;
				}
			}
			if (if_attacked == 1){
				break;
			}
		}
		if (if_attacked == 1){
			my_tower_info[i].myTower_state = 0;//״̬Ϊdefencing
			continue;//��������
		}
		//������֧Ԯ
		int if_attacking = -1;
		for (int x = 0; x < 13; x++){
			for (int y = 0; y < 13; y++){
				if (line_info[x][y].line_sourceTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
					for (int m = 0; m < 3; m++){
						for (int n = 0; n < enemy_info[m].enemy_tower_TotalNum; n++){
							if (line_info[x][y].line_targetTower == enemy_info[m].enemy_tower_info[n].enemyTower_id){
								if_attacking = 1;//�������ڹ���״̬
								break;
							}
						}
						if (if_attacking == 1){
							break;
						}
					}
				}
				if (if_attacking == 1){
					break;
				}
			}
			if (if_attacking == 1){
				break;
			}
		}
		if (if_attacking == 1){
			my_tower_info[i].myTower_state = 1;//״̬Ϊattacking
			continue;//û�ез������������ڹ����з���
		}
		//֧Ԯ
		int if_supporting = -1;
		for (int x = 0; x < 13; x++){
			for (int y = 0; y < 13; y++){
				if (line_info[x][y].line_sourceTower == my_tower_info[i].myTower_id && line_info[x][y].line_exist == true){
					for (int j = 0; j < my_tower_TotalNumber; j++){
						if (line_info[x][y].line_targetTower == my_tower_info[j].myTower_id){
							if_supporting = 1;
							break;
						}
					}
				}
			}
			if (if_supporting == 1){
				break;
			}
		}
		if (if_supporting == 1){
			my_tower_info[i].myTower_state = 3;//״̬Ϊsupporting
			continue;
		}
		//�ɳ�
		my_tower_info[i].myTower_state = 2;//״̬Ϊgrowing
	}
}

//���ߵ���غϣ�Դ��id��Ŀ����id��info�������ر��ߵ���Ŀ�����Ļغ���
double LineArriveRound(int id1, int id2, Info &info){
	for (int t = 0; t < 13; t++){
		if (tower_info[t].its_id == id1){
			for (int r = 0; r < 13; r++){
				if (tower_info[r].its_id == id2){
					if (line_info[tower_info[t].its_id][tower_info[r].its_id].line_exist == true){
						//int line_current_resource = line_info[tower_info[t].its_id][tower_info[r].its_id].line_resource;
						if (tower_info[t].its_currentLineNum == 1){
							int arriveRound = (int)(((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) - line_info[tower_info[t].its_id][tower_info[r].its_id].line_resource) / 3);
							return arriveRound;
						}
						if (tower_info[t].its_currentLineNum == 2){
							int arriveRound = (int)(((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) - line_info[tower_info[t].its_id][tower_info[r].its_id].line_resource) / (3 * 0.8));
							return arriveRound;
						}
						if (tower_info[t].its_currentLineNum == 3){
							int arriveRound = (int)(((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) - line_info[tower_info[t].its_id][tower_info[r].its_id].line_resource) / (3 * 0.6));
							return arriveRound;
						}
					}
				}
			}
		}
	}
	return 10000;
}

//���ߵ����ܻغ�����Դ��id��Ŀ����id��info�������شӷ�����������ܻغ���
double LineTotalRound(int id1, int id2, Info& info){
	for (int t = 0; t < 13; t++){
		if (tower_info[t].its_id == id1){
			for (int r = 0; r < 13; r++){
				if (tower_info[r].its_id == id2){
					if (line_info[tower_info[t].its_id][tower_info[r].its_id].line_exist == true){
						//int line_total_resource = line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10;
						if (tower_info[t].its_currentLineNum == 1){
							int arriveRound = (int)((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) / 3);
							return arriveRound;
						}
						if (tower_info[t].its_currentLineNum == 2){
							int arriveRound = (int)((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) / (3 * 0.8));
							return arriveRound;
						}
						if (tower_info[t].its_currentLineNum == 3){
							int arriveRound = (int)((line_info[tower_info[t].its_id][tower_info[r].its_id].line_maxlength / 10) / (3 * 0.6));
							return arriveRound;
						}
					}
				}
			}
		}
	}
	return 10000;
}

//����ģʽ��ʹ�ã��������ʱ������Դ̫�٣��������б��ߣ���id��info��
void ifFallback(int id, Info& info){
	for (int i = 0; i < my_tower_TotalNumber; i++){
		if (my_tower_info[i].myTower_id == id && (my_tower_info[i].myTower_resource < (0.2 * my_tower_info[i].myTower_maxResource))){
			for (int x = 0; x < 13; x++){
				for (int y = 0; y < 13; y++){
					if (line_info[x][y].line_exist == true && line_info[x][y].line_sourceTower == my_tower_info[i].myTower_id){
						double sourceTower_resourceNeed = my_tower_info[i].myTower_maxResource - my_tower_info[i].myTower_resource;
						int devideTroops = (int)sourceTower_resourceNeed;
						info.myCommandList.addCommand(cutLine, x, y, (int)minimum(devideTroops, line_info[x][y].line_resource));
						//my_current_control_number++;
					}
				}
			}
		}
	}
}

//������Сֵ����
double minimum(double x, double y){
	if (x > y){
		return y;
	}
	else{
		return x;
	}
}

//�������ֵ����
double maximum(double x, double y){
	if (x > y){
		return x;
	}
	else{
		return y;
	}
}

//������������
void upgradeLevel(Info& info){
	if (info.playerInfo[my_id].RegenerationSpeedLevel == 0 && my_current_tech >= 8){
		info.myCommandList.addCommand(upgrade, 0);
		//my_current_control_number++;
		my_current_tech -= 2;
	}
	if (info.playerInfo[my_id].RegenerationSpeedLevel == 1 && my_current_tech >= 10){
		info.myCommandList.addCommand(upgrade, 0);
		//my_current_control_number++;
		my_current_tech -= 4;
	}
	if (info.playerInfo[my_id].RegenerationSpeedLevel == 2 && my_current_tech >= 12){
		info.myCommandList.addCommand(upgrade, 0);
		//my_current_control_number++;
		my_current_tech -= 6;
	}
	if (info.playerInfo[my_id].RegenerationSpeedLevel == 3 && my_current_tech >= 14){
		info.myCommandList.addCommand(upgrade, 0);
		//my_current_control_number++;
		my_current_tech -= 8;
	}
	if (info.playerInfo[my_id].RegenerationSpeedLevel == 4 && my_current_tech >= 16){
		info.myCommandList.addCommand(upgrade, 0);
		//my_current_control_number++;
		my_current_tech -= 10;
	}
	if (info.playerInfo[my_id].ExtraControlLevel == 0 && my_current_tech >= 9){
		info.myCommandList.addCommand(upgrade, 2);
		//my_current_control_number++;
		my_current_tech -= 3;
	}
	if (info.playerInfo[my_id].ExtraControlLevel == 1 && my_current_tech >= 12){
		info.myCommandList.addCommand(upgrade, 2);
		//my_current_control_number++;
		my_current_tech -= 5;
	}
	if (info.playerInfo[my_id].ExtraControlLevel == 2 && my_current_tech >= 15){
		info.myCommandList.addCommand(upgrade, 2);
		//my_current_control_number++;
		my_current_tech -= 7;
	}
	if (info.playerInfo[my_id].DefenceLevel == 0 && my_current_tech >= 8){
		info.myCommandList.addCommand(upgrade, 3);
		///my_current_control_number++;
		my_current_tech -= 2;
	}
	if (info.playerInfo[my_id].DefenceLevel == 1 && my_current_tech >= 10){
		info.myCommandList.addCommand(upgrade, 3);
		///my_current_control_number++;
		my_current_tech -= 4;
	}
	if (info.playerInfo[my_id].DefenceLevel == 2 && my_current_tech >= 12){
		info.myCommandList.addCommand(upgrade, 3);
		///my_current_control_number++;
		my_current_tech -= 6;
	}
	if (info.playerInfo[my_id].ExtendingSpeedLevel == 0 && my_current_tech >= 12){
		info.myCommandList.addCommand(upgrade, 1);
		//my_current_control_number++;
		my_current_tech -= 2;
	}
	if (info.playerInfo[my_id].ExtendingSpeedLevel == 1 && my_current_tech >= 14){
		info.myCommandList.addCommand(upgrade, 1);
		//my_current_control_number++;
		my_current_tech -= 4;
	}
	if (info.playerInfo[my_id].ExtendingSpeedLevel == 2 && my_current_tech >= 16){
		info.myCommandList.addCommand(upgrade, 1);
		//my_current_control_number++;
		my_current_tech -= 6;
	}
	if (info.playerInfo[my_id].ExtendingSpeedLevel == 3 && my_current_tech >= 18){
		info.myCommandList.addCommand(upgrade, 1);
		//my_current_control_number++;
		my_current_tech -= 8;
	}
	if (info.playerInfo[my_id].ExtendingSpeedLevel == 4 && my_current_tech >= 20){
		info.myCommandList.addCommand(upgrade, 1);
		//my_current_control_number++;
		my_current_tech -= 10;
	}
}

//�����������յ�Ŀ�����ľ��������������Ŀ�����������������ġ���������������ߡ�������id
int myTowerSort(int id, Info& info){
	double minDistance = 100000.0;
	int targetID = -1;
/*	for (int i = 0; i < 13; i++){
		if (tower_info[i].its_id == id){
			bool targetFound = false;
			for (int j = 0; j < my_tower_TotalNumber; j++){
				if ((my_tower_info[j].myTower_id != my_tower_info[i].myTower_id) && (my_tower_info[j].myTower_state == 2 || my_tower_info[j].myTower_state == 3) && (my_tower_info[j].myTower_currentLineNum < my_tower_info[j].myTower_maxLineNum) && (my_tower_info[j].myTower_resource >= (0.4 * my_tower_info[j].myTower_maxResource))){
					double currentDistance = getDistance(info.towerInfo[tower_info[i].its_id].position, info.towerInfo[my_tower_info[j].myTower_id].position);
					if (currentDistance < minDistance && currentDistance != 0){
						minDistance = currentDistance;
						targetID = my_tower_info[j].myTower_id;
						targetFound = true;
					}
				}
			}
			if (!targetFound){
				for (int j = 0; j < my_tower_TotalNumber; j++){
					if ((my_tower_info[j].myTower_id != my_tower_info[i].myTower_id) && (my_tower_info[j].myTower_state == 1) && (my_tower_info[j].myTower_currentLineNum < my_tower_info[j].myTower_maxLineNum) && (my_tower_info[j].myTower_resource >= (0.6 * my_tower_info[j].myTower_maxResource))){
						double currentDistance = getDistance(info.towerInfo[tower_info[i].its_id].position, info.towerInfo[my_tower_info[j].myTower_id].position);
						if ((currentDistance < minDistance) && (currentDistance != 0)){
							minDistance = currentDistance;
							targetID = my_tower_info[j].myTower_id;
							targetFound = true;
						}
					}
				}
			}
		}
	}*/
	//Debug
	return targetID;
}

//Debug
void Debug(Info&info){
	cout << info.round << '\t';
	for (int i = 0; i < my_tower_TotalNumber; i++){
		cout << my_tower_info[i].myTower_id << "," << my_tower_info[i].myTower_state << '\t';
	}
	cout << endl;
	system("pause");
}