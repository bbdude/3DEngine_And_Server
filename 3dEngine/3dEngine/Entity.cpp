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
	position = vector3(0, -18, 0);
	aiHold.returnSpot = position;
	size = vector2(10, 10);
	head.init("head");
	body.init("body");
}
void Entity::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(0.25f, 0.25f, 0.25f);
	body.draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 30, 0);
	glScalef(0.25f, 0.25f, 0.25f);
	glRotatef(-25,0, 1, 0);
	head.draw();
	glPopMatrix();
}
void Entity::updateFollow()
{
	aiHold.updateFollow(position);
}
void Entity::addPoint(vector3 change)
{
	aiHold.updateAstar(position, change);
	//aiHold.nextPath.push_back(change);
}
void Entity::update(vector3 player)
{
	aiHold.updateAstar(position);
	/*switch (aiHold.curr)
	{
	case AIhold::WALK:
		switch (aiHold.stage)
		{
		case 0:
			aiHold.walkFunction(vector3(0, 0, 100), position);
			if (position.z >= 100)
				aiHold.stage++;
			break;
		case 1:
			aiHold.walkFunction(vector3(100, 0, 100), position);
			if (position.z >= 100 && position.x >= 100)
				aiHold.stage++;
			break;
		case 2:
			aiHold.walkFunction(vector3(100, 0, 0), position);
			if (position.z <= 0)
				aiHold.stage++;
			break;
		case 3:
			aiHold.walkFunction(vector3(0, 0, 0), position);
			if (position.z <= 5 && position.x <= 5)
				aiHold.stage = 0;
			break;
		}
		{
			vector3 holdPos = position;
			if ((aiHold.walkFunction(player, holdPos).x == 1))
				aiHold.curr = aiHold.STALK;
		}
		break;
	case AIhold::DIE:break;
	case AIhold::STAND:break;
	case AIhold::STALK:
	{
		//position += aiHold.walkFunction(player, position);
		vector3 checkV = aiHold.stalkFunction(player, position);
		if (checkV.x == 1)
		{
			aiHold.curr = aiHold.RETURN;
			aiHold.stage = 0;
		}
	}
	break;
	case AIhold::RETURN:
		aiHold.walkFunction(aiHold.returnSpot, position);
		//if (position.x == aiHold.returnSpot.x && position.z == aiHold.returnSpot.z)
		if (position.x <= aiHold.returnSpot.x + 1 && position.x >= aiHold.returnSpot.x - 1 &&
			position.z <= aiHold.returnSpot.z + 1 && position.z >= aiHold.returnSpot.z - 1)
		{
			aiHold.curr = aiHold.WALK;
			aiHold.stage = 0;
		}
		break;
	case AIhold::FLEE:
		position -= aiHold.walkFunction(player, position);
		break;
	}*/

}

bool Entity::testColl(vector3 player, vector3 playersize)
{
	//playersize = vector3(4, 0, 4);
	//player.z -= 20;
	player.z -= 20;
	if (player.x > (position.x + size.x)) return false; // box1 is too far right, no collision
	else if ((player.x + playersize.x) < position.x) return false; // box1 is too far left, no collision
	else if (player.z > (position.z + (size.x))) return false; // box1 is too far down, no collision
	else if ((player.z + playersize.x) < position.z - (size.x)) return false; // box1 is too far up, no collision
	else return true;
	return false;
}
