#include"game2d.h"
#include<iostream>
#include<cstdlib>
NS_2048_BEGIN
Game2d::Game2d()
{
	row = col = 4;
	tile.resize(row);
	for (auto &i : tile)
		i.resize(col);
}
void Game2d::newGame()
{
	for (auto &i : tile)
		for (auto &j : i)
			j = 0;
	score = 0;
	doCreate();
	doCreate();
}
void Game2d::doMove()
{
	moveTile(playerM->analyze(tile));
}
void Game2d::doCreate()
{
	std::pair<std::pair<int, int>, int> result = playerC->analyze(tile);
	setTile(result.first.first,result.first.second,result.second);
}
void Game2d::setPlayerM(std::shared_ptr<Player_Move> pM)
{
	playerM = pM;
}
void Game2d::setPlayerC(std::shared_ptr<Player_Create> pC)
{
	playerC = pC;
}
NS_2048_END
