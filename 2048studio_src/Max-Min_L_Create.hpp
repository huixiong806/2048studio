/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef MAX_MIN_L_CREATE_H
#define MAX_MIN_L_CREATE_H
#include "base2d.h"
#include "player_create.h"
#include<vector>
#include<algorithm>
#include<iostream>
NS_2048_BEGIN
typedef unsigned long long ull;
class MaxMinLowCreate :public Player_Create, Base2d
{
public:
	//<posx,posy>,value
	virtual std::pair<std::pair<int, int>, int> analyze(std::vector<std::vector<int>>& board);
private:
	int maxdeep;
	std::pair<std::pair<int, int>, int> choice;
	float evaluation();
	const float weight[4][4] = 
	{ 
		{ -1.75,-1.5,-1.5,-1.75 },
		{ -1.5,-1.0,-1.0,-1.5 },
		{ -1.5,-1.0,-1.0,-1.5 },
		{ -1.75,-1.5,-1.5,-1.75 } 
	};
	//return value is the best choice and score
	float MaxMin_move(int deep, float alpha, float beta);
	float MaxMin_create(int deep, float alpha, float beta);
};
float MaxMinLowCreate::evaluation()
{
	float res = 0;
	for (int i = 0; i <= 3; ++i)
		for (int j = 0; j <= 3; ++j)
			res += weight[i][j] * (float)tile[i][j];
	//std::cout << res << std::endl;
	return res;
}
std::pair<std::pair<int, int>, int> MaxMinLowCreate::analyze(std::vector<std::vector<int>>& board)
{
	maxdeep = 8;
	row = col = 4;
	tile = board;
	MaxMin_create(0, -0xffffff, 0xffffff);
	return choice;
}
float MaxMinLowCreate::MaxMin_move(int deep, float alpha, float beta)
{
	//对于min节点，所有值取相反数后再求最大值，相当于求最小值
	using std::max;
	if (deep == maxdeep)
		return -evaluation();
	std::vector<int> moveablePool;
	getMoveablePool(tile, moveablePool);
	std::vector<std::vector<int>> temp = tile;
	for (int i : moveablePool)
	{
		moveTile(i);
		float score = -MaxMin_create(deep + 1, -beta, -alpha);
		tile = temp;
		//剪枝
		if (score >= beta)
			return beta;
		if (alpha < score)
			alpha = score;
	}
	return alpha;
}
float MaxMinLowCreate::MaxMin_create(int deep, float alpha, float beta)
{
	using std::max;
	if (deep == maxdeep)
		return evaluation();
	for (int i = 0; i <= 3; ++i)
		for (int j = 0; j <= 3; ++j)
			if (!tile[i][j])
				for (int k = 2; k <= 4; k += 2)
				{
					setTile(i, j, k);
					float score = -MaxMin_move(deep + 1, -beta, -alpha);
					setTile(i, j, 0);
					if (alpha <score)
					{
						alpha = score;
						if(!deep)choice = std::make_pair(std::make_pair(i,j),k);
					}
					//剪枝,这行不要移到上面
					if (score >= beta)return beta;
				}
	return alpha;
}
NS_2048_END
#endif