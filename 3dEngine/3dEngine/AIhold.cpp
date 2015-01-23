#include "stdafx.h"
#include "AIhold.h"


AIhold::AIhold()
{
}


AIhold::~AIhold()
{
}
vector3 AIhold::walkFunction(vector3 walk, vector3 & position)
{
	vector3 newPoint = vector3(walk.x - position.x, 0, walk.z - position.z);
	float len = sqrt(newPoint.x * newPoint.x + newPoint.z * newPoint.z);
	vector3 speed = vector3(0,0,0);
	if (len == 0)
		return speed;
	speed.x += newPoint.x / len;
	speed.z += newPoint.z / len;
	speed.y = 0;
	speed = vector3(speed.x / 5, 0, speed.z / 5);
	position += speed;
	if (len < 150 || len > -150)
		speed.x = 1;
	return speed;
}
vector3 AIhold::standFunction(vector3 blank, vector3 & position)
{
	return position;
}
vector3 AIhold::stalkFunction(vector3 target, vector3 & position)
{
	//position += walkFunction(target, position);
	//return position;

	vector3 newPoint = vector3(target.x - position.x, 0, target.z - position.z);
	float len = sqrt(newPoint.x * newPoint.x + newPoint.z * newPoint.z);
	vector3 speed = vector3(0, 0, 0);
	if (len == 0)
		return speed;
	speed.x += newPoint.x / len;
	speed.z += newPoint.z / len;
	speed.y = 0;
	speed = vector3(speed.x / 25, 0, speed.z / 25);
	position += speed;
	if (len > 150 || len < - 150)
		speed.x = 1;
	return speed;
}
vector3 AIhold::fleeFunction(vector3 fleePoint, vector3 & position)
{
	return fleePoint;
}
vector3 AIhold::dieFunction(vector3 blank, vector3 & position)
{
	return position;
}

void AIhold::changeState(STATE newState)
{
	//enum STATE { WALK, STAND, STALK, FLEE, DIE };
	switch (newState)
	{
	case WALK:
		update = &this->walkFunction;
		break;
	case STAND:
		update = &this->standFunction;
		break;
	case STALK:
		update = &this->stalkFunction;
		break;
	case FLEE:
		update = &this->fleeFunction;
		break;
	case DIE:
		update = &this->dieFunction;
		break;
	}
}
void AIhold::changeState(std::string newState)
{}
void AIhold::updateFollow(vector3 & position)
{
	if (!nextPath.empty())
	{
		walkFunction(nextPath.front() * 10, position);

		vector3 sendPos = position;
		sendPos.y = 0;

		if (sendPos.closeequals(nextPath.front() * 10, 0.5f))
		{
			nextPath.erase(nextPath.begin());
		}
	}
}
void AIhold::updateAstar(vector3 start, vector3 goal)
{
	vector3 position = start;
	position.x /= 10;
	position.z /= 10;
	position.y = 0;
	goal.y = 0;
	vector3 tempPos = position;
	Astar holder = Astar();
	string bob = holder.generate((int)start.x/10, (int)start.z/10, (int)goal.x/10, (int)goal.z/10);
	for (auto c : bob)
	{
		switch (c)
		{
		case '0':
			position.x += 1;
			nextPath.push_back(position);
			break;
		case '1':
			position.z += 1;
			nextPath.push_back(position);
			break;
		case '2':
			position.x -= 1;
			nextPath.push_back(position);
			break;
		case '3':
			position.z -= 1;
			nextPath.push_back(position);
			break;
		default:
			break;
		}
	}
	int bobet = 0;
	//PathFinding newPath = PathFinding();
	//newPath.FindPath(position, vector3(100, 0, 100));
	//newPath.GetNextCell();
	//int bob = 5;
}
void AIhold::updateAstar(vector3 & position)
{
	vector3 tempPos = position;
	//tempPos.x /= 10;
	//tempPos.z /= 10;
	if (!nextPath.empty())
		//updateAstar(tempPos, vector3(250, 0, 250));
	//else
	{
		walkFunction(nextPath.front() * 10, position);

		vector3 sendPos = position;
		sendPos.y = 0;

		if (sendPos.closeequals(nextPath.front() * 10, 0.5f))
		{
			followStepsTaken++;
			nextPath.erase(nextPath.begin());
		}
	}
}
/*void AIhold::updateAstar(vector3 & position)
{
	vector3 tempPos = position;
	//tempPos.x /= 10;
	//tempPos.z /= 10;
	if (nextPath.empty())
		updateAstar(tempPos, vector3(250, 0, 250));
	else
	{
		walkFunction(nextPath.front() * 10, position);

		vector3 sendPos = position;
		sendPos.y = 0;

		if (sendPos.closeequals(nextPath.front() * 10, 0.5f))
		{
			nextPath.erase(nextPath.begin());
		}
	}
}*/