#pragma once
#include <vector>
#include "entity.h"

class IO
{
public:
	IO();

	static vector<Entity> readMap(string filename);

	~IO();
};

