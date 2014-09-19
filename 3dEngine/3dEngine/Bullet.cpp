#include "StdAfx.h"
#include "Bullet.h"


Bullet::Bullet(void)
{
	killOff = false;
}


Bullet::~Bullet(void)
{
}

void Bullet::operator << (Bullet change)
{
	angle = change.angle;
	color = change.color;
	/*for (int i = 0; i < 7; i++)
	{
		vertex[i] = change.vertex[i];
	}for (int i = 0; i < 12; i++)
	{
		polygon[i] = change.polygon[i];
	}*/
	//polygon = change.polygon;
	size = change.size;
	speed = change.speed;
	position = change.position;
	texture = change.texture;
}
void Bullet::updateSpeed()
{
	position += speed;
	if (position.x <= -1000 || position.x >= 1000 || position.y <= -1000 || position.y >= 1000)
		killOff = true;
}