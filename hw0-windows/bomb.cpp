#include <iostream>
#include "bomb.h"
using namespace std;
void bomb::setX(int temp)
{
	pos_x = temp;
}
void bomb::setY(int temp)
{
	pos_y = temp;
}
int bomb::getX()
{
	return pos_x;
}
int bomb::getY()
{
	return pos_y;
}
void bomb::explosion()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			exp[i][j] = 5;
		}
	}
}
void bomb::setexplosion(int x,int y, int value)
{
	exp[x][y] = value;
}
int bomb::getexplosion(int x, int y)
{
	return exp[x][y];
}
void bomb::time(int var)
{
	t += var;
}
int bomb::gettime()
{
	return t;
}