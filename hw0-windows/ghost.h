#include <iostream>
#include <string>
#include <deque>

using namespace std;

class ghost
{
protected:
	int **array1;
	int **array2;
	deque <int> dequex;
	deque <int> dequey;
	int xpos, ypos, xpos1, ypos1;
public:
	ghost(int num1 = 240, int num2 = 300,int num3=540,int num4=660)
	{
		xpos = num1;
		ypos = num2;
		xpos1 = num3;
		ypos1 = num4;
	}
	int getgx();
	int getgy();
	void setgx(int);
	void setgy(int);
	int getgx1();
	int getgy1();
	void setgx1(int);
	void setgy1(int);
};