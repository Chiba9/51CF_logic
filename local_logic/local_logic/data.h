#ifndef _DATA_H
#define _DATA_H
/*  
**  Data�ṹ��
**  �������ݵĴ洢�͹���    
**  ���ⲿ�洢�����ֻ��洢 ID �� Data �е���
*/
#include<vector>
#include<map>
#include "student.h"
#include "tentacle.h"
#include "map.h"
#include "player.h"
using std::map;
namespace DATA {
	struct Data
	{
		map<TStudentID, Student>  students;
		map<TTentacleID, Tentacle> tentacles;
		map<TCamp, Player>   players;
		Map              gameMap;
	};
}

#endif // !_DATA_H