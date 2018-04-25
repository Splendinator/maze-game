#include "Sound.h"



Sound::Sound()
{
	FMOD::System_Create(&s);
	s->init(100, FMOD_INIT_NORMAL,0);
	s->set3DSettings(1, 1, 1);
	s->createSound("../../Sounds/playerfootsteps.wav", FMOD_3D, 0, &footstep);
	footstep->set3DMinMaxDistance(0, 200);
	footstep->setMode(FMOD_LOOP_NORMAL);
	s->playSound(footstep, 0, true, &c);
	c->setPaused(true);
	s->update();
	
}

void Sound::playFootsteps(bool b)
{
	c->setPaused(b);
}


Sound::~Sound()
{
}
