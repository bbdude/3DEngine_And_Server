#pragma once
//#define GLEW_STATIC
//#define TIXML_USE_STL
#include <gl\glew.h>
#include <iostream>
#include "VectorLib.h"
#include "SOIL.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include "tinyxml.h"
#include "tinystr.h"
//#include <tinyxml.h>
//#include <tinystr.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Talent
{
	int pointsA = 0;
	int pointsM = 1;
	float procTime = 0;
	float cdTime = 20;
	std::string type = "";
	std::string name = "";
	bool avail = false;
	GLuint	texture;
	vector2 position = vector2(0,0);
	vector2 size = vector2(62, 62);
	void loadGLTextures();
	void init();
};

class TalentTree
{
public:
	vector2 size;
	vector<vector<map<string, Talent>>> talents;
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
	void loadElement(vector<vector<map<std::string, Talent>>> & tileNodes, TiXmlElement * node, int column, int subcolumn, int row);
	virtual void loadData();
	void changeSel(int change);
};

