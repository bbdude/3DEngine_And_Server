#pragma once
#include "basicshape.h"
#include "VectorLib.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include <vector>
class Model
{
public:
	Model();
	~Model();
	GLuint	texture;


	std::vector<vector3> vertices;
	std::vector<vector2> uvs;
	std::vector<vector3> normals;

	void loadOBJ(const char * path, std::vector < vector3 > & out_vertices, std::vector < vector2 > & out_uvs, std::vector < vector3 > & out_normals);
	void draw();
	void init(std::string part);

	void loadGLTextures(std::string file);
	void loadGLTextures(int limit);
};

