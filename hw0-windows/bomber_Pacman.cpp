//============================================================================
// Name        : bubble-shooter.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Bubble Shooting...
//============================================================================
#ifndef BOMBER_PACMAN_CPP
#define BOMBER_PACMAN_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool bombStatus = false;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
*  that is what dimensions (x and y) your game will have
*  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
* */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
	ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
	float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float)gw / ogw, sy = (float)gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
	float radius/*Radius*/,
	const ColorNames &colorname/*Bomberman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
		radius / 10, colors[BLACK]);
}
/*
* Main Canvas drawing function.
* */
Board *b;
void GameDisplay()/**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	//

	b->Draw();
	int x, y;
	b->GetInitPinkyPosition(x, y);
	cout << x << "  y= " << y << endl << flush;
	DrawEnemy(b->GHOST.getgx(), b->GHOST.getgy(), PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	DrawEnemy(b->GHOST.getgx1(), b->GHOST.getgy1(), GREEN, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	b->GetInitBombermanPosition(x, y);
	
	DrawBomberman(b->getpacmanobj().getx(), b->getpacmanobj().gety(), b->GetCellSize() / 2 - 2, GRAY);

	//cout << b->getpacmanobj().getx();
	
//	DrawEnemy(660, 600, GREEN_YELLOW, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	//DrawEnemy(720, 540, BLACK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
//	DrawEnemy(660, 480, BLUE_VIOLET, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());

	/*
	int var1, var2;
	var1 = ((b->getpacmanobj().getx()));
	var2 = (b->getpacmanobj().gety());
	cout << " var1 is " << var1 << "Var 2 is " << var2 << endl;
	*/
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (b->get_food(12-i,j) == 1)
			{
				DrawCircle(((j + 0.4)) * 60, (i + 0.4) * 60, 4, colors[DARK_ORANGE]);
			}
		}
	}
	//cout << "x position is " << b->getpacmanobj().getx() << endl << " y position is " << b->getpacmanobj().gety() << endl;
	//cout << "Bomb pos is x  " << b->drop.getX() << endl << "bomb pos y " << b->drop.getY() << endl;
	b->GetInitTextPosition(x, y);
	cout << endl << "Text Position = " << x << "  y= " << y << endl << flush;
	DrawString(x, y, "SCORE: ", colors[45]);
	DrawString(x + 90 , y, Num2Str(b->getscore()), colors[46]);
	DrawString(x + 160, y, "LIVES: ", colors[76]);
	DrawString(x + 240, y, Num2Str(b->getpacmanobj().life()) , colors[76]);
	DrawString(x + 360, y, "Press S to play, Hope you enjoy. :) ", colors[15]);
	//	glPopMatrix();
	// Put a condition by access board if its not equal to 1 only then break bricks.
	if (bombStatus == true) 
	{
		int var1, var2;
		var1 = (b->drop.getX() / 60);
		var2 = 12-(b->drop.getY() / 60);
		
		DrawCircle(b->drop.getX(), b->drop.getY(), 20, colors[BLACK]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
		DrawCircle(b->drop.getX() - 7, b->drop.getY() + 7, 4, colors[BLUE]);
		DrawCircle(b->drop.getX() + 7, b->drop.getY() + 7, 4, colors[BLUE]);
		
	//	if (bombStatus==false)
			//glutPostRedisplay();
	}
	//cout << "x position of pacman is " << b->drop.getX() << endl << "y position of pacman is:  " << b->drop.getY() << endl;
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */

void NonPrintableKeys(int key, int x, int y)
{
	
	if (key
		== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) 
	{
		// what to do when left key is pressed...
		int var1, var2;
		
		var1 = ((b->getpacmanobj().getx()) / 60) - 1;
		var2 = 12 - (b->getpacmanobj().gety() / 60);
		if (b->accessboard(var2, var1) == 0)
		{
			b->MOVELEFT();
			if (b->get_food(var2, var1) == 1)
				b->setscore(100);
			b->set_food(0, var2, var1);
		//	cout << "Score is " << b->getscore() << endl;
			glutPostRedisplay();
		}


	}
	else if (key
		== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{
		int var1, var2;
		var1 = ((b->getpacmanobj().getx()) / 60) + 1;
		var2 = 12 - (b->getpacmanobj().gety() / 60);
		if (b->accessboard(var2, var1) == 0)
		{
			b->MOVERIGHT();
			if (b->get_food(var2, var1) == 1)
				b->setscore(100);
			b->set_food(0,  var2, var1);
			glutPostRedisplay();
		}
/*		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				cout << b->get_food(i,j) << " ";
			}
			cout << endl;
		}*/
		/*

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				cout << b->accessboard(i,j) << " ";
			}
			cout << endl;
		}
		*/

	}
	else if (key
		== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
		int var1, var2;
		var1 = ((b->getpacmanobj().getx()) / 60);
		var2 = 12 - ((b->getpacmanobj().gety() / 60) + 1);
		if (b->accessboard(var2, var1) == 0)
		{
			b->MOVEUP();
			if (b->get_food(var2, var1) == 1)
				b->setscore(100);
			b->set_food(0,  var2, var1);
			glutPostRedisplay();
		}
	}

	else if (key
		== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) 
	{
		int var1, var2;
		var1 = ((b->getpacmanobj().getx()) / 60);
		var2 = 12 - ((b->getpacmanobj().gety() / 60) - 1);
		if (b->accessboard(var2, var1) == 0)
		{
			//cout << "x down of pacman is " << b->getpacmanobj().getx() << endl << "y down of pacman is:  " << b->getpacmanobj().gety()<< endl;
			b->MOVEDOWN();
			if (b->get_food(var2, var1) == 1)
				b->setscore(100);
			b->set_food(0,  var2, var1);
			glutPostRedisplay();
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	/*
	glutPostRedisplay();
	*/
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'b' || key == 'B') //Key for placing the bomb
	{

		bombStatus = true;
		b->drop.setX(b->getpacmanobj().getx());
		b->drop.setY(b->getpacmanobj().gety());
	}
	if (key == 's' || key == 'S')
	{
		b->foodfunction();
	}
	glutPostRedisplay();
}

/*
* This function is called after every 1000.0/FPS milliseconds
* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
void Timer(int m) 
{
	// implement your functionality here
	if (bombStatus == true)
		b->drop.time(1);

	if (b->drop.gettime() % 2 == 0)
	{
		bombStatus = false;
		int var1, var2;
		var1 = (b->drop.getX() / 60);
		var2 = 12 - (b->drop.getY() / 60);
		b->killpacman();
		b->killbomberboy();
		b->killbomberboy2();
	//	b->killpacbyghost();
		if (b->accessboard(var2, var1 - 1) == 2 || b->accessboard(var2, var1 - 1) == 3)
		{
			if (b->accessboard(var2, var1 - 1) == 3)
			{
				if (b->accessboard(var2, var1 - 1) != 1)
				{
					b->setboard(var2, var1 - 1, 0);
					b->setboard(var2, var1 - 2, 0);
					b->setscore(100);
				}
			}
			else
			{
				b->setboard(var2, var1 - 1, 0);
			}
		}

		if (b->accessboard(var2, var1 + 1) == 2 || b->accessboard(var2, var1 + 1) == 3)
		{
			if (b->accessboard(var2, var1 + 1) == 3)
			{
				if (b->accessboard(var2, var1 + 1) != 1)
				{
					b->setboard(var2, var1 + 1, 0);
					b->setboard(var2, var1 + 2, 0);
					b->setscore(100);
				}
			}
			else
			{
				b->setboard(var2, var1 + 1, 0);
				b->setscore(50);
			}
		}

		if (b->accessboard(var2 + 1, var1) == 2 || b->accessboard(var2 + 1, var1) == 3)
		{
			if (b->accessboard(var2 + 1, var1) == 3)
			{
				if (b->accessboard(var2 + 1, var1) != 1)
				{
					b->setboard(var2 + 1, var1, 0);
					b->setboard(var2 + 2, var1, 0);
					b->setscore(100);
				}
			}
			else
			{
				b->setboard(var2 + 1, var1, 0);
				b->setscore(50);
			}
		}

		if (b->accessboard(var2 - 1, var1) == 2 || b->accessboard(var2 - 1, var1) == 3)
		{
			if (b->accessboard(var2 - 1, var1) == 3)
			{
				if (b->accessboard(var2 - 1, var1) != 1)
				{
					b->setboard(var2 - 1, var1, 0);
					b->setboard(var2 - 2, var1, 0);
					b->setscore(100);
				}
			}
			else
			{
				b->setboard(var2 - 1, var1, 0);
				b->setscore(50);
			}
		}
		glutPostRedisplay();
	}
		
	if (b->getpacmanobj().life() < 1)
	{
		exit(-1);
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*
* our gateway main function
* */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
