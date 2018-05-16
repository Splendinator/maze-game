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
	body->addCollisionShape(collisionShape, rp3d::Transform(v, q), 20);

	meshScale = Vector3(1, 1, 1);

}



EntityPhysics::~EntityPhysics()
{
	world->destroyRigidBody(body);
}

Matrix4 EntityPhysics::getModelMatrix()
{
	Matrix4 m4;
	
	float matrix[16] = {};
	body->getTransform().getOpenGLMatrix(matrix);

	return (Matrix4)matrix * Matrix4::Scale(meshScale);
}


void EntityPhysics::move(Vector3 p)
{
	rp3d::Vector3 v = body->getTransform().getPosition();

	body->setTransform(rp3d::Transform(rp3d::Vector3(v.x + p.x, v.y + p.y, v.z + p.z), body->getTransform().getOrientation()));
}

void EntityPhysics::rotate(Vector3 around, float deg)
{
	rp3d::Quaternion q = body->getTransform().getOrientation();
	body->setTransform(rp3d::Transform(body->getTransform().getPosition(), rp3d::Quaternion(deg, rp3d::Vector3(around.x, around.y, around.z)) + q));
}

void EntityPhysics::scale(Vector3 s)
{
	meshScale = s;
	collisionShape->setLocalScaling(*(rp3d::Vector3*)&s);
}

void EntityPhysics::lookAt(Vector3 ve)
{

	Vector2 v = Vector2(ve.x - body->getTransform().getPosition().x, ve.z - body->getTransform().getPosition().z);

	if (ve.x - body->getTransform().getPosition().x == 0 && ve.z - body->getTransform().getPosition().z == 0) return;

	
	float angle = atan(v.x / v.y);

	angle += PI;

	if (v.y < 0) angle += PI;

	if (angle < 0) angle += 2*PI;

	//cout << "Angle: " << angle << endl;


	rp3d::Quaternion q = rp3d::Quaternion(rp3d::Vector3(0, angle, 0));

	body->setTransform(rp3d::Transform(body->getTransform().getPosition(), q));

}

rp3d::Vector3 EntityPhysics::foward() {
	return body->getTransform().getOrientation() * rp3d::Vector3(0, 0, -1);
}


