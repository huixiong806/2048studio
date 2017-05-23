/*2048studio
 *programed by orangebird.
 *copyright orangebird 2016,all rights reserved.
*/
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "base2d.h"
#include "player_move.h"
#include "player_create.h"
#include<memory>
NS_2048_BEGIN
class Game2d:public Base2d
{
public:
    Game2d();
	void doMove();
	void doCreate();
	virtual void newGame();
	void setPlayerM(std::shared_ptr<Player_Move> pM);
	void setPlayerC(std::shared_ptr<Player_Create> pC);
protected:
	std::shared_ptr<Player_Move> playerM;
	std::shared_ptr<Player_Create> playerC;
};
NS_2048_END
#endif
