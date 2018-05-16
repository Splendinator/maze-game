#pragma comment(lib, "reactphysics3d.lib")
#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "freetyped.lib")


#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include "EntityPlayer.h"
#include "EntityAI.h"
#include "IO.h"
#include "Bin.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Sound.h"
#include <chrono>

//Timer
const float PHYSICS_DELTA = 0.008; //Time in seconds between each physics calculation.
std::chrono::duration<int, std::ratio<1, 1000000>> timeStep = std::chrono::duration<int, std::ratio<1, 1000000>>((int)(PHYSICS_DELTA*1000000));
std::chrono::duration<int, std::ratio<1, 1000000>> debugTimeStep = std::chrono::duration<int, std::ratio<1, 1000000>>((int)(0.2 * 1000000));

//Renderer
Window window = Window("Game!", 1920, 1080, false);
Renderer renderer = Renderer(window);

//Meshes
Mesh *wallMesh = Mesh::GenerateCube();
Mesh *groundMesh = Mesh::GenerateCube();
Mesh *enemyHappyMesh = Mesh::GenerateEnemy();
Mesh *enemyAngryMesh = Mesh::GenerateEnemy();
Mesh *enemyDeadMesh = Mesh::GenerateEnemy();

//Collision Shapes
rp3d::CapsuleShape *playerCollider = new rp3d::CapsuleShape(2,3);
rp3d::BoxShape *wallCollider = new rp3d::BoxShape(rp3d::Vector3(1, 1, 1));
rp3d::BoxShape *groundCollider = new rp3d::BoxShape(rp3d::Vector3(2, 1, 2));
rp3d::BoxShape *cubeCollider = new rp3d::BoxShape(rp3d::Vector3(2, 2, 2));
//rp3d::BoxShape *enemyCollider = new rp3d::BoxShape(rp3d::Vector3(1, 1, 1));
rp3d::SphereShape *enemyCollider = new rp3d::SphereShape(1.41f);

//Create the dynamics world 
rp3d::DynamicsWorld *world = new rp3d::DynamicsWorld(rp3d::Vector3(0.0, -70, 0.0));


EntityPlayer player = EntityPlayer(wallMesh, &renderer, world, (rp3d::ConvexShape *)playerCollider,Vector3(0,1,0));
EntityAI pet = EntityAI(enemyHappyMesh, &renderer, world, (rp3d::ConvexShape *)enemyCollider);
EntityPhysics ground = EntityPhysics(groundMesh, &renderer, world, (rp3d::ConvexShape *)groundCollider);


//Input subsystem
Input input = Input(&renderer, world, &player);

//Array for maze walls
Bin<EntityPhysics> wallBin = Bin<EntityPhysics>(sizeof(EntityPhysics),1000);
Bin<EntityAI> enemyBin = Bin<EntityAI>(sizeof(EntityAI), 100);


//Pathing Map
Map *pathMap;

