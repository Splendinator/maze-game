#pragma comment(lib, "nclgl.lib")

#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Entity.h"

Window window = Window("My First OpenGL 3 Triangle!", 800, 600, false);
Renderer renderer = Renderer(window);
Camera c;





int shutDown() {
	return 0;
}


int gameLoop() {

	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.RenderScene();
	}

	return shutDown();
}


int startUp() {

	return gameLoop();

}


int main() {
	return startUp();
}



