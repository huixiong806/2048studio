/*2048studio
*copyright orangebird 2016~2017.
**/
#ifndef RAMDOMLY_CREATE_H
#define RAMDOMLY_CREATE_H
#include "base.h"
#include "player_create.h"
#include<vector>
NS_2048_BEGIN
class RandomlyCreate:public Player_Create
{
public:
	//<posx,posy>,value
	virtual std::pair<std::pair<int, int>, int> analyze(std::vector<std::vector<int>>& board);
};
std::pair<std::pair<int, int>, int> RandomlyCreate::analyze(std::vector<std::vector<int>>& board)
{
	std::vector<std::pair<int, int>> emptyPool;
	getCreateablePool(board, emptyPool);
	int randNum = rand() % emptyPool.size();
	return std::make_pair(std::make_pair(emptyPool[randNum].first, emptyPool[randNum].second), (rand() % 10) ? 2 : 4);
}
NS_2048_END
#endif