#pragma once
#include "BasicShape.h"
#include "Model.h"
#include "AIhold.h"

class Entity :
	public BasicShape
{
public:
	Model body;
	Model head;
	AIhold aiHold;
	vector2 size;
	int health = 100;

	Entity();
	~Entity();

	void init();
	void draw();
	void update(vector3 player);
	void updateFollow();
	void addPoint(vector3 change);

	bool testColl(vector3 player, vector3 playersize);
};

