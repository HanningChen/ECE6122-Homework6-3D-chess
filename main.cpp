/*
	Author:Hanning Chen
	Class:ECE6122
	Last Date Modified:2019.11.21
	Description:This is the source code for ECE6122 hmk6 which includes
				main function ,piece drawing function, board drawing function, display function
				, keyboard function and reshape function
*/
#include<GL/glut.h>
#include<iostream>
#include"Board.h"
#include"OBJ_Loader.h"
#include<vector>
using namespace std;
//board is a 2 dimensional matrix hold the position of the pieces
int** board;
//Here we define switchLight0 and switchLight1 to indentify the state of light
int switchLight0 = 1;
int switchLight1 = 1;
//eyeX,eyeY,eyeZ are the position of the camera
double eyeX = 4;
double eyeY = -5;
double eyeZ = 10;
//eyeUpX,eyeUpY,eyeUpZ are the x,y,z of the up vector of eye
double eyeUpX = 0;
double eyeUpY = 1;
double eyeUpZ = 1;
//Next we specify the parameter of light

GLfloat light1Position[] = { 5,5,8 };

//As piazza shown,we should turn off some parameter of the light0

GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light0_specular[] = { 0,0,0,1 };
GLfloat light0_diffuse[] = { 0,0,0,1 };

GLfloat light1_ambient[] = { 0,0,0,1 };
GLfloat light1_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light1_diffuse[] = { 0.5,0.5,0.5,1 };

//We specify the color here,the white and the black color
GLfloat whiteColorR = (double)140 / 255;
GLfloat whiteColorG = (double)130 / 255;
GLfloat whiteColorB = (double)135 / 255;

GLfloat blackColorR = (double)150 / 255;
GLfloat blackColorG = (double)75 / 255;
GLfloat blackColorB = 0;

//put the white and black color in the vector
GLfloat whiteColor[] = { whiteColorR,whiteColorR,whiteColorB };
GLfloat blackColor[] = { blackColorR,blackColorG,blackColorB };

//angle is the board rotating angle
double angle = 0;
//We store the position of knight, the left knight 1 knight[0] and right knight is knight[1]
double whiteKnightX[2];
double whiteKnightY[2];

double blackKnightX[2];
double blackKnightY[2];
//We store the position of pawn, the left pawn 1 knight[0] and right apwn is knight[1]
double whitePawnX[8];
double whitePawnY[8];

double blackPawnX[8];
double blackPawnY[8];

//drawModeMark indentify whether now the drawing is normal or enhanced
int drawModeMark = 0;

//Init() is function to init the initial effect of light and material 
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Here we specify the smooth model
	glShadeModel(GL_SMOOTH);
	//Here we specify the parameter of the material
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	//Here we specify the parameter of light0 and light1
	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//Here we enable the depth test
	glEnable(GL_DEPTH_TEST);

	//Here we initialize the pawn's positon
	for (int i = 0; i < 8; i++)
	{
		whitePawnX[i] = 0.5 + i;
		whitePawnY[i] = 1.5;
	}
	for (int i = 0; i < 8; i++)
	{
		blackPawnX[i] = 0.5 + i;
		blackPawnY[i] = 6.5;
	}
	//Here we initialize the knight's position
	whiteKnightX[0] = 1.5;
	whiteKnightY[0] = 0.5;
	whiteKnightX[1] = 6.5;
	whiteKnightY[1] = 0.5;

	blackKnightX[0] = 1.5;
	blackKnightY[0] = 7.5;
	blackKnightX[1] = 6.5;
	blackKnightY[1] = 7.5;
	
	//We create a board to store the position of pieces
	board = new int* [8];
	for (int i = 0; i < 8; i++)
		board[i] = new int[8];
	//Here we initiate the pieces position
	initBoard(board);
	//To avoid piece to be too shining, I use this function
	glEnable(GL_NORMALIZE);
}

