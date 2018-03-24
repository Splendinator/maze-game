#pragma once

#include "Mesh.h"
#include "Vector3.h"
#include "Matrix4.h"

class Renderer;

class Entity
{
public:
	Entity();
	Entity(Mesh *m, Renderer *r);
	~Entity();

	virtual void move(Vector3);
	virtual void rotate(Vector3 around, float deg);
	virtual void scale(Vector3);

	Mesh *getMesh() { return mesh; }
	virtual Matrix4 getModelMatrix() { return modelMatrix; }


private:
	Mesh *mesh; //Mesh used.

	Renderer *renderer;	//Renderer used.
	vector<Entity *>::iterator rendererIndex; //Index of mesh in renderer.

protected:
	Matrix4 modelMatrix; //Model matrix
	
	//Collision * col;
};

