#include "EntityAI.h"



EntityAI::EntityAI()
{
	moves = new vector<Vector3>;
}



EntityAI::EntityAI(Mesh * mesh, Renderer * r, rp3d::DynamicsWorld * world, rp3d::ConvexShape * collisionShape)
	:EntityPhysics(mesh, r, world, collisionShape)
{
}

EntityAI::~EntityAI()
{
	delete moves;
}
