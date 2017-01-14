/*2048studio
*copyright orangebird 2016~2017.
**/
#ifndef HUMAN_CREATE_H
#define HUMAN_CREATE_H
#include "base.h"
#include "player_create.h"
#include<vector>
#include<iostream>
NS_2048_BEGIN
class HumanCreate:public Player_Create
{
public:
	//<posx,posy>,value
	virtual std::pair<std::pair<int, int>, int> analyze(std::vector<std::vector<int>>& board);
};
std::pair<std::pair<int, int>, int> HumanCreate::analyze(std::vector<std::vector<int>>& board)
{
	std::cout << "please input 3 numbers,separated by spaces" << std::endl;
	std::cout << "the row,cow and the tile you want to put(only 2,4 allowed)" << std::endl;
	int x, y, v;
	do{
		std::cin >> x >> y >> v;
	} while (board[x][y] != 0||(v!=2&&v!=4));
	std::cout << "succesfully create the tile!" << std::endl;
	return std::make_pair(std::make_pair(x,y),v);
}
NS_2048_END
#endif