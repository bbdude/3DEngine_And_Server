#pragma once
#include "Cube.h"
class Player
{
public:
	vector3 position;
	vector3 speed;
	vector3 size;
	int filling;
	int jump;
	float health;
	float mana;
	float invTimer;
	float angle;
	float vertAngle;
	float jumpYPos;
	float lx;
	float lz;
	float ly;
	float lightInf;
	float armAngle;

	Player();
	~Player(); 
	void update(bool fall);
	void draw();
};

