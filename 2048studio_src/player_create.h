/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef PLAYER_CREATE_H
#define PLAYER_CREATE_H
#include "base.h"
#include "player.hpp"
#include<vector>
NS_2048_BEGIN
class Player_Create:public Player
{
public:
	//<posx,posy>,value
	virtual std::pair<std::pair<int,int>,int> analyze(std::vector<std::vector<int>>& board) = 0;
};
NS_2048_END
#endif
#pragma once
