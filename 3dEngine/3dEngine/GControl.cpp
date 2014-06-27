#include "stdafx.h"
#include "GControl.h"


GControl::GControl(){}
GControl::~GControl(){}
void GControl::draw()
{
	test.draw();
	floor.draw();
}
void GControl::update()
{
	test.update(0, vector3(0, 0, 0));
	floor.update(0, vector3(0, 0, 0));
	player.update(true);
}
void GControl::init()
{
	//test.LoadGLTextures(1);
	curr = GAME;
	vector3 position(500, -20, -500);
	vector3 color(0.4, 0.3, 0);
	vector2 size(-1000, 1);
	floor.fill(position, size, color, 0);
	floor.init("floor.png");

	position.fill(100, 15, -100);
	size << vector2(10, 10);
	test.fill(position, size, color, 0);
	test.init("wood.png");
}