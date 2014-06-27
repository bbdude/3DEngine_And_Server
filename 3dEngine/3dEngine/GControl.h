#pragma once
#include <iostream>
#include <windows.h>
#include "glut.h"
#include <math.h>
#include <map>
#include <gl/GL.h>
#include <gl\GLU.h>
#include "SOIL.h"
#include "VectorLib.h"
#include "BasicShape.h"
#include "Cube.h"
#include "Player.h"

class GControl
{
public:
	//Var
	Player player;
	Cube floor;
	Cube test;

	vector2 mouse = vector2(0, 0);
	vector2 screen = vector2(800, 600);

	enum STATE { SPLASH, MENU, GAME, EXIT, OPTIONS };
	STATE curr;


	std::map<unsigned char, bool> keyState;

	//Functions
	GControl();
	~GControl();
	void draw();
	void update();
	void init();
};

