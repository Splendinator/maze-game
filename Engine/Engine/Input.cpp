#include "Input.h"




Input::Input(Renderer *renderer, rp3d::DynamicsWorld * world, EntityPlayer * player)
{
	p = player;
	w = world;
	r = renderer;
	bullet = new EntityPhysics(m, r, w, s);

}

Input::~Input()
{
	delete s;
}

void Input::handleInput(float timeStep)
{
	timeElapsed += timeStep;

	if (p->getCamera().GetPitch() > MAX_PITCH) p->getCamera().SetPitch(MAX_PITCH);
	if (p->getCamera().GetPitch() < MIN_PITCH) p->getCamera().SetPitch(MIN_PITCH);

	rp3d::Vector3 direction = rp3d::Vector3(-sin(p->getCamera().GetYaw() / 360 * 2 * PI), 0, -cos(p->getCamera().GetYaw() / 360 * 2 * PI));
	rp3d::Vector3 aiming = (direction * (1 - abs(p->getCamera().GetPitch()) / 90) + rp3d::Vector3(0, p->getCamera().GetPitch() / 90, 0)).getUnit();

	callback c;
	w->raycast(rp3d::Ray(p->body->getTransform().getPosition(),
		p->body->getTransform().getPosition() + rp3d::Vector3(0, -ON_FLOOR_THRESHOLD, 0)), &c);
	bool onFloor = c.collided;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			direction * MOVEMENT_SPEED * timeStep * (1 - !onFloor * IN_AIR_SLOWDOWN));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(direction.z, direction.y, -direction.x) * MOVEMENT_SPEED * timeStep * (1 - !onFloor * IN_AIR_SLOWDOWN));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(-direction.x, direction.y, -direction.z) * MOVEMENT_SPEED * timeStep * (1 - !onFloor * IN_AIR_SLOWDOWN));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(-direction.z, direction.y, direction.x) * MOVEMENT_SPEED * timeStep * (1 - !onFloor * IN_AIR_SLOWDOWN));
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE) && !Window::GetKeyboard()->KeyHeld(KEYBOARD_SPACE)) {
		if (onFloor) {
			p->body->setLinearVelocity(p->body->getLinearVelocity() +
				rp3d::Vector3(0, JUMP_HEIGHT, 0));
		}
	}

	if (Window::GetMouse()->ButtonDown(MOUSE_LEFT) && !Window::GetMouse()->ButtonHeld(MOUSE_LEFT)) {
		EntityPhysics *temp = bullets.add(bullet);
		temp->applySubSystems();

		//aiming.y += 0.01f; //Slight upwards momentum to compensate for gravity;
		rp3d::Vector3 bulletSpawn = *(rp3d::Vector3 *)&p->getCamera().GetPosition() + aiming * BULLET_SPAWN_DIST;
		
		temp->move(Vector3(bulletSpawn.x, bulletSpawn.y, bulletSpawn.z));
		temp->body->applyForceToCenterOfMass(aiming * BULLET_SHOOT_FORCE);
		BulletLifeSpan b;
		b.bullet = temp;
		b.expiryDate = timeElapsed + BULLET_LIFESPAN;
		bulletsAlive.push_back(b);
	}

	for (vector<BulletLifeSpan>::iterator it = bulletsAlive.begin(); it != bulletsAlive.end(); ++it){
		
		
		if (it->expiryDate < timeElapsed) {
			
			bullets.remove(it->bullet);
			bulletsAlive.erase(it);
			break;
		}
		colCallback c;
		w->testCollision(it->bullet->body, &c);
		if (c.collided) {
			bullets.remove(it->bullet);
			bulletsAlive.erase(it);
			break;
		}
	}

	p->getCamera().SetPitch(p->getCamera().GetPitch() - Window::GetMouse()->GetRelativePosition().y * SENSITIVITY);
	p->getCamera().SetYaw(p->getCamera().GetYaw() - Window::GetMouse()->GetRelativePosition().x * SENSITIVITY);
	
	float hVelocity = sqrt(p->body->getLinearVelocity().x * p->body->getLinearVelocity().x + p->body->getLinearVelocity().z * p->body->getLinearVelocity().z);
	if (hVelocity > MAX_SPEED) {
		p->body->setLinearVelocity(rp3d::Vector3(p->body->getLinearVelocity().x * (MAX_SPEED / hVelocity), p->body->getLinearVelocity().y, p->body->getLinearVelocity().z * (MAX_SPEED / hVelocity)));
	}

	//Sound
	sound.playFootsteps(p->body->getLinearVelocity().length() < 20.f || !onFloor );

}
