/*
* Board.h
*
*  Created on: May 2, 2014
*      Author: Sibt ul Hussain
*/
#ifndef _BOARD_H_
#define _BOARD_H_

//#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "bomb.h"
#include "ghost.h"
using namespace std;
class Board {
private:

	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	pacman obj;
	int food[13][17];
	int score = 0;
public:
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);
	pacman getpacmanobj()
	{
		return obj;
	}
	ghost GHOST;
	void killpacman();
	void killbomberboy();
	void killbomberboy2();
	//void killpacbyghost();
	bomb drop;
	void setscore(int);
	int getscore();
	void setting();
	~Board(void);
	void InitalizeBoard(int, int);
	//draw the board
	void Draw();

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitBombermanPosition(int &x, int &y) {
		x = xcellsize + xcellsize / 2;
		y = ycellsize + ycellsize / 2;
	}

	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	//	int GetMidx
	void makeboard();
	int accessboard(int, int);
	void MOVERIGHT();
	void MOVELEFT();
	void MOVEUP();
	void MOVEDOWN();
	void foodfunction();
	int get_food(int, int);
	void set_food(int , int , int );
	void setboard(int, int,int);
	static int Getb(int, int);
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
