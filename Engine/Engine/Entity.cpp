#include "Entity.h"
#include "Renderer.h"


Entity::Entity()
{
	mesh = nullptr;
}

Entity::Entity(Mesh *m, Renderer* r)
{
	mesh = m;
	renderer = r;
	r->addEntity(this);
}

Entity::~Entity()
{
	renderer->removeEntity(this);
}



void Entity::move(Vector3 p)
{
	modelMatrix = modelMatrix * Matrix4::Translation(p);
}

void Entity::rotate(Vector3 around, float deg)
{
	modelMatrix = modelMatrix * Matrix4::Rotation(deg,around);
}

void Entity::scale(Vector3 s)
{
	modelMatrix = modelMatrix * Matrix4::Scale(s);
}

void Entity::applyRenderer()
{
	renderer->addEntity(this);
}
