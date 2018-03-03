#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "reactphysics3d.lib")

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3?
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"

Window window = Window("My First OpenGL 3 Triangle!", 800, 600, false);
Renderer renderer = Renderer(window);
Camera c;

rp3d::CollisionWorld world;
// Initial position and orientation of the collision body 
rp3d::Vector3 initPosition(0.0, 3.0, 0.0);
rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
rp3d::Transform initTransform(initPosition, initOrientation);

// Create a collision body in the world 
rp3d::CollisionBody* body;





int shutDown() {
	return 0;
}


int gameLoop() {

	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.RenderScene();
		std::cout << body->getTransform().getPosition().x << body->getTransform().getPosition().y << body->getTransform().getPosition().z << std::endl;
	}

	return shutDown();
}


int startUp() {
	body = world.createCollisionBody(initTransform);
	return gameLoop();

}


int main() {
	return startUp();
}



