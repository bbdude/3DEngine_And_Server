#include "StdAfx.h"
#include "Player.h"
#include <iostream>


Player::Player(void)
{
	lightInf = 0.3f;
	size.fill(10, 10, 10);
	jump = 0;
	angle = 0.0f;
	vertAngle = 0.0f;
	jumpYPos = -15;
	lx = 0.0f;
	lz = -1.0f;
	ly = 0.0f;
	//position.fill(-40, 2, 5);
	position.fill(0, 0, 0);
	speed.fill(0, 0, 0);
	health = 100;
	mana = 100;
	invTimer = 0;
}


Player::~Player(void)
{
}

void Player::update(bool fall)
{
	if (invTimer > 0)
		invTimer -= 0.5;
	if (health > 0 && health < 100 && invTimer == 0)
		health += 0.001;

	if (position.y <= jumpYPos + 30 && jump == 1)
		speed.y = 0.1f;
	else if (jump == 1)
		jump = 0;
	else if (position.y >= 0)// && !fall)
	{
		speed.y = -0.1f;
	}
	else
	{
		jump = 2;
		speed.y = 0;
	}
	position.y += speed.y;
	position.x += speed.x;
	position.z += speed.z;
	speed.fill(0, 0, 0);
}

void Player::draw()
{
}