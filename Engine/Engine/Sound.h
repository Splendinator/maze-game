#pragma once

#include "fmod.hpp"
#include <iostream>


class Sound
{
private:
	FMOD::System *s;
	FMOD::Sound *footstep;
	FMOD::Sound *roar;
	FMOD::Channel *c = 0;
	FMOD_RESULT r;

public:
	Sound();

	void playFootsteps(bool b);

	~Sound();
};

