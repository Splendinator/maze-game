#pragma once
#include "reactphysics3d.h"
#include "Renderer.h"
#include "EntityPlayer.h"

#include "Bin.h"
#include "Sound.h"
#include <vector>

struct BulletLifeSpan {
	EntityPhysics *bullet;
	float expiryDate;
};

class callback : public rp3d::RaycastCallback
{
	public:
	bool collided = false;
	rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo &raycastInfo) {
		collided = true;
		return 0; //Stop raycast after first hit
	}
};

class colCallback : public rp3d::CollisionCallback
{
public:
	bool collided = false;
	void notifyContact(const rp3d::ContactPointInfo& contactPointInfo) {
		collided = true;
	}
};


class Input
{
public:
	Input(Renderer *r, rp3d::DynamicsWorld *world, EntityPlayer *player);
	~Input();

	void handleInput(float timeStep);

	//Vector of all currently alive bullets;
	vector<BulletLifeSpan> bulletsAlive;
	Bin<EntityPhysics> bullets = Bin<EntityPhysics>(sizeof(EntityPhysics), 100);

private:
	EntityPlayer *p;
	rp3d::DynamicsWorld *w;
	Renderer *r;



	//Bullet
	Mesh *m = Mesh::GenerateCube();
	rp3d::SphereShape *s = new rp3d::SphereShape(2.f);;
	EntityPhysics *bullet;


	//Time elapsed since program started
	float timeElapsed = 0;




	const float MOVEMENT_SPEED = 600;
	const float MAX_SPEED = 60; 
	const float AIR_MULTIPLIER = 0.1;
	const float SENSITIVITY = 1;
	const float ON_FLOOR_THRESHOLD = 3.8;
	const float JUMP_HEIGHT = 35; 
	const float BULLET_SPAWN_DIST = 10;
	const float BULLET_SHOOT_FORCE = 800000;
	const float IN_AIR_SLOWDOWN = 0.9;
	const float MAX_PITCH = 90;
	const float MIN_PITCH = -90;
	const float BULLET_LIFESPAN = 3;

	Sound sound;
	
};

