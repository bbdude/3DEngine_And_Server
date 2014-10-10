#pragma once
//#define GLEW_STATIC
#include <gl\glew.h>
#include "VectorLib.h"
#include "SOIL.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include <map>

struct Icon
{
	vector2 size;
	vector3 color = vector3(1, 1, 1);
	float cooldown = 0;
	GLuint	texture;

	void run(){ color = vector3(0, 0, 0); cooldown = 1000; }
};
class ActionBar
{
public:
	vector2 size;
	int select = 0;
	int max = 1;
	GLuint	texture;
	std::map<std::string, Icon> icons;

	ActionBar();
	~ActionBar();

	void loadGLTextures(std::string file);
	void loadGLTexturesIco(std::string file,std::string choice);
	void loadGLTextures(int limit); 
	void update();
	void draw(void);
	void setCD(int choice, int time);
	void init();
	void changeSel(int change);
};

