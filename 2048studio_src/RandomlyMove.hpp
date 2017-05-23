/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef RAMDOMLY_MOVE_H
#define RAMDOMLY_MOVE_H
#include "base.h"
#include "player_move.h"
#include<vector>
NS_2048_BEGIN
class RandomlyMove:public Player_Move
{
public:
	//<posx,posy>,value
	virtual int analyze(std::vector<std::vector<int>>& board);
};
int RandomlyMove::analyze(std::vector<std::vector<int>>& board)
{
	std::vector<int>moveablePool;
	getMoveablePool(board, moveablePool);
	return moveablePool[rand() % moveablePool.size()];
}
NS_2048_END
#endif