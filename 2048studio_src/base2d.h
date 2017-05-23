/*2048studio
 *programed by orangebird.
 *copyright orangebird 2016,all rights reserved.
*/
#ifndef BASE2D_H
#define BASE2D_H
#include "base.h"
#include<vector>
NS_2048_BEGIN
class Base2d
{
public:
    Base2d();
    Base2d(int row_,int col_);
    virtual ~Base2d(){}
    int getRow();
    int getCol();
    void setRow(int row_);
    void setCol(int col_);
    //range from 0 to row/col - 1
    void setTile(int row_,int col_,int value);
    //90% 2,10% 4
    virtual bool createTile();
    int getTile(int row_,int col_);
    //up=0,down=1,left=2,right=3
    virtual bool moveTile(int dir);
    virtual bool moveUp();
    virtual bool moveDown();
    virtual bool moveLeft();
    virtual bool moveRight();
    void setScore(int score_);
    int getScore();
    virtual bool win();
    virtual bool over();
    void setWinTile(int winTile_);
    int getWinTile();
    virtual void newGame();
protected:
	int row,col;
	int score;
	int winTile;
    std::vector<std::vector<int>>tile;
};
NS_2048_END
#endif
