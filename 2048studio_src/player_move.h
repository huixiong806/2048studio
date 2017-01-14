/*2048studio
*copyright orangebird 2016~2017.
**/
#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H
#include "base.h"
#include "player.hpp"
#include<vector>
NS_2048_BEGIN
class Player_Move: public Player
{
public:
	//up 0,down 1,left 2,right 3
	virtual int analyze(std::vector<std::vector<int>>& board) = 0;
};
NS_2048_END
#endif
#pragma once