//This is the function to draw the normal piece
//This is the function to draw the enhanced mode pieces
//We first draw the piece at (0,0,0) and scale it and the move it to the correct position
void drawPiece()
{
	glColor3fv(whiteColor);
	//Here we try to draw the white pawn
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
			glTranslatef(whitePawnX[i], whitePawnY[i], 0.5);
			glScalef(0.75, 0.75, 1);
			glTranslatef(0, 0, 0);
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	}
	//Here we draw the white rook
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.5 + i * 7, 0.5, 0.51);
			glScalef(0.75, 0.75, 1);
			glTranslatef(0, 0, 0);
			glutSolidCube(1);
		glPopMatrix();
	}
	//Here we try to draw the white knight
	glPushMatrix();
		glTranslatef(whiteKnightX[0], whiteKnightY[0], 0.34);
		glScalef(0.25, 0.25, 0.45);
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(whiteKnightX[1], whiteKnightY[1], 0.34);
		glScalef(0.25, 0.25, 0.45);
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
	
	//Here we try to draw the white bishop
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(2.5 + i * 3, 0.5, 0);
			glutSolidCone(0.35, 1, 20, 20);
		glPopMatrix();
	}
	
	//Here we try to draw the white queen
	glPushMatrix();
		glTranslatef(3.5, 0.5, 0.30);
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(0, 0, 0);
		glutSolidTetrahedron();
	glPopMatrix();
	
	//Here we try to draw the white king
	glPushMatrix();
		glTranslatef(4.5, 0.5, 0.42);
		glScalef(0.42, 0.42, 0.42);
		glTranslatef(0, 0, 0);
		glutSolidOctahedron();
	glPopMatrix();
	
	//Here we try to draw the black pawn
	glColor3fv(blackColor);
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
			glTranslatef(blackPawnX[i], blackPawnY[i], 0.5);
			glScalef(0.75, 0.75,1);
			glTranslatef(0, 0, 0);
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	}
	//Here we draw the black rock
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.5 + i * 7, 7.5, 0.51);
			glScalef(0.75, 0.75, 1);
			glTranslatef(0, 0, 0);
			glutSolidCube(1);
		glPopMatrix();
	}
	//Here we try to draw the black knight
	glPushMatrix();
		glTranslatef(blackKnightX[0], blackKnightY[0], 0.34);
		glScalef(0.25, 0.25, 0.45);
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(blackKnightX[1], blackKnightY[1], 0.34);
		glScalef(0.25, 0.25, 0.45);
		glTranslatef(0, 0, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
	
	//Here we try to draw the black bishop
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(2.5 + i * 3, 7.5, 0);
			glutSolidCone(0.35, 1, 20, 20);
		glPopMatrix();
	}
	//Here we try to draw the black queen
	glPushMatrix();
		glTranslatef(3.5, 7.5, 0.3);
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(0, 0, 0);
		glutSolidTetrahedron();
	glPopMatrix();
	//Here we try to draw the black king
	glPushMatrix();
		glTranslatef(4.5, 7.5, 0.42);
		glScalef(0.42, 0.42, 0.42);
		glTranslatef(0, 0, 0);
		glutSolidOctahedron();
	glPopMatrix();
}

//This is the function to draw the board
void drawBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//The odd grid is white and even is black
			if ((i + j) % 2 == 1)
				glColor4f(1, 1, 1, 1);
			else
				glColor4f(0, 0, 0, 1);
			//Here we use the glNormal function to specify the normal of board
			glNormal3f(0, 0, 1);
			//We draw 4 points to draw each square
			glBegin(GL_POLYGON);
			glVertex3d(i, j, 0);
			glVertex3d(i, ((double)j + 1), 0);
			glVertex3d(((double)i + 1), ((double)j + 1), 0);
			glVertex3d(((double)i + 1), j, 0);
			glEnd();
		}
	}
}

