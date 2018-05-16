#pragma once

#include <vector>
#include "Renderer.h"
#include <chrono>

enum state { WANDER,CHASE, DEAD};

class EntityAI
	: public EntityPhysics
{
public:

	float health;
	int state;
	chrono::high_resolution_clock::time_point jumpTimer = chrono::high_resolution_clock::now();


	std::vector<Vector3> *moves;

	EntityAI();
	EntityAI(Mesh *mesh, Renderer *r, rp3d::DynamicsWorld * world, rp3d::ConvexShape *collisionShape);
	~EntityAI();
};

