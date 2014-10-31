#pragma once
//#define GLEW_STATIC
#include <gl\glew.h>
#include <iostream>
#define _WINSOCKAPI_    // stops windows.h including winsock.h
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
#include "ClientDlg.h"
#include <vector>
#include "Bullet.h"
#include "Model.h"
#include "Entity.h"
#include "TalentTree.h"
#include "ActionBar.h"

class GControl
{
public:
	//Var
	ActionBar abar = ActionBar();
	TalentTree tree = TalentTree();
	
	Player player;
	Cube floor;
	//Cube test;
	Entity testEntity;
	//Model testHead;
	//Model testBody;
	std::vector<Cube> cubes = std::vector<Cube>(3);
	std::vector<Bullet> bullets = std::vector<Bullet>(0);
	Bullet masterBullet;
	int updateTimer = 0;
	bool hitOP = false;
	bool hitME = false;
	bool showTree = false;
	string username;// = char[] {'t', 'e', 's', 't', 'U'};

	vector2 mouse = vector2(0, 0);
	vector2 screen = vector2(800, 600);

	enum STATE { SPLASH, MENU, GAME, EXIT, OPTIONS };
	STATE curr;


	std::map<unsigned char, bool> keyState;

	//Functions
	GControl();
	~GControl();
	void draw();
	void drawGui();
	void update(ClientDlg * dlg);
	void init();
	void fireBullet(vector3 & playerPos, float angle, float lx, float ly, float lz);
};

