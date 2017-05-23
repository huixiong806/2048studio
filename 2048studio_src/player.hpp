/*2048studio
*programed by orangebird.
*copyright orangebird 2016,all rights reserved.
*/
#ifndef PLAYER_H
#define PLAYER_H
#include "base.h"
#include<vector>
NS_2048_BEGIN
class Player
{
public:
	//a vector,includes all moveable direction
	virtual void getMoveablePool(std::vector<std::vector<int>> board,std::vector<int>& pool)
	{
		bool flag = false;
		for (int j = 0; j < 4; ++j)
		{
			for (int i = 1; i < 4; ++i)
			{
				if ((!board[i - 1][j] || board[i][j] == board[i - 1][j]) && board[i][j])
				{
					pool.push_back(0);
					flag = true;
					break;
				}
				if (flag)break;
			}
			if (flag)break;
		}
		flag = false;
		for (int j = 0; j < 4; ++j)
		{
			for (int i = 2; i >= 0; --i)
			{
				if ((!board[i + 1][j] || board[i][j] == board[i + 1][j]) && board[i][j])
				{
					pool.push_back(1);
					flag = true;
					break;
				}
				if (flag)break;
			}
			if (flag)break;
		}
		flag = false;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j < 4; ++j)
			{
				if ((!board[i][j - 1] || board[i][j] == board[i][j - 1]) && board[i][j])
				{
					pool.push_back(2);
					flag = true;
					break;
				}
				if (flag)break;
			}
			if (flag)break;
		}
		flag = false;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 2; j >= 0; --j)
			{
				if ((!board[i][j + 1] || board[i][j] == board[i][j + 1]) && board[i][j])
				{
					pool.push_back(3);
					flag = true;
					break;
				}
				if (flag)break;
			}
			if (flag)break;
		}	
	}
	//a vector,includes all createable position
	virtual void getCreateablePool(std::vector<std::vector<int>> board, std::vector<std::pair<int,int>>& pool)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if (!board[i][j])
					pool.push_back(std::make_pair(i, j));
	}
};
NS_2048_END
#endif