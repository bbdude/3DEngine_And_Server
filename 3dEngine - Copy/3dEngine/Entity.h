#pragma once
#include "BasicShape.h"
#include "Model.h"
class Entity :
	public BasicShape
{
public:
	Model body;
	Model head;
	vector2 size;
	int health = 100;

	Entity();
	~Entity();

	void init();
	void draw();
	void update();

	bool testColl(vector3 player, vector3 playersize);
};

