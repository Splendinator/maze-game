#pragma comment(lib, "reactphysics3d.lib")
#pragma comment(lib, "nclgl.lib")

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include "EntityPlayer.h"
#include "IO.h"
#include "Bin.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include <chrono>

//Timer
const float PHYSICS_DELTA = 0.008; //Time in seconds between each physics calculation.
std::chrono::duration<int, std::ratio<1, 1000000>> timeStep = std::chrono::duration<int, std::ratio<1, 1000000>>((int)(PHYSICS_DELTA*1000000));

//Renderer
Window window = Window("My First OpenGL 3 Triangle!", 1600, 900, false);
Renderer renderer = Renderer(window);

//Meshes
Mesh *wallMesh = Mesh::GenerateCube();
Mesh *groundMesh = Mesh::GenerateCube();

//Collision Shapes
rp3d::CapsuleShape *playerCollider = new rp3d::CapsuleShape(2,3);
rp3d::BoxShape *wallCollider = new rp3d::BoxShape(rp3d::Vector3(12, 12, 12));
rp3d::BoxShape *groundCollider = new rp3d::BoxShape(rp3d::Vector3(1000, 20, 1000));
rp3d::BoxShape *cubeCollider = new rp3d::BoxShape(rp3d::Vector3(2, 2, 2));

//Create the dynamics world 
rp3d::DynamicsWorld *world = new rp3d::DynamicsWorld(rp3d::Vector3(0.0, -70, 0.0));


EntityPlayer player = EntityPlayer(wallMesh, &renderer, world, (rp3d::ConvexShape *)playerCollider,Vector3(0,1,0));
EntityPhysics ground = EntityPhysics(groundMesh, &renderer, world, (rp3d::ConvexShape *)groundCollider);


//Input subsystem
Input input = Input(&renderer, world, &player);

//Array for maze walls
Bin<EntityPhysics> wallBin = Bin<EntityPhysics>(sizeof(EntityPhysics),10000);


int shutDown() {

	delete playerCollider;
	delete wallCollider;
	delete groundCollider;
	delete cubeCollider;
	
	return 0;
}


int gameLoop() {

	chrono::high_resolution_clock::time_point physTime = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::time_point inputTime = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::time_point currTime = chrono::high_resolution_clock::now();

	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		
		//Physics update
		currTime = chrono::high_resolution_clock::now();
		while (physTime < currTime) {
			world->update(PHYSICS_DELTA);
			player.body->setTransform(rp3d::Transform(player.body->getTransform().getPosition(), rp3d::Quaternion(0, 0, 0, 1))); //For some reason setting "angular dampening" over 1.0 causes reactPhysics3d to crash (even though documentation says it's fine); so this tacky line of code is needed to stop player rotation.
			physTime += timeStep;
		}

		//Renderer update
		renderer.RenderScene();
	
		//Input system
		currTime = chrono::high_resolution_clock::now();
		input.handleInput((float)(((currTime - inputTime).count()) * chrono::high_resolution_clock::period().num) / chrono::high_resolution_clock::period().den);
		inputTime = currTime;
		

	}

	return shutDown();
}

int startUp() {

	// Change the number of iterations of the velocity solver 
	world->setNbIterationsVelocitySolver(15);

	// Change the number of iterations of the position solver 
	world->setNbIterationsPositionSolver(8);

	wallMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/brick.jpg",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	groundMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/orange.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	

	//PLAYER PHYSICS SETUP
	player.body->setAngularDamping(1);	//Player can't rotate at all
	player.body->setMass(150);
	rp3d::Material m = player.body->getMaterial();
	m.setFrictionCoefficient(0.2);	//Doesn't slide around
	m.setBounciness(0);	//Doesn't bounce
	player.body->setMaterial(m);
	player.scale(Vector3(1, 1, 1));
	player.move(Vector3(22, 10, -15));

	//GROUND PHYSICS SETUP
	ground.scale(Vector3(405, 20, 405));
	ground.body->setType(rp3d::STATIC);
	ground.move(Vector3(405, -20, -405));
	m = ground.body->getMaterial();
	m.setFrictionCoefficient(100000000); //Don't want the player sliding everywhere; floor should be sticky.
	m.setBounciness(0);	//Not bouncy
	ground.body->setMaterial(m);

	//MAZE GENERATION
	EntityPhysics *wall = new EntityPhysics(wallMesh, &renderer, world, (rp3d::ConvexShape *)wallCollider);
	wall->scale(Vector3(12, 12, 12));
	m = wall->body->getMaterial();
	m.setBounciness(0); //Brick Walls aren't bouncy
	m.setFrictionCoefficient(0); //Or particularly slidey.
	wall->body->setMaterial(m);
	IO::genMaze(&wallBin, *wall, chrono::system_clock::now().time_since_epoch().count());
	delete wall;

	renderer.setPlayer(&player);	//Let renderer know which player (camera) to use.

	world->enableSleeping(true);


	return gameLoop();
}


int main() {
	return startUp();
}



