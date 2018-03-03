#include "Renderer.h"
#include "Camera.h"



Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	triangle = Mesh::GenerateCube();

	triangle1 = Entity(triangle);
	triangle2 = Entity(triangle);

	triangle1.scale(Vector3(1, 1, 1));


	currentShader = new Shader("../../Shaders/TexturedVertex.glsl",
		"../../Shaders/TexturedFragment.glsl");

	if(!currentShader->LinkProgram()) {
		return;
	}

	projMatrix = Matrix4::Perspective(1.0f, 100000.0f,
		(float)width / (float)height, 55.0f);

	
	
	

	init = true;
}
Renderer::~Renderer(void)	{
	delete triangle;
}


void Renderer::RenderScene()	{
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	

	glUseProgram(currentShader->GetProgram());


	//*** TEMP INPUT SUBSYSTEM ***

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		player.move(Vector3(0, 0, -0.1));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		player.move(Vector3(-0.1, 0, 0));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		player.move(Vector3(0, 0, 0.1));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		player.move(Vector3(0.1, 0, 0));
	}

	//****************************
	

	viewMatrix = player.getCamera().BuildViewMatrix();

	modelMatrix = triangle1.getModelMatrix();

	UpdateShaderMatrices();

	triangle1.getMesh()->Draw();

	modelMatrix = triangle2.getModelMatrix();
	UpdateShaderMatrices();
	
	triangle2.getMesh()->Draw();

	glUseProgram(0);

	SwapBuffers();	
}

