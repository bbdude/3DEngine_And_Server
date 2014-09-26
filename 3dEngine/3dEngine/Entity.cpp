#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}


void Entity::init()
{
	//position = position.empty();
	position = vector3(15, -18, 15);
	size = vector2(10, 10);
	head.init("head");
	body.init("body");
}
void Entity::draw()
{
	glTranslatef(position.x, position.y, position.x);
	body.draw();
	glTranslatef(0, 30, 0);
	glRotatef(-25,0, 1, 0);
	head.draw();
}
void Entity::update()
{

}

bool Entity::testColl(vector3 player, vector3 playersize)
{
	//playersize = vector3(4, 0, 4);
	//player.z -= 20;
	player.x -= 20;
	if (player.x > (position.x + size.x)) return false; // box1 is too far right, no collision
	else if ((player.x + playersize.x) < position.x) return false; // box1 is too far left, no collision
	else if (player.z > (position.z + (size.x))) return false; // box1 is too far down, no collision
	else if ((player.z + playersize.x) < position.z - (size.x)) return false; // box1 is too far up, no collision
	else return true;
	return false;
}
