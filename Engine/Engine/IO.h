#pragma once
#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include <vector>
#include <random>
#include "EntityPhysics.h"
#include "Bin.h"

enum direction {NORTH,EAST,SOUTH,WEST};

struct node {
	bool n = true, e = true, s = true, w = true;
};

//Maze gen constants.
const static int MAP_SIZE = 27;	//Has to be odd;
const int nodes = (MAP_SIZE - 1) / 2;	//Nodes needed;
const static int AROUND_CHANCE = 2;	//Chance to go around the ring;
const static int INWARD_CHANCE = 1; //Chance to go inward to the next ring;

class IO
{
public:
	IO();

	static vector<Entity> readMap(string filename);

	
	static void genMaze(Bin<EntityPhysics> *bin, EntityPhysics e, unsigned int seed);

	~IO();
};

