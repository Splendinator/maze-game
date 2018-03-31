#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3?
#include "EntityPlayer.h"

EntityPlayer::EntityPlayer()
{

}

EntityPlayer::EntityPlayer(Mesh *mesh, Renderer *r, rp3d::DynamicsWorld * world, rp3d::ConvexShape *collisionShape, Vector3 cameraOffset)
	:EntityPhysics(mesh,r,world,collisionShape)
{
	offset = cameraOffset;
}


EntityPlayer::~EntityPlayer()
{
}


//void EntityPlayer::move(Vector3 p)
//{
//	camera.SetPosition(camera.GetPosition() + p);
//	modelMatrix = modelMatrix * Matrix4::Translation(p);
//}
//
//void EntityPlayer::rotate(Vector3 around, float deg)
//{
//	modelMatrix = modelMatrix * Matrix4::Rotation(deg, around);
//}
//
//void EntityPlayer::scale(Vector3 s)
//{
//	modelMatrix = modelMatrix * Matrix4::Scale(s);
//}