// 3dEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>
#include "glut.h"
#include <stdio.h>
#include <gl/GL.h>
#include <gl\GLU.h>
#include "SOIL.h"
#include "VectorLib.h"
#include "GControl.h"
#include "ClientDlg.h"

GControl gcon;
ClientDlg * m_pClient;

void resize(int width, int height)
{
	gcon.screen.x = width;
	gcon.screen.y = height;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, gcon.screen.x, gcon.screen.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)gcon.screen.x / (GLfloat)gcon.screen.y, 1.0f, 1000.0f);
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){ gcon.keyState[key] = true; }
void keyboardUp(unsigned char key, int x, int y)
{
	gcon.keyState[key] = false;

	//if (key == 'W' || key == 'A' || key == 'D' || key 'S')
	switch (key)
	{
	/*case 'W':
		gcon.keyState['W'] = false;
		break;
	case 'A':
		gcon.keyState['A'] = false;
		break;
	case 'D':
		gcon.keyState['D'] = false;
		break;
	case 'S':
		gcon.keyState['S'] = false;
		break;*/
	case ' ':
		if (gcon.player.jump == 2 && gcon.curr == gcon.GAME)
		{
			gcon.player.jump = 1;
			gcon.player.jumpYPos = gcon.player.position.y;
			//position.y++;
		}
		else if (gcon.curr == gcon.MENU)
		{
			gcon.curr = gcon.GAME;
		}
		break;
	case 27:
		exit(0);
		break;
	case 'q': case 'Q':
		gcon.fireBullet(gcon.player.position, 0, gcon.player.lx, gcon.player.ly, gcon.player.lz);
		break;
	case '/':
		gcon.player.position.x = 0;
		gcon.player.position.z = 0;
		gcon.player.position.y = 0;
		std::cout << gcon.player.lx << "," << gcon.player.ly << "/n";
		break;
	//case '8': case 'w': case 'W':case '4': case 'a': case 'A':case '2': case 's': case 'S':case '6': case 'd': case 'D':
		//gcon.player.speed.x = 0;
		//gcon.player.speed.z = 0;
		//break;
	case 'p': case 'P':
		glutFullScreen();
		break;
	case 'f': case 'F':
		if (gcon.player.filling == 0)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			gcon.player.filling = 1;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			gcon.player.filling = 0;
		}
		break;
	}
}
void keyboardS(int key, int x, int y){}
void keyCommands()
{
	for (auto & element : gcon.keyState)
	{
		if (element.second)
		{
			float modifier = 0.1f;
			//char newkey = (char)(((int)'0') + key);
			//if (element.first >= 'A' && element.first <= 'Z')
			/*if (element.second == 'W' || element.second == 'D' || element.second == 'A' || element.second == 'S')
			{
				modifier = 0.2f;
				element.second = false;
			}*/
			switch (element.first)
			{
			case 'w':
				gcon.player.speed.x = gcon.player.lx * modifier;
				gcon.player.speed.z = gcon.player.lz * modifier;
				break;
			case 's':
				gcon.player.speed.x = -(gcon.player.lx * modifier);
				gcon.player.speed.z = -(gcon.player.lz * modifier);
				break;
			case 'a':
				gcon.player.speed.x = (gcon.player.lz) * modifier;
				gcon.player.speed.z = -(gcon.player.lx) * modifier;
				break;
			case 'd':
				gcon.player.speed.x = -(gcon.player.lz) * modifier;
				gcon.player.speed.z = (gcon.player.lx) * modifier;
				break;

			case 'Q':
				break;
			}
		}
	}
}
void update()
{
	gcon.update(m_pClient);
	//gcon.player.update(true);
	//std::cout << gcon.player.position.x << "," << gcon.player.position.y << "," << gcon.player.position.z;
}
void mouseMotion(int x, int y)
{
	//if (!maps.paused)
	//{
	static bool warped = false;
	bool capture = false;
	if (warped)
	{
		warped = false;
		return;
	}

	gcon.mouse.x = x;
	gcon.mouse.y = y;
	if (x != gcon.screen.x || y != gcon.screen.y)
		capture = true;
	if (capture)
	{
		warped = true;
		if (x > gcon.screen.x / 2)
		{
			gcon.player.angle -= 0.05f;
			gcon.player.lx = sin(gcon.player.angle);
			gcon.player.lz = -cos(gcon.player.angle);
			glutWarpPointer(gcon.screen.x / 2, gcon.screen.y / 2);
		}
		else if (x < gcon.screen.x / 2)
		{
			gcon.player.angle += 0.05f;
			gcon.player.lx = sin(gcon.player.angle);
			gcon.player.lz = -cos(gcon.player.angle);
			glutWarpPointer(gcon.screen.x / 2, gcon.screen.y / 2);
		}
		if (y < gcon.screen.y / 2 && gcon.player.vertAngle < 0.8)
		{
			gcon.player.vertAngle += 0.05f;
			gcon.player.ly = sin(gcon.player.vertAngle);
			glutWarpPointer(gcon.screen.x / 2, gcon.screen.y / 2);
		}
		else if (y > gcon.screen.y / 2 && gcon.player.vertAngle > -0.8)
		{
			gcon.player.vertAngle -= 0.05f;
			gcon.player.ly = sin(gcon.player.vertAngle);
			glutWarpPointer(gcon.screen.x / 2, gcon.screen.y / 2);
		}
	}
	//}
}
void mouseClick(int button, int state, int x, int y){}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///<summary>Draw commands </summary>

	switch (gcon.curr)
	{
	case gcon.GAME:

		gluLookAt(gcon.player.position.x, gcon.player.position.y + 1.0f, gcon.player.position.z, gcon.player.position.x + gcon.player.lx, gcon.player.position.y + 1.0f + gcon.player.ly, gcon.player.position.z + gcon.player.lz, 0.0f, 1.0f, 0.0f);

		gcon.player.draw();
		gcon.draw();
		break;
	case gcon.MENU:
		//drawMenu();
		break;
	case gcon.EXIT:
		break;
	case gcon.SPLASH:
		break;
	case gcon.OPTIONS:
		break;
	}
	glFlush();
	glutSwapBuffers();

	///<summary>Update commands </summary>
	update();
	keyCommands();
}
void init()
{
	glClearColor(0.0, 0.0, 0.2, 0.0);
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, gcon.screen.x, gcon.screen.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)gcon.screen.x / (GLfloat)gcon.screen.y, 1.0f, 1000.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glutSetCursor(GLUT_CURSOR_NONE);
	gcon.init();
}

int main(int argc, char** argv)
{
	//ClientDlg cld = ClientDlg();
	m_pClient = new ClientDlg();// = new ClientCon();// = new ClientCon(void);
	m_pClient->m_pClient = new ClientCon();
	//m_pClient->m_pClient->StartConnect("192.168.0.4", 85, "testI");
	m_pClient->m_pClient->StartConnect("192.168.0.4", 85, "testI");
	gcon.username = "testI";
	//gcon.// = char[]{ 't', 'e', 's', 't', 'U' };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gcon.screen.x, gcon.screen.y);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Darths R6 Demake, Fo Shizzle");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardS);
	glutPassiveMotionFunc(mouseMotion);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutMouseFunc(mouseClick);
	init();
	glutMainLoop();

	return(1);
}

