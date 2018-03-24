#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "reactphysics3d.lib")

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3?
#include "Window.h"
#include "Renderer.h"
#include "EntityPhysics.h"

Window window = Window("My First OpenGL 3 Triangle!", 800, 600, false);
Renderer renderer = Renderer(window);
Camera c;

Mesh *cubeMesh = Mesh::GenerateCube();
rp3d::BoxShape *cubeCollider = new rp3d::BoxShape(rp3d::Vector3(1, 1, 1));
rp3d::BoxShape *groundCollider = new rp3d::BoxShape(rp3d::Vector3(100, 6, 100));

// Create the dynamics world 
rp3d::DynamicsWorld world(rp3d::Vector3(0.0, -9.81, 0.0));

EntityPlayer player;
EntityPhysics ground;
EntityPhysics cube = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)cubeCollider);
EntityPhysics cube2;



int shutDown() {
	return 0;
}


int gameLoop() {

	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.RenderScene();
		world.update(0.008f);

		//*** TEMP INPUT SYSTEM ***
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
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
			cube.move(Vector3(0, 0.2, 0));
		}
		//*************************
	}

	return shutDown();
}

int startUp() {
	
	// Change the number of iterations of the velocity solver 
	world.setNbIterationsVelocitySolver(15);

	// Change the number of iterations of the position solver 
	world.setNbIterationsPositionSolver(8);

	cubeMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/brick.jpg",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));


	//cube = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)cubeCollider);
	//cube2 = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)cubeCollider);
	//ground = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)groundCollider);
	//ground.scale(Vector3(0, 0, 0));
	//ground.body->setType(rp3d::STATIC);

	//cube2.move(Vector3(0, 1.5, 0));
	cube.move(Vector3(0, 0, -10));
	//ground.move(Vector3(0, -8, 0));

	renderer.setPlayer(&player);
	

	// Body
	//body = world.createRigidBody(rp3d::Transform(rp3d::Vector3(0,0,0),rp3d::Quaternion()));

	// Floor
	//floorCollider = new rp3d::BoxShape(rp3d::Vector3(1000, 2, 1000));




	
	return gameLoop();

}


int main() {
	return startUp();
}



