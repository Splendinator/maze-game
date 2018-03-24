#pragma once

#include "Entity.h"
#include "Camera.h"

class EntityPlayer : public Entity
{

private: 
	Camera camera;

public:
	EntityPlayer();
	EntityPlayer(Mesh *, Renderer *);
	~EntityPlayer();


	void move(Vector3);
	void rotate(Vector3 around, float deg);
	void scale(Vector3);

	Camera getCamera() { return camera; };
};

