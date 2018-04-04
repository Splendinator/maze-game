#include "Renderer.h"




Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{

	currentShader = new Shader("../../Shaders/TexturedVertex.glsl",
		"../../Shaders/TexturedFragment.glsl");

	if(!currentShader->LinkProgram()) {
		return;
	}

	projMatrix = Matrix4::Perspective(1.0f, 100000.0f,
		(float)width / (float)height, 55.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);



	init = true;
}
Renderer::~Renderer(void)	{
	
}


void Renderer::RenderScene()
{
	glClearDepth(1.0f);
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glUseProgram(currentShader->GetProgram());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	viewMatrix = player->getCamera().BuildViewMatrix();

	for (vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {


		modelMatrix = (**it).getModelMatrix();
		

		UpdateShaderMatrices();
		(**it).getMesh()->Draw();
	}

	
	

	glUseProgram(0);

	SwapBuffers();	
}

