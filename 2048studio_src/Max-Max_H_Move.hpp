/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef MAX_MAX_HIGH_MOVE_H
#define MAX_MAX_HIGH_MOVE_H
#include "base2d.h"
#include "player_move.h"
#include<vector>
#include<iostream>
#include<algorithm>
NS_2048_BEGIN
typedef unsigned long long ull;
class MaxMaxHighMove :public Player_Move,Base2d
{
public:
	//<posx,posy>,value
	virtual int analyze(std::vector<std::vector<int>>& board);
private:
	int maxDepth;
	int choice;
	double evaluation();
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
	double MaxMax_move(int depth);
	double MaxMax_create(int depth);
};
double MaxMaxHighMove::evaluation()
{
	using namespace std;
	double val[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
	double result = -0xffffff;
	for (int i = 0; i < 24; ++i)
		result = max(result, val[i]);
	return result;
}
int MaxMaxHighMove::analyze(std::vector<std::vector<int>>& board)
{
	maxDepth = 6;
	row = col = 4;
	tile = board;
	MaxMax_move(0);
	return choice;
}
double MaxMaxHighMove::MaxMax_move(int depth)
{
	using namespace std;
	if (depth == maxDepth)
		return evaluation();
	vector<int> moveablePool;
	getMoveablePool(tile,moveablePool);
	std::vector<std::vector<int>> temp = tile;
	double maxScore = -1;
	for (int i : moveablePool)
	{
		moveTile(i);
		float score = MaxMax_create(depth + 1);
		if (score >= maxScore)
		{
			maxScore = score;
			if(!depth)choice = i;
		}
		tile = temp;
	}
	return maxScore;
}
double MaxMaxHighMove::MaxMax_create(int depth)
{
	using namespace std;
	if (depth == maxDepth)
		return evaluation();
	double score = 0;
	for (int i = 0; i <= 3;++i)
		for (int j = 0; j <= 3; ++j)
			if (!tile[i][j])
			{
				for (int k = 2; k <= 4; k+=2)
				{
					setTile(i, j, k);
					score = max(score, MaxMax_move(depth + 1));
					setTile(i, j, 0);
				}
			}
	return score;
}
NS_2048_END
#endif
