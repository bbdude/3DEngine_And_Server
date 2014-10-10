#ifndef __SHADER_H
#define __SHADER_H

#include "stdafx.h"
#include <string>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

class Shader {
public:
	Shader();
	Shader(const char *vsFile, const char *fsFile);
	~Shader();
	
    void init(const char *vsFile, const char *fsFile);
    
	void bind();
	void unbind();
	
	unsigned int id();
	
private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
};
#endif
