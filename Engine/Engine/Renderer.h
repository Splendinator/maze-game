#pragma once

#include "OGLRenderer.h"
#include "Entity.h"
#include "PlayerEntity.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();

	inline void SetScale(float s) { scale = s; }
	inline void SetRotation(float r) { rotation = r; }
	inline void SetPosition(Vector3 p) { position = p; }

	Entity triangle1;
	Entity triangle2;
	PlayerEntity player;

protected:
	Mesh * triangle;



	float scale;
	float rotation;
	Vector3 position;
};
