#include "EntityPlayer.h"

EntityPlayer::EntityPlayer()
{

}

EntityPlayer::EntityPlayer(Mesh *mesh, Renderer *r) : Entity(mesh,r)
{

}


EntityPlayer::~EntityPlayer()
{
}


void EntityPlayer::move(Vector3 p)
{
	camera.SetPosition(camera.GetPosition() + p);
	modelMatrix = modelMatrix * Matrix4::Translation(p);
}

void EntityPlayer::rotate(Vector3 around, float deg)
{
	modelMatrix = modelMatrix * Matrix4::Rotation(deg, around);
}

void EntityPlayer::scale(Vector3 s)
{
	modelMatrix = modelMatrix * Matrix4::Scale(s);
}