void restart() {
	enemyBin.empty();
	wallBin.empty();

	//MAZE GENERATION
	EntityPhysics *wall = new EntityPhysics(wallMesh, &renderer, world, (rp3d::ConvexShape *)wallCollider);
	wall->scale(Vector3(12, 12, 12));
	rp3d::Material m = wall->body->getMaterial();
	m.setBounciness(0); //Brick Walls aren't bouncy
	m.setFrictionCoefficient(0); //Or particularly slidey.
	wall->body->setMaterial(m);
	pathMap = IO::genMaze(&wallBin, &enemyBin, wall, &pet, chrono::system_clock::now().time_since_epoch().count());
	delete wall;

	player.body->setTransform(rp3d::Transform(rp3d::Vector3(24, 11, -24), rp3d::Quaternion(0, 0, 0, 1)));
	player.body->setLinearVelocity(rp3d::Vector3(0,0,0));




}

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
	chrono::high_resolution_clock::time_point debugTime = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::time_point currTime = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::time_point aiTime = chrono::high_resolution_clock::now();

	chrono::high_resolution_clock::time_point uiTimer = chrono::high_resolution_clock::now();

	bool debug = false;

	restart:
	while (window.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		
		//Input system
		currTime = chrono::high_resolution_clock::now();
		input.handleInput((float)(((currTime - inputTime).count()) * chrono::high_resolution_clock::period().num) / chrono::high_resolution_clock::period().den);
		inputTime = currTime;
		char inputS[30];
		sprintf(inputS, "Input: %dms", (chrono::high_resolution_clock::now() - currTime) / 10000);

	
		//Physics update
		currTime = chrono::high_resolution_clock::now();
		while (physTime < currTime) {
			world->update(PHYSICS_DELTA);
			player.body->setTransform(rp3d::Transform(player.body->getTransform().getPosition(), rp3d::Quaternion(0, rp3d::Vector3(0, 1, 0)))); //Stop rotation;
			physTime += timeStep;
		}
		char phys[30];
		sprintf(phys, "Physics: %dms", (chrono::high_resolution_clock::now() - currTime) / 10000);

		//Renderer update
		currTime = chrono::high_resolution_clock::now();
		renderer.RenderScene();
		char rend[30];
		sprintf(rend, "Rendering: %dms", (chrono::high_resolution_clock::now() - currTime) / 10000);

		
		//Debug
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F)) {
			debug = !debug;
			renderer.clearUI();
			renderer.drawCrosshair(Vector4(0,1,0,1),renderer.CROSSHAIR_DEFAULT);
		}
		if (debugTime < chrono::high_resolution_clock::now() && debug) {
			renderer.clearUI();
			renderer.drawText(phys, 5, 5, Vector3(0, 0.8, 0));
			renderer.drawText(rend, 5, 15, Vector3(0, 0.8, 0));
			renderer.drawText(inputS, 5, 25, Vector3(0, 0.8, 0));
			debugTime = chrono::high_resolution_clock::now() + debugTimeStep;
		}

		//UI
		if (uiTimer < chrono::high_resolution_clock::now()) {
			renderer.clearUI();
			renderer.drawCrosshair(Vector4(0,1,0,1), renderer.CROSSHAIR_DEFAULT);
			uiTimer = chrono::high_resolution_clock::now() + chrono::hours(24);
		}

		//AI Calculation
		
		

		rp3d::Vector3 temp;
		s:
		for (vector<EntityAI *>::iterator it = enemyBin.getVector()->begin(); it != enemyBin.getVector()->end(); ++it) {
			
			for (vector<BulletLifeSpan>::iterator bullet = input.bulletsAlive.begin(); bullet != input.bulletsAlive.end(); ++bullet) {
				if ((bullet->bullet->body->getTransform().getPosition() - (**it).body->getTransform().getPosition()).length() < 6.5f && (**it).state != DEAD) {
					(**it).state = DEAD;
					(**it).setMesh(enemyDeadMesh);
					(**it).body->setLinearVelocity(rp3d::Vector3(rand() % 11 - 5, rand() % 11 + 5, rand() % 11 - 5) * 5.f);
					(**it).body->setMass(50);
					input.bullets.remove(bullet->bullet);
					input.bulletsAlive.erase(bullet);
					goto s;
				}
			}

			(**it).body->setLinearVelocity((**it).body->getLinearVelocity() + rp3d::Vector3(0, min(45.f - (**it).body->getLinearVelocity().y,0),0));

			if ((**it).state != DEAD && (player.body->getTransform().getPosition() - (**it).body->getTransform().getPosition()).length() < 8.0f) {
				restart();
				renderer.drawText("Lose!", 900, 5, Vector3(1, 0, 0));
				uiTimer = chrono::high_resolution_clock::now() + chrono::seconds(5);
				goto restart;
			}
			
			

			//rp3d::Quaternion q = (*it)->body->getTransform().getOrientation();
			//q.x = 0;
			//q.z = 0;


			//Handle state
			callback c;
			world->raycast(rp3d::Ray((**it).body->getTransform().getPosition() + rp3d::Vector3(0, 4, 0), player.body->getTransform().getPosition() + rp3d::Vector3(0,4,0),1.f), &c);
			


				if (c.collided || (**it).foward().dot((player.body->getTransform().getPosition() - (**it).body->getTransform().getPosition()).getUnit()) < 0.7f) {	//In line of sight
					if ((**it).state == CHASE) {
						(**it).moves->clear();
						(**it).moves->push_back(*(Vector3 *)&player.body->getTransform().getPosition()); //Go to player's last known location;
						(**it).setMesh(enemyHappyMesh);
						(**it).state = WANDER;
					}
				
				}
				else
				{
					if ((**it).state == WANDER) {
						(**it).setMesh(enemyAngryMesh);
						(**it).state = CHASE;
					}
					
				}
			
			
			//w->raycast(rp3d::Ray(p->body->getTransform().getPosition(),
			//	p->body->getTransform().getPosition() + rp3d::Vector3(0, -ON_FLOOR_THRESHOLD, 0)), &c))

			if ((**it).state == WANDER) {
				if (!(**it).moves->empty()) {

					(**it).lookAt((**it).moves->front());
					
			
					temp = (*(rp3d::Vector3 *)&(**it).moves->front() - (**it).body->getTransform().getPosition());
					float pct = max(min((temp.length() - 12.f) / 24.f,1),0);

					//cout << temp.length() << " " << pct << " " << endl;

					//Pathing interpolation
					if ((**it).moves->size() >= 2) {
						
						//cout << *(Vector3 *)&(**it).body->getTransform().getPosition() << " " << (**it).moves->at(0) << " " << (**it).moves->at(1) << " " << pct << endl << ((**it).moves->at(1) + (((**it).moves->at(0) - (**it).moves->at(1)) * pct)) << endl;

						(**it).lookAt(((**it).moves->at(1) + (((**it).moves->at(0) - (**it).moves->at(1)) * pct)));

						temp = *(rp3d::Vector3 *) &((**it).moves->at(1) + (((**it).moves->at(0) - (**it).moves->at(1)) * (pct + 0.3f))) -  (**it).body->getTransform().getPosition();

						//cout << temp.length() << endl;

						//temp = *(rp3d::Vector3 *) &(((**it).moves->at(1) + (((**it).moves->at(0) - (**it).moves->at(1)) * pct)) - (**it).body->getTransform().getPosition());

						//temp = *(rp3d::Vector3 *)&(**it).moves->front() - (*(rp3d::Vector3 *) &((**it).moves->at(0)   + (((**it).moves->at(1) - (**it).moves->at(0)) * pct)));
						//temp = *(rp3d::Vector3 *)&(**it).moves->front() + (*(rp3d::Vector3 *)&(**it).moves[1] - *(rp3d::Vector3 *)&(**it).moves->front()) * pct;
						//temp = (temp - (**it).body->getTransform().getPosition());
					}

					//cout << (**it).moves->size() << endl;

					if (pct > 0.1f) {
						temp.y = 0;
						temp = temp.getUnit() * 20.f;
						(**it).body->setLinearVelocity(rp3d::Vector3(temp.x, (**it).body->getLinearVelocity().y, temp.z));
					}
					else {
						(**it).moves->erase((**it).moves->begin());
					}
				}
				else {
					Vector3 randVector = Vector3(((rand() % ((MAP_SIZE - 3) / 2)) * 2 + 1) * 24, 0, ((rand() % ((MAP_SIZE - 3) / 2)) * 2 + 1) * 24);
					pathMap->genRoute((**it), randVector);
				}
			}

			if ((**it).state == CHASE) {
				(**it).lookAt(*(Vector3 *)&player.body->getTransform().getPosition());
				temp = player.body->getTransform().getPosition() - (**it).body->getTransform().getPosition();
				if (temp.length() > 2.f) {
					temp.y = 0;
					temp = temp.getUnit() * 70.f;
					(**it).body->setLinearVelocity(rp3d::Vector3(temp.x, (**it).body->getLinearVelocity().y, temp.z));
				}
			}

			//Jump to prevent them getting stuck on each other
			if ((**it).state != DEAD && (**it).jumpTimer < chrono::high_resolution_clock::now()) {
				(**it).body->setLinearVelocity((**it).body->getLinearVelocity() + rp3d::Vector3(0, 45, 0));
				(**it).jumpTimer += chrono::milliseconds(rand() % 4000 + 1500);
			}

			

		}

		aiTime = chrono::high_resolution_clock::now();

		bool won = true;
		for (vector<EntityAI *>::iterator it = enemyBin.getVector()->begin(); it != enemyBin.getVector()->end(); ++it) {
			if ((**it).state != DEAD) {
				won = false;
				break;
			}
		}
		if (won) {
			restart();
			renderer.drawText("Win!", 900, 5, Vector3(0, 1, 0));
			uiTimer = chrono::high_resolution_clock::now() + chrono::seconds(5);
			goto restart;
		}

	}

	return shutDown();
}

