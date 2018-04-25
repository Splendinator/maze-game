#pragma once



#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include "OGLRenderer.h"
#include "Entity.h"
#include "EntityPlayer.h"
#include "GL/glut.h"	//Print text on screen.
#include <vector>

#include "ft2build.h"
#include FT_FREETYPE_H

class Renderer : public OGLRenderer {
protected:
	EntityPlayer *player;
	vector<Entity *> entities;

	float scale;
	float rotation;
	Vector3 position;

	FT_Library library;
	FT_Face font;
	int error;

	const static int UI_FONT_PIXELS = 10;
	const static int LETTER_GAP_PIXELS = 0;
	const static int UI_WIDTH = 400;
	const static int UI_HEIGHT = 225;

	GLuint texID;
	float *color;

	Mesh *ui = Mesh::GenerateCube();



public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	void drawText(string s, int x, int y, Vector3 colour);
	void clearUI() { 
		memset(color, 0, sizeof(float) * UI_WIDTH*UI_HEIGHT * 4);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, UI_WIDTH, UI_HEIGHT, 0, GL_RGBA, GL_FLOAT, color);
	};

	inline void SetScale(float s) { scale = s; }
	inline void SetRotation(float r) { rotation = r; }
	inline void SetPosition(Vector3 p) { position = p; }

	void setPlayer(EntityPlayer *player) { this->player = player; }
	void addEntity(Entity *e) { entities.push_back(e); }
	void removeEntity(Entity *e) {
		cout << entities.size() << endl;
		cout << "DELETING ENTITY " << e << endl;
		for (vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
			if (*it == e) {   entities.erase(it); break; };
		}
		cout << entities.size() << endl;
	}

	
};
