#include <iostream>
#include <vector>

class pacman
{
protected:
	int xpos;
	int ypos;
	int current_score;
	int current_lives;
	int hp;
public:
	pacman(int num1 =90, int num2=90)
	{
		xpos = num1;
		ypos = num2;
		current_lives = 3;
	}
	void setx(int);
	void sety(int);
	int getx();
	int gety();
	void moveleft();
	void moveright();
	void moveup();
	void movedown();
	bool alive();
	int life();
	void  setlife(int);
};