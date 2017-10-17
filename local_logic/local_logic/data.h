#ifndef _DATA_H
#define _DATA_H
/*  
**  Data�ṹ��
**  �������ݵĴ洢�͹���    
**  ���ⲿ�洢�����ֻ��洢 ID �� Data �е���
*/
#include<vector>
#include "student.h"
#include "tentacle.h"
#include "map.h"
#include "player.h"
using std::vector;
namespace DATA {
	struct Data
	{
		vector<Student>  students;
		vector<Tentacle> tentacles;
		vector<Player>   players;
		Map              gameMap;
	};
}

#endif // !_DATA_H