//This is the function to draw the enhanced mode pieces
//We first draw the piece at (0,0,0) and scale it and the move it to the correct position
//To draw the enhanced mode chess we have to use enhanceDraw()
void enhanceDrawPiece()
{
	
	//Here we try to draw the white pawn
	glColor3fv(whiteColor);
	
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		glTranslatef(whitePawnX[i], whitePawnY[i],0);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("pawn.obj");
		glPopMatrix();
	}
	
	//Here we draw the white rook
	
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
		glTranslatef(0.5 + i * 7, 0.5, 0.01);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("rook.obj");
		glPopMatrix();
	}
	
	//Here we try to draw the white knight
	glPushMatrix();
		glTranslatef(whiteKnightX[0], whiteKnightY[0], 0.02);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("knight.obj");
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(whiteKnightX[1], whiteKnightY[1], 0.02);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("knight.obj");
	glPopMatrix();
	
	//Here we try to draw the white bishop
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(2.5 + i * 3, 0.5, 0.01);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, 0);
			enhanceDraw("bishop.obj");
		glPopMatrix();
	}
	
	//Here we try to draw the white queen
	glPushMatrix();
		glTranslatef(3.5, 0.5, 0.01);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("queen.obj");
	glPopMatrix();
	
	//Here we try to draw the white king
	glPushMatrix();
		glTranslatef(4.5, 0.5,0.01);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("king.obj");
	glPopMatrix();
	
	//Here we try to draw the black pawn
	glColor3fv(blackColor);
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
			glTranslatef(blackPawnX[i], blackPawnY[i], 0);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, 0);
			enhanceDraw("pawn.obj");
		glPopMatrix();
	}

	//Here we draw the black rock
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.5 + i * 7, 7.5, 0.01);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, 0);
			enhanceDraw("rook.obj");
		glPopMatrix();
	}
	//Here we try to draw the black knight
	glPushMatrix();
		glTranslatef(blackKnightX[0], blackKnightY[0], 0.02);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("knight.obj");
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(blackKnightX[1], blackKnightY[1], 0.02);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("knight.obj");
	glPopMatrix();

	//Here we try to draw the black bishop
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(2.5 + i * 3, 7.5, 0.01);
			glScalef(0.05, 0.05, 0.05);
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, 0);
			enhanceDraw("bishop.obj");
		glPopMatrix();
	}

	//Here we try to draw the black queen
	glPushMatrix();
		glTranslatef(3.5, 7.5, 0.02);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("queen.obj");
	glPopMatrix();

	//Here we try to draw the black king
	glPushMatrix();
		glTranslatef(4.5, 7.5, 0.01);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0);
		enhanceDraw("king.obj");
	glPopMatrix();
}

