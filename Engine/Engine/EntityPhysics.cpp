#include "EntityPhysics.h"



EntityPhysics::EntityPhysics()
{

}

EntityPhysics::EntityPhysics(Mesh *mesh, Renderer *r, rp3d::DynamicsWorld *world, rp3d::ConvexShape *collisionShape) : Entity(mesh,r)
{
	this->world = world;
	this->collisionShape = collisionShape;
	
	rp3d::Quaternion q = rp3d::Quaternion::identity();

	rp3d::Vector3 v;
	v.setToZero();

	body = world->createRigidBody(rp3d::Transform(v,q));

	meshScale = Vector3(1, 1, 1);
}



EntityPhysics::~EntityPhysics()
{
	world->destroyRigidBody(body);
}

Matrix4 EntityPhysics::getModelMatrix()
{
	float matrix[16];
	body->getTransform().getOpenGLMatrix(matrix);

	return matrix;
}


void EntityPhysics::move(Vector3 p)
{
	rp3d::Vector3 v = body->getTransform().getPosition();

	body->setTransform(rp3d::Transform(rp3d::Vector3(v.x + p.x, v.y + p.y, v.z + p.z), body->getTransform().getOrientation()));
}

void EntityPhysics::rotate(Vector3 around, float deg)
{
	rp3d::Quaternion q = body->getTransform().getOrientation();
	body->setTransform(rp3d::Transform(body->getTransform().getPosition(), rp3d::Quaternion(around.x, around.y, around.z, deg) + q));
}

void EntityPhysics::scale(Vector3 s)
{
	meshScale = s;
}


