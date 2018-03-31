#pragma comment(lib, "reactphysics3d.lib")
#pragma comment(lib, "nclgl.lib")

#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include "EntityPlayer.h"
#include "IO.h"
#include "Bin.h"
#include "Window.h"
#include "Renderer.h"


Window window = Window("My First OpenGL 3 Triangle!", 800, 600, false);
Renderer renderer = Renderer(window);
Camera c;

Mesh *cubeMesh = Mesh::GenerateCube();
rp3d::CylinderShape *playerCollider = new rp3d::CylinderShape(1,1);
rp3d::BoxShape *wallCollider = new rp3d::BoxShape(rp3d::Vector3(1, 1, 1));
rp3d::BoxShape *groundCollider = new rp3d::BoxShape(rp3d::Vector3(100, 20, 100));

// Create the dynamics world 
rp3d::DynamicsWorld world(rp3d::Vector3(0.0, -9.81, 0.0));

EntityPlayer player = EntityPlayer(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)playerCollider,Vector3(0,2,0));
EntityPhysics ground = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)groundCollider);
EntityPhysics wall = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)wallCollider);
EntityPhysics wall2 = EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)wallCollider);


Bin<EntityPhysics> wallBin = Bin<EntityPhysics>(sizeof(EntityPhysics),10000);


int shutDown() {
	return 0;
}


int gameLoop() {

	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.RenderScene();
		world.update(0.008f);
		

		//*** TEMP INPUT SYSTEM ***
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			player.body->applyForceToCenterOfMass(rp3d::Vector3(0, 0, -600));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			player.body->applyForceToCenterOfMass(rp3d::Vector3(-600, 0, 0));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			player.body->applyForceToCenterOfMass(rp3d::Vector3(0, 0, 600));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			player.body->applyForceToCenterOfMass(rp3d::Vector3(600, 0, 0));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			if (player.body->getLinearVelocity().y < 0.001) { player.body->applyForceToCenterOfMass(rp3d::Vector3(0, 12000, 0)); }
		}
		
		if (sqrt(player.body->getLinearVelocity().x * player.body->getLinearVelocity().x + player.body->getLinearVelocity().z * player.body->getLinearVelocity().z) > 5) {
			cout << "TOO FAST";
			player.body->setLinearVelocity(rp3d::Vector3(player.body->getLinearVelocity().x/2, player.body->getLinearVelocity().y, player.body->getLinearVelocity().z/2));
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
	ground.body->setType(rp3d::STATIC);

	//cube2.move(Vector3(0, 1.5, 0));
	wall.scale(Vector3(1, 1, 1));
	wall.move(Vector3(0, 4, -10));
	wall2.move(Vector3(0, 1, -10));
	//ground.move(Vector3(0, -8, 0));
	ground.move(Vector3(0, -20, -10));



	player.body->setAngularDamping(1);	//Player can't rotate at all.
	rp3d::Material m = player.body->getMaterial();
	m.setFrictionCoefficient(5);	//Doesn't slide around
	m.setBounciness(0);	//Doesn't bounce
	player.body->setMaterial(m);





	renderer.setPlayer(&player);

	world.enableSleeping(false);
	//cout << wallBin.getVector().size();

	// Body
	//body = world.createRigidBody(rp3d::Transform(rp3d::Vector3(0,0,0),rp3d::Quaternion()));

	// Floor
	//floorCollider = new rp3d::BoxShape(rp3d::Vector3(1000, 2, 1000));

	
	//IO::genMaze(&wallBin,EntityPhysics(cubeMesh, &renderer, &world, (rp3d::ConvexShape *)wallCollider), 1337);

	
	return gameLoop();

}


int main() {
	return startUp();
}



