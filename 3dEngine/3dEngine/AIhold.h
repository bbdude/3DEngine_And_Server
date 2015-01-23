#pragma once
#include "VectorLib.h"
#include "Pathfinding.h"

class AIhold
{
public:
	AIhold();
	~AIhold();

	enum STATE { WALK, STAND, STALK, FLEE, DIE,RETURN };
	STATE curr = STALK;
	vector3 position;
	vector3 returnSpot;
	int stage = 0;
	float ticks = 0;
	float updateTime = 150;
	int followStepsTaken = 0;
	vector<vector3> nextPath;

	static vector3 walkFunction(vector3, vector3&);
	static vector3 standFunction(vector3, vector3&);
	static vector3 stalkFunction(vector3, vector3&);
	static vector3 fleeFunction(vector3, vector3&);
	static vector3 dieFunction(vector3, vector3&);

	vector3(*update)(vector3, vector3&);

	void updateAstar(vector3 start, vector3 goal);
	void updateAstar(vector3& position);
	void updateFollow(vector3 & position);
	void init();

	void changeState(STATE);
	void changeState(std::string);
};

