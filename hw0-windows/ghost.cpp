#include <iostream>
#include <string>
#include <deque>
#include "ghost.h"

using namespace std;

void ghost::setgx(int gx)
{
	xpos = gx;
}
void ghost::setgy(int gy)
{
	ypos = gy;
}
int ghost::getgx()
{
	return xpos;
}
int ghost::getgy()
{
	return ypos;
}
void ghost::setgx1(int gx1)
{
	xpos1 = gx1;
}
void ghost::setgy1(int gy1)
{
	ypos1 = gy1;
}
int ghost::getgx1()
{
	return xpos1;
}
int ghost::getgy1()
{
	return ypos1;
}