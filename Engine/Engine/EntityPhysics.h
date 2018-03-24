#pragma once

#include "reactphysics3d.h"
#include "Entity.h"
#include "Mesh.h"


class EntityPhysics : public Entity
{
public:

	rp3d::RigidBody *body;

	EntityPhysics();
	EntityPhysics(Mesh *mesh, Renderer *r, rp3d::DynamicsWorld * world, rp3d::ConvexShape *collisionShape);
	~EntityPhysics();

	virtual Matrix4 getModelMatrix();

	void move(Vector3);
	void rotate(Vector3 around, float deg);
	void scale(Vector3);



private:
	
	rp3d::DynamicsWorld *world;
	rp3d::ConvexShape *collisionShape;
	rp3d::Transform transform;

	Vector3 meshScale;
};

