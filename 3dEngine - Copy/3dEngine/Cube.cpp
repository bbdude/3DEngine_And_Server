#include "StdAfx.h"
#include "Cube.h"

Cube::Cube(void){
	position.x = 0;
	position.y = 0;
	position.z = 0;

	this->size.x = 5;
	this->size.y = 5;
}
Cube::Cube(float x, float y, float z, float width, float height)
{
	position.x = x;
	position.y = y;
	position.z = z;

	this->size.x = width;
	this->size.y = height;
}
Cube::~Cube(void){}
void Cube::loadGLTextures(std::string file)
{
	texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
void Cube::loadGLTextures(int limit){}
void Cube::update(){ light = 0.5f; }
void Cube::update(float lighInf, vector3 playerPos)
{
	float distance = sqrt((playerPos.x - position.x)*(playerPos.x - position.x) + (playerPos.y - position.y)*(playerPos.y - position.y) + (playerPos.z - position.z)*(playerPos.z - position.z));
	light = distance * 0.01f;
}
void Cube::draw(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//bottom
	glTexCoord2f(0, 0); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 0); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glTexCoord2f(0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glPopMatrix();


	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//top
	glTexCoord2f(0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 1); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glTexCoord2f(0, 1); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//front
	glTexCoord2f(0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glTexCoord2f(1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glTexCoord2f(1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glTexCoord2f(0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//back
	glTexCoord2f(0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glTexCoord2f(0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//left
	glTexCoord2f(0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 0); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glTexCoord2f(0, 1); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//right
	glTexCoord2f(0, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 0); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glTexCoord2f(1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glTexCoord2f(0, 1); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnd();
}
void Cube::drawC(void)
{
	glBegin(GL_QUADS);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//bottom
	glColor3f(1,0, 0); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glColor3f(1,1, 0); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glColor3f(1,1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glColor3f(1,0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glPopMatrix();


	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//top
	glColor3f(1,0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 1); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glColor3f(1,0, 1); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//front
	glColor3f(1,0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glColor3f(1,1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glColor3f(1,1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glColor3f(1,0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//back
	glColor3f(1,0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glColor3f(1,0, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//left
	glColor3f(1,0, 0); glVertex3f(position.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 0); glVertex3f(position.x, position.y - (size.y / 2), position.z - size.x);
	glColor3f(1,1, 1); glVertex3f(position.x, position.y - (size.y / 2), position.z);
	glColor3f(1,0, 1); glVertex3f(position.x, position.y + (size.y / 2), position.z);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 1, 1);
	//right
	glColor3f(1,0, 0); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z - size.x);
	glColor3f(1,1, 0); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z - size.x);
	glColor3f(1,1, 1); glVertex3f(position.x + size.x, position.y - (size.y / 2), position.z);
	glColor3f(1,0, 1); glVertex3f(position.x + size.x, position.y + (size.y / 2), position.z);
	glPopMatrix();
	glEnd();
}
void Cube::init()
{
	curTex = 0;

	loadGLTextures("cube.png");
}
void Cube::init(std::string file)
{
	curTex = 0;

	loadGLTextures(file);
}
void Cube::fill(vector3 position, vector2 size, vector3 color, float angle)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->angle = angle;
}
void Cube::fill(vector3 position, vector2 size, float angle)
{
	this->position = position;
	this->size = size;
	this->angle = angle;
	this->color.fill(0, 0, 0);
}
void Cube::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	color.x = r;
	color.y = g;
	color.z = b;
}

bool Cube::testColl(vector3 player, vector3 playersize)
{
	if (player.x > (position.x + size.x)) return false; // box1 is too far right, no collision
	else if ((player.x + playersize.x) < position.x) return false; // box1 is too far left, no collision
	else if (player.z > (position.z + (size.x))) return false; // box1 is too far down, no collision
	else if ((player.z + playersize.x) < position.z - (size.x)) return false; // box1 is too far up, no collision
	else return true;
	return false;
}