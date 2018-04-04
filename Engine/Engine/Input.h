#pragma once
#include "reactphysics3d.h"
#include "EntityPlayer.h"

class callback : public rp3d::RaycastCallback
{
	public:
	bool collided = false;
	rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo &raycastInfo) {
		collided = true;
		return 0; //Stop raycast after first hit
	}
};

class Input
{
public:
	Input(rp3d::DynamicsWorld *world, EntityPlayer *player);
	~Input();

	void handleInput(float timeStep);

private:
	EntityPlayer *p;
	rp3d::DynamicsWorld *w;

	const float MOVEMENT_SPEED = 400;
	const float MAX_SPEED = 40;
	const float AIR_MULTIPLIER = 0.1;
	const float SENSITIVITY = 5;
	const float ON_FLOOR_THRESHOLD = 3.8;
	const float JUMP_HEIGHT = 400;
};

