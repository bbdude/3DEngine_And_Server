#pragma once
//#define GLEW_STATIC
#include <gl\glew.h>
#include "VectorLib.h"
#include "SOIL.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include <map>

class TalentTree
{
public:
	vector2 size;
	int select = 0;
	int tree = 1;
	GLuint	texture;
	bool up = false;
	TalentTree();
	~TalentTree();

	void loadGLTextures(std::string file);
	//void loadGLTexturesIco(std::string file, std::string choice);
	void loadGLTextures(int limit);
	void update();
	void draw(void);
	void setCD(int choice, int time);
	void init();
	void changeSel(int change);
};

