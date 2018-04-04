#include "Input.h"




Input::Input(rp3d::DynamicsWorld * world, EntityPlayer * player)
{
	p = player;
	w = world;
}

Input::~Input()
{
}

void Input::handleInput(float timeStep)
{

	rp3d::Vector3 direction = rp3d::Vector3(-sin(p->getCamera().GetYaw() / 360 * 2 * PI), 0, -cos(p->getCamera().GetYaw() / 360 * 2 * PI));
	callback c;
	w->raycast(rp3d::Ray(p->body->getTransform().getPosition(),
		p->body->getTransform().getPosition() + rp3d::Vector3(0,-ON_FLOOR_THRESHOLD,0)),&c);
	bool inAir = c.collided;

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() + 
			direction * MOVEMENT_SPEED * timeStep);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(direction.z, direction.y, -direction.x) * MOVEMENT_SPEED * timeStep);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(-direction.x, direction.y, -direction.z) * MOVEMENT_SPEED * timeStep);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		p->body->setLinearVelocity(p->body->getLinearVelocity() +
			rp3d::Vector3(-direction.z, direction.y, direction.x) * MOVEMENT_SPEED * timeStep);
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		if (inAir) {
			p->body->setLinearVelocity(p->body->getLinearVelocity() +
				rp3d::Vector3(0, JUMP_HEIGHT, 0) * timeStep);
		}
	}
	p->getCamera().SetPitch(p->getCamera().GetPitch() - Window::GetMouse()->GetRelativePosition().y * SENSITIVITY);
	p->getCamera().SetYaw(p->getCamera().GetYaw() - Window::GetMouse()->GetRelativePosition().x * SENSITIVITY);
	
	float hVelocity = sqrt(p->body->getLinearVelocity().x * p->body->getLinearVelocity().x + p->body->getLinearVelocity().z * p->body->getLinearVelocity().z);
	if (hVelocity > MAX_SPEED) {
		p->body->setLinearVelocity(rp3d::Vector3(p->body->getLinearVelocity().x * (MAX_SPEED / hVelocity), p->body->getLinearVelocity().y, p->body->getLinearVelocity().z * (MAX_SPEED / hVelocity)));
	}
	//*************************

}
