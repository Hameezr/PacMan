#include <iostream>
#include <vector>
#include "pacman.h"

class bomb
{
protected:
	int pos_x;
	int pos_y;
	pacman position;
	int exp[13][17];
	int t;
public:
	bomb()
	{
		pos_x = position.getx();
		pos_y = position.gety();
		t = 1;
	}
	bomb(int num1, int num2)
	{
		pos_x = num1;
		pos_y = num2;
	}

	void setX(int);
	void setY(int);
	int getX();
	int getY();
	void explosion();
	void setexplosion(int,int,int);
	int getexplosion(int,int);
	void time(int);
	int gettime();
};