#pragma once
#include <gl\glew.h>
#include "basicshape.h"
#include "VectorLib.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include <vector>
#include "shader.h"
#include <vector>
#include "Cube.h"

struct Particle
{
	//Position, direction,color,rotation
	//Matrix values = Matrix();
	vector3 position = vector3();
	vector3 speed = vector3();
	vector3 rotation = vector3();
	vector3 direction = vector3();
	vector4 color = vector4();
	bool killOff = false;
};
class ParticleEffect
{
public:
	//Where the particles originate from.
	vector3 target;
	//distance particles reset at
	vector3 maxDistance;
	//Max amount of particles
	int maxPix;
	//The particles array
	std::vector<Particle> particles;

	ParticleEffect();
	~ParticleEffect();
	void createSpawnPoint(vector3 target, vector3 maxDistance,vector4 color, int maxPixels);
	void changeColor(vector4 color);
	void updateWithTarget(vector3 currentTarget);
	void draw();
	void turnOff();
	void pushOutMovement(vector3 Start, vector3 maxDistance, vector4 color, int maxPixels);
};

