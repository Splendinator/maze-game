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
	
	
	

	init = true;
}
Renderer::~Renderer(void)	{
	
}


void Renderer::RenderScene()	{
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	

	glUseProgram(currentShader->GetProgram());
	

	viewMatrix = player->getCamera().BuildViewMatrix();

	for (vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {


		modelMatrix = (**it).getModelMatrix();
		

		UpdateShaderMatrices();
		(**it).getMesh()->Draw();
	}

	
	

	glUseProgram(0);

	SwapBuffers();	
}

