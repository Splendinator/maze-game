#pragma comment(lib, "nclgl.lib")

#include "Window.h"
#include "Renderer.h"

Window window;
Renderer renderer;



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
	window = Window("My First OpenGL 3 Triangle!", 800, 600, false);

	if (!window.HasInitialised()) {
		return -1;
	}

	renderer = Renderer(window);
	
	if (!renderer.HasInitialised()) {
		return -1;
	}

	return gameLoop();

}


int main() {
	return startUp();
}



