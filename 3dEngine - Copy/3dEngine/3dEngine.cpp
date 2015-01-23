// 3dEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#define GLEW_STATIC
#include <gl\glew.h>
#include <iostream>
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>
#include "glut.h"
#include <stdio.h>
//#include <gl/GL.h>
//#include <gl\GLU.h>
#include "SOIL.h"
#include "VectorLib.h"
#include "GControl.h"
#include "ClientDlg.h"
#include "Maths\Maths.h"

GControl gcon;
ClientDlg * m_pClient;


//Camera & light positions
VECTOR3D cameraPosition(-2.5f, 3.5f, -2.5f);
VECTOR3D lightPosition(2.0f, 3.0f, -2.0f);


//Size of shadow map
const int shadowMapSize = gcon.screen.x;

//Textures
GLuint shadowMapTexture;

//Matrices
MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;

void resize(int width, int height)
{
	gcon.screen.x = width;
	gcon.screen.y = height;
	//Update the camera's projection matrix
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, (float)gcon.screen.x / gcon.screen.y, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
	glPopMatrix();
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
	case 'n': case 'N':
		gcon.showTree = !gcon.showTree;
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
void DrawScene(float angle)
{
	//Display lists for objects
	static GLuint spheresList = 0, torusList = 0, baseList = 0;

	//Create spheres list if necessary
	if (!spheresList)
	{
		spheresList = glGenLists(1);
		glNewList(spheresList, GL_COMPILE);
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glPushMatrix();

			glTranslatef(0.45f, 1.0f, 0.45f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(-0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(0.0f, 0.0f, -0.9f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glPopMatrix();
		}
		glEndList();
	}

	//Create torus if necessary
	if (!torusList)
	{
		torusList = glGenLists(1);
		glNewList(torusList, GL_COMPILE);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPushMatrix();

			glTranslatef(0.0f, 0.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutSolidTorus(0.2, 0.5, 24, 48);

			glPopMatrix();
		}
		glEndList();
	}

	//Create base if necessary
	if (!baseList)
	{
		baseList = glGenLists(1);
		glNewList(baseList, GL_COMPILE);
		{
			glColor3f(0.0f, 0.0f, 1.0f);
			glPushMatrix();

			glScalef(1.0f, 0.05f, 1.0f);
			glutSolidCube(3.0f);

			glPopMatrix();
		}
		glEndList();
	}


	//Draw objects
	glCallList(baseList);
	glCallList(torusList);

	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glCallList(spheresList);
	glPopMatrix();
}
void display(void)
{
	//gluLookAt(gcon.player.position.x, gcon.player.position.y + 1.0f, gcon.player.position.z, gcon.player.position.x + gcon.player.lx, gcon.player.position.y + 1.0f + gcon.player.ly, gcon.player.position.z + gcon.player.lz, 0.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix);

	//Use viewport the same size as the shadow map
	glViewport(0, 0, shadowMapSize, shadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	//DrawScene(0);
	gcon.draw();

	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);




	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cameraProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cameraViewMatrix);

	//glViewport(0, 0, gcon.screen.x, gcon.screen.y);

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	//DrawScene(0);
	gcon.draw();



	//3rd pass
	//Draw with bright light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]
	MATRIX4X4 textureMatrix = biasMatrix*lightProjectionMatrix*lightViewMatrix;

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);

	//Bind & enable shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

	//DrawScene(0);
	gcon.draw();

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);



	/*//Update frames per second counter
	fpsCounter.Update();

	//Print fps
	static char fpsString[32];
	sprintf(fpsString, "%.2f", fpsCounter.GetFps());

	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Print text
	glRasterPos2f(-1.0f, 0.9f);
	for(unsigned int i=0; i<strlen(fpsString); ++i)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);*/

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();

	///<summary>Update commands </summary>
	update();
	keyCommands();
}
void init()
{
	//glClearColor(0.0, 0.0, 0.2, 0.0);
	//glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, gcon.screen.x, gcon.screen.y);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)gcon.screen.x / (GLfloat)gcon.screen.y, 1.0f, 1000.0f);
	//glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glutSetCursor(GLUT_CURSOR_NONE);

	if (glewIsSupported("GL_ARB_depth_texture"))
	{
		puts("Supported");
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Use the color as the ambient and diffuse material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//White specular material color, shininess 16
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	//Calculate & save matrices
	glPushMatrix();

	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)gcon.screen.x / (GLfloat)gcon.screen.y, 1.0f, 1000.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);

	glLoadIdentity();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);

	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);

	glLoadIdentity();
	gluLookAt(lightPosition.x, lightPosition.y, lightPosition.z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);

	glPopMatrix();

	//Reset timer
	//timer.Reset();




	gcon.init();
}

int main(int argc, char** argv)
{
	//ClientDlg cld = ClientDlg();
	//glewExperimental = TRUE;
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	m_pClient = new ClientDlg();// = new ClientCon();// = new ClientCon(void);
	m_pClient->m_pClient = new ClientCon();
	//m_pClient->m_pClient->StartConnect("192.168.0.4", 85, "testI");
	//m_pClient->m_pClient->StartConnect("10.15.20.143", 85, "testI");
	gcon.username = "testI";
	//gcon.// = char[]{ 't', 'e', 's', 't', 'U' };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gcon.screen.x, gcon.screen.y);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Darths R6 Demake, Fo Shizzle");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
		//Problem: glewInit failed, something is seriously wrong.
		//cout << "glewInit failed, aborting." << endl;
	}
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
	}

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

