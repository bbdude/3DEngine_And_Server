#pragma once
#include "basicshape.h"
#include "VectorLib.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>

class Cube :
	public BasicShape
{
public:
	Cube(void);
	Cube(float x, float y, float z, float width, float height);
	~Cube(void);	

	//vector3 position;
	vector3 color;
	vector2 size;

	float angle;
	float curTex;
	float light;
	bool floor;

	GLuint	texture;

	void loadGLTextures(std::string file);
	void loadGLTextures(int limit); void update();
	void update(float lighInf, vector3 playerPos);
	void draw(void);
	void init();
	void init(std::string file);
	void fill(vector3 position, vector2 size, vector3 color, float angle);
	void fill(vector3 position, vector2 size, float angle);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
};

