#include <iostream>
#include "pacman.h"

using namespace std;

void pacman::setx(int x11)
{
	xpos = x11;
}
void pacman::sety(int y11)
{
	ypos = y11;
}
int pacman::getx()
{
	return xpos;
}
int pacman::gety()
{
	return ypos;
}
void pacman::moveleft()
{
	xpos -= 60;
}
void pacman::moveright()
{
	xpos += 60;
}
void pacman::moveup()
{
	ypos += 60;
}
void pacman::movedown()
{
	ypos -= 60;
}
bool pacman::alive()
{
	if (current_lives > 0)
		return true;
	else
		return false;
}
int pacman::life()
{
	return current_lives;
}
void pacman::setlife(int l)
{
	current_lives -= l;
}