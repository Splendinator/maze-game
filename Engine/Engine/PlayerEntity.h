#pragma once
#include "Entity.h"
#include "Camera.h"

class PlayerEntity : public Entity
{

private: 
	Camera camera;

public:
	PlayerEntity();
	PlayerEntity(Mesh *);
	~PlayerEntity();


	void move(Vector3);
	void rotate(Vector3 around, float deg);
	void scale(Vector3);

	Camera getCamera() { return camera; };
};

