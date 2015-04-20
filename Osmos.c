#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 10

//Player square position. Order : LEFT TOP RIGHT BOTTOM
GLint player[4] = {350,400,400,350};
//All other squares position AND direction. Yet to be initialised.
GLint others[MAX][5];
void myinit()
{

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1366,0,768);
	glMatrixMode(GL_MODELVIEW);
	InitialiseOthers();
}

//Draws player
void DrawPlayer()
{
	glPointSize(2.0);
	glBegin(GL_QUADS);
        glColor3f(0.5,1.0,0.5);
        glVertex2f(player[0], player[3]);
        glVertex2f(player[0], player[1]);
        glVertex2f(player[2], player[1]);
        glVertex2f(player[2], player[3]);
    glEnd();
}

void ModifyPlayer(int x, int y)
{
	player[0] += x;
	player[2] += x;
	player[1] += y;
	player[3] += y;
	display();
}

void MovePlayer(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a':
			ModifyPlayer(-10,0);
			break;
		case 'd':
			ModifyPlayer(10,0);
			break;
		case 'w':
			ModifyPlayer(0,10);
			break;
		case 's':
			ModifyPlayer(0,-10);
			break;
		default:
			break;
	}
}

void InitialiseOthers()
{
	int i, sizebox;
	for(i = 0; i < MAX; i++)
	{
		sizebox = (rand() % 70) + 30;
		others[i][0] = rand() % 750;
		others[i][1] = rand() % 750;
		others[i][2] = others[i][0] + sizebox;
		others[i][3] = others[i][1] - sizebox;
		others[i][4] = rand() % 8;
	}
}
void DrawOthers()
{
	int i;
	glPointSize(2.0);
	glColor3f(0.258824,0.258824,0.435294);
	for(i = 0; i < MAX; i++)
	{
		glBegin(GL_QUADS);
			glVertex2f(others[i][0], others[i][3]);
			glVertex2f(others[i][0], others[i][1]);
			glVertex2f(others[i][2], others[i][1]);
			glVertex2f(others[i][2], others[i][3]);
		glEnd();
	}
}

void ModifyOthers()
{
	float x, y, speed = 1;
	int i;
	for(i = 0; i < MAX; i++)
	{
		switch(others[i][4])
		{
			case 0:
				x = speed;
				y = 0;
				break;
			case 1:
				x = speed;
				y = -speed;
				break;
			case 2:
				x = 0;
				y = -speed;
				break;
			case 3:
				x = -speed;
				y = -speed;
				break;
			case 4:
				x = -speed;
				y = 0;
				break;
			case 5:
				x = -speed;
				y = speed;
				break;
			case 6:
				x = 0;
				y = speed;
				break;
			case 7:
				x = speed;
				y = speed;
				break;
			default:
				break;
		}
		others[i][0] += x;
		others[i][1] += y;
		others[i][2] += x;
		others[i][3] += y;

//Bounce off LEFT wall
		if(others[i][0] == 0)
		{
			switch(others[i][4])
			{
				case 3:
					others[i][4] = 1;
					break;
				case 4:
					others[i][4] = 0;
					break;
				case 5:
					others[i][4] = 7;
					break;
					break;
				default:
					break;
			}
		}
//Bounce off TOP wall
		if(others[i][1] == 768)
		{
			switch(others[i][4])
			{
				case 5:
					others[i][4] = 3;
					break;
				case 6:
					others[i][4] = 2;
					break;
				case 7:
					others[i][4] = 1;
					break;
					break;
				default:
					break;
			}
		}
//Bounce off RIGHT wall
		if(others[i][2] == 1366)
		{
			switch(others[i][4])
			{
				case 0:
					others[i][4] = 4;
					break;
				case 1:
					others[i][4] = 3;
					break;
				case 7:
					others[i][4] = 5;
					break;
					break;
				default:
					break;
			}
		}
//Bounce off BOTTOM wall
		if(others[i][3] == 0)
		{
			switch(others[i][4])
			{
				case 1:
					others[i][4] = 7;
					break;
				case 2:
					others[i][4] = 6;
					break;
				case 3:
					others[i][4] = 5;
					break;
					break;
				default:
					break;
			}
		}
	}
	display();
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawPlayer();
	DrawOthers();
	glFlush();
	ModifyOthers();
}



int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Osmos");
	glutDisplayFunc(display);
	glutKeyboardFunc(MovePlayer);
	myinit();
	glutMainLoop();
	return 0;
}