//Here is the function to excue the draw function and display them
void display(void)
{
	//We have to initiate the initial sistuation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Each time we should use glLoadIdentity to clear the matrix
	glLoadIdentity();
	//When the height of eye is negative we should change the vector
	if (eyeZ >= 0)
	{
		eyeUpY = 1;
		gluLookAt(eyeX, eyeY, eyeZ, 4, 4, 0, eyeUpX, eyeUpY, eyeUpZ);
	}
	else
	{
		eyeUpY = -1;
		gluLookAt(eyeX, eyeY, eyeZ, 4, 4, 0, eyeUpX, eyeUpY, eyeUpZ);
	}
	/*To make sure this board rotate around the center we first move it to the(4,4,0)
		and then move it back.*/
	glTranslatef(4, 4, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-4, -4, 0);
	//Here we use the drawBoard and drawPiece/enhanceDrawPiece function
	drawBoard();
	if (drawModeMark == 0)
		drawPiece();
	else
		enhanceDrawPiece();
	glutSwapBuffers();
}
//To make sure the viewport is correct we should set the viewport parameter here
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//Here we set the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Here we set the perspective matrix
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 2, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//Here we set the function to enable the keyboard operation
void positionKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		//Here we derease the camera height 0.25 when press 'd'
		eyeZ = eyeZ - 0.25;
		glutPostRedisplay();
		break;
	case 'D':
		//Here we derease the camera height 0.25 when press 'D'
		eyeZ = eyeZ - 0.25;
		glutPostRedisplay();
		break;
	case 'u':
		//Here we increase the camera height 0.25 when press 'u'
		eyeZ = eyeZ + 0.25;
		glutPostRedisplay();
		break;
	case 'U':
		//Here we increase the camera height 0.25 when press 'U'
		eyeZ = eyeZ + 0.25;
		glutPostRedisplay();
		break;
	case 'r':
		//Here we rotate the board anti-clock 10 degeree each press 'r'
		angle = angle + 10;
		glutPostRedisplay();
		break;
	case 'R':
		//Here we rotate the board anti-clock 10 degeree each press 'R'
		angle = angle + 10;
		glutPostRedisplay();
		break;
	case '0':
		//When we press '0' the state of the light open or close 
		//light0 depends on current light situation
		if (switchLight0 == 1)
		{
			//if now the light0 is open we close them and then set current state to 0
			glDisable(GL_LIGHT0);
			glutPostRedisplay();
			switchLight0 = 0;
			break;
		}
		else
		{
			//if now the light0 is close we close them and then set current state to 1
			glEnable(GL_LIGHT0);
			glutPostRedisplay();
			switchLight0 = 1;
			break;
		}
	case'1':
		//When we press '0' the state of the light open or close 
		//light0 depends on current light situation
		if (switchLight1 == 1)
		{
			//if now the light1 is open we close them and then set current state to 0
			glDisable(GL_LIGHT1);
			glutPostRedisplay();
			switchLight1 = 0;
			break;
		}
		else
		{
			//if now the light1 is close we close them and then set current state to 1
			glEnable(GL_LIGHT1);
			glutPostRedisplay();
			switchLight1 = 1;
			break;
		}
	case 'k':
		//when we press k, the knight will move
		//knightMoving will change the Knight's postion after pressing
		knightMoving(whiteKnightX, whiteKnightY, blackKnightX, blackKnightY, board);
		glutPostRedisplay();
		break;
		//when we press K, the knight will move
	case 'K':
		knightMoving(whiteKnightX, whiteKnightY, blackKnightX, blackKnightY, board);
		glutPostRedisplay();
		break;
	case 'p':
		//when we press p, the pawn will move
		////pawnMoving will change the pawn's postion after pressing
		pawnMoving(whitePawnX, whitePawnY, blackPawnX, blackPawnY, board);
		glutPostRedisplay();
		break;
	case 'P':
		//when we press P, the pawn will move
		pawnMoving(whitePawnX, whitePawnY, blackPawnX, blackPawnY, board);
		glutPostRedisplay();
		break;
	case 'e':
		//When press e or E the chess piece will change btween normal mode and enhanced mode
		//depending on current situation
		//if current state is normal mode then it will change to enhanced mode etc
		if (drawModeMark == 0)
			drawModeMark = 1;
		else
			drawModeMark = 0;
		glutPostRedisplay();
		break;
	case 'E':
		if (drawModeMark == 0)
			drawModeMark = 1;
		else
			drawModeMark = 0;
		glutPostRedisplay();
		break;
	default:break;
	}
}
//Here is the main function call
int main(int argc, char** argv)
{
	//Here we intiate the DOUBLE and DEPTH test
	int mode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
	glutInit(&argc, argv);
	//Here we set the initial mode including: double depth test and double buffer
	glutInitDisplayMode(mode);
	//The window size of the show is 600 * 600
	glutInitWindowSize(600, 600);
	glutCreateWindow("Chess Board");
	//Here we use the init function to initiate condition
	init();
	//Here we use the display function
	glutDisplayFunc(display);
	//Here we use the reshape function
	glutReshapeFunc(reshape);
	//Here we use the set the keyboard function
	glutKeyboardFunc(positionKeyboard);
	glutMainLoop();
}
