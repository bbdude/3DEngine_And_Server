#pragma once
////#define GLEW_STATIC
#include <gl\glew.h>
#include "basicshape.h"
#include "VectorLib.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include <vector>
#include "shader.h"

class Model
{
public:
	Model();
	~Model();
	int frames = 0;
	int currentFrame = 0;
	int time = 0;
	GLuint	texture;
	/*GLuint v;
	GLuint f;
	GLuint f2;
	GLuint p;*/
	Shader shader = Shader();

	//std::map<int,std::vector<vector3>> vertices;
	//std::map<int, std::vector<vector2>> uvs;
	//std::map<int, std::vector<vector3>> normals;
	std::vector<std::vector<vector3>> vertices;
	std::vector<std::vector<vector2>> uvs;
	std::vector<std::vector<vector3>> normals;
	//std::vector<vector3> vertices;
	//std::vector<vector2> uvs;
	//std::vector<vector3> normals;

	void loadOBJ(const char * path, std::vector < vector3 > & out_vertices, std::vector < vector2 > & out_uvs, std::vector < vector3 > & out_normals);
	void draw();
	void init(std::string part);
	void setShaders();

	void loadGLTextures(std::string file);
	void loadGLTextures(int limit);
};