int startUp() {

	//Window setup
	window.LockMouseToWindow(true);
	window.ShowOSPointer(false);

	// Change the number of iterations of the velocity solver 
	world->setNbIterationsVelocitySolver(15);

	// Change the number of iterations of the position solver 
	world->setNbIterationsPositionSolver(8);

	
	wallMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/brick.jpg",SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	groundMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/orange.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	enemyHappyMesh-> SetTexture(SOIL_load_OGL_texture("../../Textures/enemy.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	enemyAngryMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/angry.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	enemyDeadMesh->SetTexture(SOIL_load_OGL_texture("../../Textures/dead.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
	

	//PLAYER PHYSICS SETUP
	player.body->setAngularDamping(1);	//Player can't rotate at all
	player.body->setMass(150);
	rp3d::Material m = player.body->getMaterial();
	m.setFrictionCoefficient(0.8f);	//Doesn't slide around
	m.setBounciness(0);	//Doesn't bounce
	player.body->setMaterial(m);
	player.scale(Vector3(1, 1, 1));
	player.move(Vector3(22, 10, -15));

	//ENTITY AI
	pet.body->setMass(150);
	m = pet.body->getMaterial();
	m.setFrictionCoefficient(5.f);	//Doesn't slide around
	//m.setRollingResistance(INFINITY);
	m.setBounciness(0.5f);	//Doesn't bounce
	pet.body->setMaterial(m);
	pet.move(Vector3(-100, 10, 100));
	pet.scale(Vector3(2, 2, 2));
	pet.body->setAngularDamping(0.5f);
	pet.body->setLinearDamping(0.5f);

	//GROUND PHYSICS SETUP
	ground.scale(Vector3(405, 20, 405));
	ground.body->setType(rp3d::STATIC);
	ground.move(Vector3(405, -20, -405));
	m = ground.body->getMaterial();
	m.setFrictionCoefficient(3.0f); //Don't want the player sliding everywhere; floor should be sticky.
	m.setBounciness(0);	//Not bouncy
	ground.body->setMaterial(m);

	enemyBin.getVector()->clear();

	//MAZE GENERATION
	EntityPhysics *wall = new EntityPhysics(wallMesh, &renderer, world, (rp3d::ConvexShape *)wallCollider);
	wall->scale(Vector3(12, 12, 12));
	m = wall->body->getMaterial();
	m.setBounciness(0); //Brick Walls aren't bouncy
	m.setFrictionCoefficient(0); //Or particularly slidey.
	wall->body->setMaterial(m);
	pathMap = IO::genMaze(&wallBin, &enemyBin, wall, &pet, chrono::system_clock::now().time_since_epoch().count());
	delete wall;

	renderer.setPlayer(&player);	//Let renderer know which player (camera) to use.

	world->enableSleeping(true);

	renderer.drawCrosshair(Vector4(0,1,0,1),renderer.CROSSHAIR_DEFAULT);

	//cout << "SIZE: " << enemyBin.getVector()->size();


	return gameLoop();
}


int main() {
	int x = 2;
	while (x == 2) {
		x = startUp();
	}
	
}



