#pragma once
//#define GLEW_STATIC
#include <gl\glew.h>
#include "cube.h"
#include "VectorLib.h"

class Bullet :
	public Cube
{
public:
	Bullet(void);
	~Bullet(void);

	void operator << (Bullet change);
	void updateSpeed();
	vector3 speed;
	bool killOff;
	//float angle;
};
