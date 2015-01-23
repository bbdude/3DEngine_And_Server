#include "stdafx.h"
#include "ActionBar.h"


ActionBar::ActionBar()
{
	icons["icon1"] = Icon();
	icons["icon2"] = Icon();
}


ActionBar::~ActionBar()
{
}

void ActionBar::loadGLTextures(std::string file)
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
void ActionBar::loadGLTexturesIco(std::string file, std::string choice)
{
	icons[choice].texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	icons[choice].cooldown = 0;
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, icons[choice].texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	vector2 screen = vector2(800, 600);
	icons[choice].size.x = (((screen.x - (screen.x / 10)) - (screen.x / 10)) / 10);
}
void ActionBar::loadGLTextures(int limit)
{
}
void ActionBar::update()
{
	for (auto & element : icons)
	{
		//if (element.second.cooldown == 0 && element.second.color == vector3(1, 1, 1))
		if (element.second.cooldown == 0 && element.second.color.x == 0)
		{
			element.second.color = vector3(1, 1, 1);
		}
		else if (element.second.cooldown > 0)
		{
			element.second.cooldown--;
		}
	}
}
void ActionBar::draw(void)
{
	vector2 screen = vector2(800, 600);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen.x, screen.y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	int locationx = (screen.x / 10);
	for (auto & element : icons)
	{
		glColor3f(element.second.color.x, element.second.color.y, element.second.color.z);

		glBindTexture(GL_TEXTURE_2D, element.second.texture);
		glBegin(GL_QUADS);

		glTexCoord2f(1, 1); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 6))); //left top
		glTexCoord2f(1, 0); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 18))); //left bottom
		glTexCoord2f(0, 0); glVertex2f(locationx, (screen.y - (screen.y / 18))); //right bottom
		glTexCoord2f(0, 1); glVertex2f(locationx, (screen.y - (screen.y / 6))); //right top

		glEnd();
		locationx += element.second.size.x + 1;
	}


	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	glTexCoord2f(1,1); glVertex2f(screen.x / 10, (screen.y - (screen.y / 6))); //left top
	glTexCoord2f(1, 0); glVertex2f(screen.x / 10, (screen.y - (screen.y / 18))); //left bottom
	glTexCoord2f(0,0); glVertex2f(screen.x - screen.x / 10, (screen.y - (screen.y / 18))); //right bottom
	glTexCoord2f(0, 1); glVertex2f(screen.x - screen.x / 10, (screen.y - (screen.y / 6))); //right top

	glEnd();

	/*int locationx = (screen.x / 10) + 1;
	for (auto & element : icons)
	{
		glBindTexture(GL_TEXTURE_2D, element.second.texture);

		glBegin(GL_QUADS);

		glTexCoord2f(1, 1); glVertex2f(locationx, (screen.y - (screen.y / 6))); //left top
		glTexCoord2f(1, 0); glVertex2f(locationx, (screen.y - (screen.y / 18))); //left bottom
		glTexCoord2f(0, 0); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 18))); //right bottom
		glTexCoord2f(0, 1); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 6))); //right top



		glEnd();
	}*/


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void ActionBar::init()
{
}
void ActionBar::changeSel(int change)
{
	if (change <= max)
	{
		select = change;
	}
}
void ActionBar::setCD(int choice, int cd)
{

}