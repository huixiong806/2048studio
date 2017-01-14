/*2048studio
*copyright orangebird 2016~2017.
**/
#ifndef MAX_AVG_MOVE_H
#define MAX_AVG_MOVE_H
#include "base2d.h"
#include "player_move.h"
#include <vector>
#include <iostream>
#include <algorithm>
NS_2048_BEGIN
typedef unsigned long long ull;
class MaxAvgMove :public Player_Move,Base2d
{
public:
	//<posx,posy>,value
	virtual int analyze(std::vector<std::vector<int>>& board);
private:
	int maxDepth;
	int choice;
	float evaluation();
	const int weight[3][4][4] =
	{
		{
			{16,15,14,4},
			{13,12,11,3},
			{10,9 ,8 ,2},
			{7 ,6 ,5 ,1}
		},{
			{16,15,14,13},
			{9 ,10,11,12},
			{8 ,7 ,6 ,5 },
			{1 ,2 ,3 ,4 }
		},{
			{16,15,12,4 },
			{14,13,11,3 },
			{10,9 ,8 ,2 },
			{7 ,6 ,5 ,1 }
		}
	};
	//return value is the best choice and score
	float MaxAvg_move(int depth);
	float MaxAvg_create(int depth);
};
float MaxAvgMove::evaluation()
{
	float val[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for (int k = 0; k <= 2;++k)
		for (int i = 0; i <= 3; ++i)
			for (int j = 0; j <= 3; ++j)
			{
				int delta = k * 8;
				val[delta] += weight[k][i][j] * tile[i][j];
				val[delta+1] += weight[k][i][3 - j] * tile[i][j];
				val[delta+2] += weight[k][3 - i][j] * tile[i][j];
				val[delta+3] += weight[k][3 - i][3 - j] * tile[i][j];
				val[delta+4] += weight[k][j][i] * tile[i][j];
				val[delta+5] += weight[k][j][3 - i] * tile[i][j];
				val[delta+6] += weight[k][3 - j][i] * tile[i][j];
				val[delta+7] += weight[k][3 - j][3 - i] * tile[i][j];
			}
	float result = -0xffffff;
	for (int i = 0; i < 24; ++i)
		result = std::max(result, val[i]);
	return result;
}
int MaxAvgMove::analyze(std::vector<std::vector<int>>& board)
{
	maxDepth = 6;
	row = col = 4;
	tile = board;
	MaxAvg_move(0);
	return choice;
}
float MaxAvgMove::MaxAvg_move(int depth)
{
	using namespace std;
	if (depth == maxDepth)
		return evaluation();
	vector<int> moveablePool;
	getMoveablePool(tile,moveablePool);
	std::vector<std::vector<int>> temp = tile;
	float maxScore = -1;
	for (int i : moveablePool)
	{
		moveTile(i);
		float score = MaxAvg_create(depth + 1);
		if (score >= maxScore)
		{
			maxScore = score;
			if(!depth)choice = i;
		}
		tile = temp;
	}
	return maxScore;
}
float MaxAvgMove::MaxAvg_create(int depth)
{
	if (depth == maxDepth)
		return evaluation();
	float score = 0;
	char emptyCount = 0;
	for (int i = 0; i <= 3;++i)
		for (int j = 0; j <= 3; ++j)
			if (!tile[i][j])
			{
				emptyCount++;
				setTile(i, j, 2);
				score += MaxAvg_move(depth + 1)*0.9;
				setTile(i, j, 4);
				score += MaxAvg_move(depth + 1)*0.1;
				setTile(i, j, 0);
			}
	return score/(float)emptyCount;
}
NS_2048_END
#endif
