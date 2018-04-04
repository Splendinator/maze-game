#pragma once

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
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

	Mesh *getMesh() const { return mesh; }
	virtual Matrix4 getModelMatrix() { return modelMatrix; }

	virtual void applySubSystems() { applyRenderer(); }

private:
	Mesh *mesh; //Mesh used.

	vector<Entity *>::iterator rendererIndex; //Index of mesh in renderer.

	

protected:
	Renderer *renderer;	//Renderer used.
	Matrix4 modelMatrix; //Model matrix
	
	void applyRenderer();
};

