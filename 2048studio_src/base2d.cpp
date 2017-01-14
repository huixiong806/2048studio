#include"base2d.h"
#include<iostream>
#include<cstdlib>
NS_2048_BEGIN
Base2d::Base2d()
{
    row=col=4;
    tile.resize(row);
    for(auto &i:tile)
        i.resize(col);
    winTile=2048;
}
Base2d::Base2d(int row_,int col_)
{
    row=row_;
    col=col_;
    tile.resize(row);
    for(auto &i:tile)
        i.resize(col);
    winTile = 2048;
}
int Base2d::getRow()
{
    return row;
}
int Base2d::getCol()
{
    return col;
}
void Base2d::setRow(int row_)
{
    row=row_;
    tile.resize(row);
}
void Base2d::setCol(int col_)
{
    col=col_;
    for(auto i:tile)
        i.resize(col);
}
void Base2d::setTile(int row_,int col_,int value)
{
    tile[row_][col_]=value;
}
//90% 2,10% 4
bool Base2d::createTile()
{
    std::vector<std::pair<int,int>> emptyPool;
    for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
            if(!tile[i][j])
                emptyPool.push_back(std::make_pair(i,j));
    if(emptyPool.empty())return false;
    int randNum=rand()%emptyPool.size();
    tile[emptyPool[randNum].first][emptyPool[randNum].second]=(rand()%10) ? 2 : 4;
    return true;
}
int Base2d::getTile(int row_,int col_)
{
    return tile[row_][col_];
}
//up=0,down=1,left=2,right=3
bool Base2d::moveTile(int dir)
{
    switch(dir)
    {
    case 0:
        return moveUp();
        break;
    case 1:
        return moveDown();
        break;
    case 2:
        return moveLeft();
        break;
    case 3:
        return moveRight();
        break;
    default:
        return false;
        break;
    }
}
bool Base2d::moveUp()
{
    bool flag = false;
    int i, j, k;
    std::vector<int>temp(row);
    for (j=0;j<col;++j)
    {
        k = 0;
        for(auto &t:temp)
            t=0;
        for (i=0;i<row;++i)
        {
            if (!tile[i][j])
                continue;
            if (tile[i][j]==temp[k])
            {
                temp[k] += tile[i][j];
                score += temp[k++];
                continue;
            }
            if (temp[k])++k;
            temp[k] = tile[i][j];
        }
        for (i=0;i<row;++i)
            if (tile[i][j]!=temp[i])
            {
                tile[i][j]= temp[i];
                flag = true;
            }
    }
    return flag;
}
bool Base2d::moveDown()
{
    bool flag = false;
    int i, j, k;
    std::vector<int>temp(row);
    for (j=0;j<col;++j)
    {
        k = row-1;
        for(auto &t:temp)
            t=0;
        for (i=row-1;i>=0;--i)
        {
            if (!tile[i][j])
                continue;
            if (tile[i][j]==temp[k])
            {
                temp[k] += tile[i][j];
                score += temp[k--];
                continue;
            }
            if (temp[k])--k;
            temp[k] = tile[i][j];
        }
        for (i=0;i<row;++i)
            if (tile[i][j]!=temp[i])
            {
                tile[i][j]= temp[i];
                flag = true;
            }
    }
    return flag;
}
bool Base2d::moveLeft()
{
    bool flag = false;
    int i, j, k;
    std::vector<int>temp(col);
    for (i=0;i<row;++i)
    {
        k = 0;
        for(auto &t:temp)
            t=0;
        for (j=0;j<col;++j)
        {
            if (!tile[i][j])
                continue;
            if (tile[i][j]==temp[k])
            {
                temp[k] += tile[i][j];
                score += temp[k++];
                continue;
            }
            if (temp[k])++k;
            temp[k] = tile[i][j];
        }
        for (j=0;j<col;++j)
            if (tile[i][j]!=temp[j])
            {
                tile[i][j]= temp[j];
                flag = true;
            }
    }
    return flag;
}
bool Base2d::moveRight()
{
    bool flag = false;
    int i, j, k;
    std::vector<int>temp(col);
    for (i=0;i<row;++i)
    {
        k = col-1;
        for(auto &t:temp)
            t=0;
        for (j=col-1;j>=0;--j)
        {
            if (!tile[i][j])
                continue;
            if (tile[i][j]==temp[k])
            {
                temp[k] += tile[i][j];
                score += temp[k--];
                continue;
            }
            if (temp[k])--k;
            temp[k] = tile[i][j];
        }
        for (j=0;j<col;++j)
            if (tile[i][j]!=temp[j])
            {
                tile[i][j]= temp[j];
                flag = true;
            }
    }
    return flag;
}
void Base2d::setScore(int score_)
{
    score=score_;
}
int Base2d::getScore()
{
    return score;
}
bool Base2d::win()
{
    for(auto i:tile)
        for(auto j:i)
            if(j>=winTile)
                return true;
    return false;
}
bool Base2d::over()
{
    for(auto i:tile)
        for(auto j:i)
            if(!j)return false;
    for(int i=0;i<row;++i)
        for(int j=1;j<col;++j)
            if(tile[i][j]==tile[i][j-1])
                return false;
    for(int j=0;j<col;++j)
        for(int i=1;i<row;++i)
            if(tile[i][j]==tile[i-1][j])
                return false;
    return true;
}
void Base2d::setWinTile(int winTile_)
{
    winTile=winTile_;
}
int Base2d::getWinTile()
{
    return winTile;
}
void Base2d::newGame()
{
    for(auto &i:tile)
        for(auto &j:i)
            j=0;
    score=0;
    createTile();
    createTile();
}
NS_2048_END
