#pragma once

#include "reactphysics3d.h"
#include "Entity.h"
#include "Mesh.h"
#include "Bin.h"


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

	void applySubSystems() { applyRenderer(); applyPhysics(); }
	Vector3 getScale() const{ return meshScale; }

	void lookAt(Vector3 v);

	rp3d::Vector3 foward();

private:
	
	rp3d::DynamicsWorld *world;
	rp3d::ConvexShape *collisionShape;
	rp3d::Transform transform;
	
	Vector3 meshScale;
	Bin<EntityPhysics> *bulletsBin;

protected:

	void applyPhysics() { 
		rp3d::Quaternion q = rp3d::Quaternion::identity();
		rp3d::Vector3 v;
		v.setToZero();
		body = world->createRigidBody(rp3d::Transform(v,q));
		body->addCollisionShape(collisionShape, rp3d::Transform(v, q), 20);
	}
};

