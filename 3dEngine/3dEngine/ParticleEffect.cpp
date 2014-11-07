#include "stdafx.h"
#include "ParticleEffect.h"


ParticleEffect::ParticleEffect()
{
}


ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::createSpawnPoint(vector3 target, vector3 maxD,vector4 color, int maxPixels)
{
	vector3 turnOverRate = vector3(-1, 0, 1);

	particles = std::vector<Particle>(maxPixels);
	//maxDistance
	maxPix = maxPixels;
	maxDistance = maxD;
	this->target = target;
	for (auto & i : particles)
	{
		//i.speed = (maxD - target) / vector3(1000000,1000000,1000000);
		//i.speed = (maxD + target) / vector3(1000000, 1000000, 1000000);
		i.speed = (maxD - target) / vector3(10000, 10000, 10000);
		//if (i.speed = vector3(0,0,0))
		//{
			i.speed = vector3(0.005, 0.005, 0.005);
		//}
		//i.values.line[0].a = target.x;
		//i.values.line[0].b = target.y;
		//i.values.line[0].c = target.z;
		i.position = target;
		i.direction = vector3(0,0,0);
		//i.values.line[1].set(0, 0, 0, 0);
		i.color = color;
		//i.values.line[2] = color;
		//i.values.line[3] << turnOverRate;
		i.rotation = turnOverRate;
		i.direction = turnOverRate;
		turnOverRate.x += 360/maxPixels;
		turnOverRate.y += 360 / maxPixels;
		turnOverRate.z += 360 / maxPixels;

		if (turnOverRate.x >= 360)
			turnOverRate.x = 0;
		if (turnOverRate.y >= 360)
			turnOverRate.y = 0;
		if (turnOverRate.z >= 360)
			turnOverRate.z = 0;
	}
}
void ParticleEffect::pushOutMovement(vector3 start, vector3 maxD, vector4 color, int maxPixels)
{
	vector3 turnOverRate = vector3(-1, 0, 1);

	particles = std::vector<Particle>(maxPixels);
	//maxDistance
	maxPix = maxPixels;
	maxDistance = maxD;
	this->target = start;
	int inc = 0;
	int current = 0;
	for (auto & i : particles)
	{
		//i.speed = (maxD - target) / vector3(1000000,1000000,1000000);
		//i.speed = (maxD + target) / vector3(1000000, 1000000, 1000000);
		int inc = 360 / maxPixels;
		int angle = inc * current;
		float radians = angle * (3.14159 / 180);

		//i.speed = (maxD - target) / vector3(10000, 10000, 10000);
		//if (i.speed = vector3(0,0,0))
		//{
		//i.speed = vector3(0.005, 0.005, 0.005);
		
		//}
		//i.values.line[0].a = target.x;
		//i.values.line[0].b = target.y;
		//i.values.line[0].c = target.z;
		i.position = target;
		i.position.x = 50 * std::cos(radians) + target.x;
		i.position.z = 50 * std::sin(radians) + target.z;
		i.position.y = -10;

		i.speed = i.position;
		i.speed.normalise();
		i.speed = i.speed / vector3(8, 8, 8);
		i.speed.y = 0;

		i.direction = vector3(0, 0, 0);
		//i.values.line[1].set(0, 0, 0, 0);
		i.color = color;
		//i.values.line[2] = color;
		//i.values.line[3] << turnOverRate;
		i.rotation = turnOverRate;
		i.direction = turnOverRate;
		turnOverRate.x += 360 / maxPixels;
		turnOverRate.y += 360 / maxPixels;
		turnOverRate.z += 360 / maxPixels;

		if (turnOverRate.x >= 360)
			turnOverRate.x = 0;
		if (turnOverRate.y >= 360)
			turnOverRate.y = 0;
		if (turnOverRate.z >= 360)
			turnOverRate.z = 0;
		current++;
	}
}
void ParticleEffect::updateWithTarget(vector3 currentTarget)
{
	target = currentTarget;
}
void ParticleEffect::changeColor(vector4 color)
{
	for (auto & i : particles)
	{
		//i.values.line[3] = color;
		i.color = color;
	}
}
void ParticleEffect::draw()
{
	for (auto & i : particles)
	{
		

		

		//glMatrixMode(GL_MODELVIEW);
	}
	auto i = std::begin(particles);

	while (i != std::end(particles)) {
		// do some stuff
		if (i->killOff)
		{
			i = particles.erase(i);
			puts("Particle ER");
		}
		else
		{
			glPushMatrix();
			//glRotatef(i->rotation.y, 0, 1, 0);// , i->rotation.y, i->rotation.z);
			//glRotatef(i->rotation.x, 1, 0, 0);// , i->rotation.y, i->rotation.z);
			//glRotatef(i->rotation.z, 0, 0, 1);// , i->rotation.y, i->rotation.z);
			glDisable(GL_TEXTURE);
			glBegin(GL_TRIANGLES);
			glLoadIdentity();
			//bottom
			//glRotatef(i->rotation.x, i->rotation.y, i->rotation.z);
			//glTranslatef(0, 0, 0);
			//glRotatef(i->rotation.z, 0, 0, 1);// , i->rotation.y, i->rotation.z);
			//glRotatef(90, 1, 1, 0);// , i->rotation.y, i->rotation.z);
			//glRotatef(i->rotation.y, 0, 1, 0);// , i->rotation.y, i->rotation.z);
			glColor3f(0,0,0);
			glVertex3f(i->position.x, i->position.y, i->position.z);
			glColor3f(1, 0, 1);
			glVertex3f(i->position.x + 2.5, i->position.y, i->position.z + 2.5);
			glColor3f(0, 1, 0);
			glVertex3f(i->position.x + 2.5, i->position.y, i->position.z - 2.5);
			glColor3f(1, 1, 1);
			glEnd();
			//i->rotation.x += 0.25;
			//i->rotation.y += 0.15;
			//i->rotation.z += 0.05;

			//glRotatef(-i->rotation.y, 0, 1, 0);// , i->rotation.y, i->rotation.z);
			//glRotatef(-i->rotation.x, -1, 0, 0);// , i->rotation.y, i->rotation.z);
			//glRotatef(-i->rotation.z, 0, 0, -1);// , i->rotation.y, i->rotation.z);
			glPopMatrix();
			i->position += i->speed;
			//vector3 invertedMaxDistance = max
			//if (i->position >= maxDistance + target || i->position <= ((maxDistance + target) * -1))
			//	i->killOff = true;
			++i;
		}
	}
}
void ParticleEffect::turnOff()
{
	particles.empty();
	//for (auto & i : particles)
	//{
	
	//	i.color = color;
	//}
}