#pragma once

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3?
#include "EntityPhysics.h"
#include "Camera.h"

class EntityPlayer : public EntityPhysics
{

private: 
	Camera camera;
	Vector3 offset;

public:
	EntityPlayer();
	EntityPlayer(Mesh *mesh, Renderer *r, rp3d::DynamicsWorld * world, rp3d::ConvexShape *collisionShape, Vector3 camreaOffset);
	~EntityPlayer();


	//void move(Vector3);
	//void rotate(Vector3 around, float deg);
	//void scale(Vector3);

	Camera getCamera() { 
		camera.SetPosition(Vector3(
			body->getTransform().getPosition().x,
			body->getTransform().getPosition().y, 
			body->getTransform().getPosition().z) + offset);
		return camera;
	};
};

