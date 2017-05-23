/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef HUMAN_MOVE_H
#define HUMAN_MOVE_H
#include "base.h"
#include "player_move.h"
#include<vector>
#include<iostream>
#include<map>
NS_2048_BEGIN
class HumanMove :public Player_Move
{
public:
	//<posx,posy>,value
	virtual int analyze(std::vector<std::vector<int>>& board);
};
int HumanMove::analyze(std::vector<std::vector<int>>& board)
{
	std::cout << "use your array keys to move the tile." << std::endl;
	std::vector<int>moveablePool;
	getMoveablePool(board, moveablePool);
	char c;
	std::map<char,int> mp;
	mp[72] = 0;
	mp[80] = 1;
	mp[75] = 2;
	mp[77] = 3;
	while (c = _getch())
	{
		if (mp.find(c) == mp.end())continue;
		bool flag = false;
		for (int i : moveablePool)
			if (i == mp[c])flag = true;
		if (flag)break;
	}
	return mp[c];
}
NS_2048_END
#endif