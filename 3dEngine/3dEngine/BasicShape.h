#pragma once
#include "VectorLib.h"
#include "glut.h"
#include "SOIL.h"
#include <sstream>
#define RED		= vector3(1, 0, 0)
#define GREEN	= vector3(0, 1, 0)
#define BLUE	= vector3(0, 0, 1)
#define YELLOW	= vector3(1, 1, 0)
#define CYAN	= vector3(0, 1, 1)
#define MAGENTA = vector3(1, 0, 1)
#define WHITE	= vector3(1, 1, 1)
#define BLACK	= vector3(0, 0, 0)

class BasicShape
{
public:
	BasicShape(void);
	~BasicShape(void);

	vector3 position;
	vector3 speed;
	vector3 size;
};

