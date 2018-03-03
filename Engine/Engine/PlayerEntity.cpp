#include "PlayerEntity.h"

PlayerEntity::PlayerEntity()
{

}

PlayerEntity::PlayerEntity(Mesh *mesh) : Entity(mesh)
{

}


PlayerEntity::~PlayerEntity()
{
}


void PlayerEntity::move(Vector3 p)
{
	camera.SetPosition(camera.GetPosition() + p);
	modelMatrix = modelMatrix * Matrix4::Translation(p);
	cout << camera.BuildViewMatrix();
}

void PlayerEntity::rotate(Vector3 around, float deg)
{
	modelMatrix = modelMatrix * Matrix4::Rotation(deg, around);
}

void PlayerEntity::scale(Vector3 s)
{
	modelMatrix = modelMatrix * Matrix4::Scale(s);
}