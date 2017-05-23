/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef MAX_MIN_H_MOVE_H
#define MAX_MIN_H_MOVE_H
#include "base2d.h"
#include "player_move.h"
#include<vector>
#include<iostream>
#include<algorithm>
NS_2048_BEGIN
typedef unsigned long long ull;
class MaxMinHighMove :public Player_Move, Base2d
{
public:
	//<posx,posy>,value
	virtual int analyze(std::vector<std::vector<int>>& board);
private:
	int maxdeep;
	int choice;
	float evaluation();
	const int weight[4][4] = 
	{ 
		{ 16,15,14,13 },
		{ 12,11,10,9 },
		{ 5,6, 7, 8 },
		{ 2, 2, 2, 2 } 
	};
	//return value is the best choice and score
	float MaxMin_move(int deep, float alpha, float beta);
	float MaxMin_create(int deep, float alpha, float beta);
};
float MaxMinHighMove::evaluation()
{
	float res = 0;
	for (int i = 0; i <= 3; ++i)
		for (int j = 0; j <= 3; ++j)
			res += weight[i][j] * tile[i][j];
	return res;
}
int MaxMinHighMove::analyze(std::vector<std::vector<int>>& board)
{
	maxdeep = 8;
	row = col = 4;
	tile = board;
	std::vector<int> moveablePool;
	getMoveablePool(tile, moveablePool);
	MaxMin_move(0, -0xffffff, 0xffffff);
	return choice;
}
float MaxMinHighMove::MaxMin_move(int deep,float alpha,float beta)
{
	using std::max;
	if (deep == maxdeep)
		return evaluation();
	std::vector<int> moveablePool;
	getMoveablePool(tile, moveablePool);
	std::vector<std::vector<int>> temp = tile;
	for (int i : moveablePool)
	{
		moveTile(i);
		float score = -MaxMin_create(deep + 1, -beta, -alpha);
		tile = temp;
		//剪枝
		if (alpha >= beta)
			return beta;
		if (alpha < score||score==-0xffffff)
		{
			alpha = score;
			if(!deep)choice = i;
		}
	}
	return alpha;
}
float MaxMinHighMove::MaxMin_create(int deep, float alpha, float beta)
{
	//对于min节点，所有值取相反数后再求最大值，相当于求最小值
	using std::max;
	if (deep == maxdeep)
		return -evaluation();
	for (int i = 0; i <= 3; ++i)
		for (int j = 0; j <= 3; ++j)
			if (!tile[i][j])
				for (int k = 2; k <= 4; k += 2)
				{
					setTile(i, j, k);
					float score = -MaxMin_move(deep + 1, -beta, -alpha);
					setTile(i, j, 0);
					//剪枝
					if (alpha >= beta)
						return beta;
					if (alpha < score)
						alpha = score;
				}
	return alpha;
}
NS_2048_END
#endif
