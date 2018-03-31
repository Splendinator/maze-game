#pragma once

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include "OGLRenderer.h"
#include "Entity.h"
#include "EntityPlayer.h"
#include <vector>


class Renderer : public OGLRenderer {
protected:
	EntityPlayer *player;
	vector<Entity *> entities;

	float scale;
	float rotation;
	Vector3 position;

public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();

	inline void SetScale(float s) { scale = s; }
	inline void SetRotation(float r) { rotation = r; }
	inline void SetPosition(Vector3 p) { position = p; }

	void setPlayer(EntityPlayer *player) { this->player = player; }
	void addEntity(Entity *e) { entities.push_back(e); }
	void removeEntity(Entity *e) {
		for (vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
			if (*it == e) { entities.erase(it); break; };
		}
	}


	
};
