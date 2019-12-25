/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
/*
* Board.cpp
*
*  Created on: May 2, 2014
*      Author: Sibt ul Hussain
*/

#include "Board.h"
#include <cstdio>
const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };


#ifdef WITH_TEXTURES
const int nbricks = 3;
GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = { "solid.png", "brick.png", "brick-green.png" };
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
* files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
			GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
	float fheight)
	/*Draws a specfic brick at given position coordinate
	* sx = position of x-axis from left-bottom
	* sy = position of y-axis from left-bottom
	* cwidth= width of displayed brick in pixels
	* cheight= height of displayed bricki pixels.
	* */
{

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
	//	glTranslatef(0, 0, 0);
	//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
				(GetRandInRange(0, 10)) < 8 ? NILL :
				(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}
}
//Constructor
Board::Board(int xsize, int ysize) {
	obj;
	drop;
	GHOST;
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	//set up board
	drop.explosion();
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
			case G_BRICK:
			case R_BRICK:
				float fwidth = (float)(xcellsize) / width * 2, fheight =
					(float)ycellsize / height * 2;
				float fx = (float)(x - 10) / width * 2 - 1, fy = (float)y
					/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				fheight);*/
				Drawbrick((BoardParts)board_array[i][j], (float)x / width - 1, (float)y / height - 1, fwidth,
					fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) 
			{
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
					colors[BLUE]);
				//DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
					colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				break;
			}
		}
	}
#endif

	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

int Board::accessboard(int i, int j)
{
	return board_array[i][j];
}
void Board::MOVERIGHT()
{
	obj.moveright();
}
void Board::MOVELEFT()
{
	obj.moveleft();
}
void Board::MOVEUP()
{
	obj.moveup();
}
void Board::MOVEDOWN()
{
	obj.movedown();
}
void Board::foodfunction()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (board_array[i][j] == 0)
				food[i][j] = 1;
			else
				food[i][j] = 0;
			//cout << food[i][j] << " ";
		}
		//cout << endl;
	}
}

int Board::get_food(int x, int y)
{
	return food[x][y];
}


void Board::set_food(int value , int row , int col )
{
	food[row][col] = value;
}
void Board::setting()
{
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 17; ++j)
		{
			drop.setexplosion(i, j, board_array[i][j]);
			cout << drop.getexplosion(i, j)<<" ";
		}
		cout << endl;
	}
}
void Board::setboard(int row, int col, int val)
{
	board_array[row][col] = val;
}
int Board::Getb(int i, int j)
{
	return board_array[i][j];
}
void Board::setscore(int s)
{
	score += s;
}
int Board::getscore()
{
	return score;
}
void Board::killpacman()
{
	if ((drop.getX() / 60 == obj.getx() / 60) && (drop.getY() / 60 == obj.gety()/60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
	else if ((((drop.getX() / 60) + 1) == obj.getx() / 60) && (drop.getY() / 60 == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
	else if ((((drop.getX() / 60) - 1) == obj.getx() / 60) && (drop.getY() / 60 == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
	else if (((drop.getX() / 60) == obj.getx() / 60) && (((drop.getY() / 60) + 1) == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
	else if (((drop.getX() / 60) == obj.getx() / 60) && ((drop.getY() / 60) - 1 == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
}
void Board::killbomberboy()
{
	if ((drop.getX() / 60 == GHOST.getgx() / 60) && (drop.getY() / 60 == GHOST.getgy() / 60))
	{
		GHOST.setgx(-1);
		GHOST.setgy(-1);
		setscore(200);
	}
	else if ((((drop.getX() / 60) + 1) == GHOST.getgx() / 60) && (drop.getY() / 60 == GHOST.getgy() / 60))
	{
		GHOST.setgx(-1);
		GHOST.setgy(-1);
		setscore(200);
	}
	else if ((((drop.getX() / 60) - 1) == GHOST.getgx() / 60) && (drop.getY() / 60 == GHOST.getgy() / 60))
	{
		GHOST.setgx(-1);
		GHOST.setgy(-1);
		setscore(200);
	}
	else if (((drop.getX() / 60) == GHOST.getgx() / 60) && (((drop.getY() / 60) + 1) == GHOST.getgy() / 60))
	{
		GHOST.setgx(-1);
		GHOST.setgy(-1);
		setscore(200);
	}
	else if (((drop.getX() / 60) == GHOST.getgx() / 60) && ((drop.getY() / 60) - 1 == GHOST.getgy() / 60))
	{
		GHOST.setgx(-1);
		GHOST.setgy(-1);
		setscore(200);
	}
}
void Board::killbomberboy2()
{
	if ((drop.getX() / 60 == GHOST.getgx1() / 60) && (drop.getY() / 60 == GHOST.getgy1() / 60))
	{
		GHOST.setgx1(-1);
		GHOST.setgy1(-1);
		setscore(200);
	}
	else if ((((drop.getX() / 60) + 1) == GHOST.getgx1() / 60) && (drop.getY() / 60 == GHOST.getgy1() / 60))
	{
		GHOST.setgx1(-1);
		GHOST.setgy1(-1);
		setscore(200);
	}
	else if ((((drop.getX() / 60) - 1) == GHOST.getgx1() / 60) && (drop.getY() / 60 == GHOST.getgy1() / 60))
	{
		GHOST.setgx1(-1);
		GHOST.setgy1(-1);
		setscore(200);
	}
	else if (((drop.getX() / 60) == GHOST.getgx1() / 60) && (((drop.getY() / 60) + 1) == GHOST.getgy1() / 60))
	{
		GHOST.setgx1(-1);
		GHOST.setgy1(-1);
		setscore(200);
	}
	else if (((drop.getX() / 60) == GHOST.getgx1() / 60) && ((drop.getY() / 60) - 1 == GHOST.getgy1() / 60))
	{
		GHOST.setgx1(-1);
		GHOST.setgy1(-1);
		setscore(200);
	}
}
/*void Board::killpacbyghost()
{
	if ((GHOST.getgx() / 60 == obj.getx() / 60) && (GHOST.getgy() / 60 == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
	if ((GHOST.getgx1() / 60 == obj.getx() / 60) && (GHOST.getgy1() / 60 == obj.gety() / 60))
	{
		obj.setx(90);
		obj.sety(90);
		obj.setlife(1);
	}
}*/
