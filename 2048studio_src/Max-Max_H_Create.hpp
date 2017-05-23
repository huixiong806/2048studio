/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef MAX_MAX_HIGH_CREATE_H
#define MAX_MAX_HIGH_CREATE_H
#include "base2d.h"
#include "player_create.h"
#include<vector>
#include<iostream>
#include<algorithm>
NS_2048_BEGIN
typedef unsigned long long ull;
class MaxMaxHighCreate :public Player_Create,Base2d
{
public:
	//<posx,posy>,value
	virtual std::pair<std::pair<int, int>, int> analyze(std::vector<std::vector<int>>& board);
private:
	int maxDepth;
	std::pair<std::pair<int, int>, int> choice;
	double evaluation();
	const double weight[4][4] ={{16,15,14,13},{9 ,10,11,12},{8 ,7 ,6 ,5 },{1 ,2 ,3 ,4 }};
	//return value is the best choice and score
	double MaxMax_move(int depth);
	double MaxMax_create(int depth);
};
double MaxMaxHighCreate::evaluation()
{
	using namespace std;
	double val[8] = {0.0};
		for (int i = 0; i <= 3; ++i)
			for (int j = 0; j <= 3; ++j)
			{
				val[0] += weight[i][j] * tile[i][j];
				val[1] += weight[i][3 - j] * tile[i][j];
				val[2] += weight[3 - i][j] * tile[i][j];
				val[3] += weight[3 - i][3 - j] * tile[i][j];
				val[4] += weight[j][i] * tile[i][j];
				val[5] += weight[j][3 - i] * tile[i][j];
				val[6] += weight[3 - j][i] * tile[i][j];
				val[7] += weight[3 - j][3 - i] * tile[i][j];
			}
	double result = -0xffffff;
	for (int i = 0; i < 8; ++i)
		result = max(result, val[i]);
	return result;
}
std::pair<std::pair<int, int>, int> MaxMaxHighCreate::analyze(std::vector<std::vector<int>>& board)
{
	maxDepth = 6;
	row = col = 4;
	tile = board;
	MaxMax_create(0);
	//std::cout << "evaluation score:" << MaxAvg_create(0) << std::endl;
	return choice;
}
double MaxMaxHighCreate::MaxMax_move(int depth)
{
	using namespace std;
	if (depth == maxDepth)
		return evaluation();
	std::vector<int> moveablePool;
	getMoveablePool(tile,moveablePool);
	if (moveablePool.empty())return -1;
	std::vector<std::vector<int>> temp = tile;
	double score = 0;
	for (int i : moveablePool)
	{
		moveTile(i);
		score=max(score, MaxMax_create(depth + 1));
		tile = temp;
	}
	return score;
}
double MaxMaxHighCreate::MaxMax_create(int depth)
{
	if (depth == maxDepth)
		return evaluation();
	double maxScore = -1;
	for (int i = 0; i <= 3;++i)
		for (int j = 0; j <= 3; ++j)
			if (!tile[i][j])
			{
				setTile(i, j, 4);
				double score = MaxMax_move(depth + 1);
				if (score >= maxScore)
				{
					maxScore = score;
					if (!depth)choice = std::make_pair(std::make_pair(i, j), 4);
				}
				setTile(i, j, 0);
			}	
	return maxScore;
}
NS_2048_END
#endif
