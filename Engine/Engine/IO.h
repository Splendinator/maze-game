#pragma once
#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include <vector>
#include <random>
#include "EntityPhysics.h"
#include "Bin.h"
#include "Map.h"

enum direction {NORTH,EAST,SOUTH,WEST};

struct node {
	bool n = true, e = true, s = true, w = true;
};

//Maze gen constants.
const static int MAP_SIZE = 21;	//Has to be odd or ugly square in center;
const static int ENEMY_CHANCE = 5; //Chance to spawn enemy on empty square, 1/ENEMY_CHANCE chance.
const int nodes = (MAP_SIZE - 1) / 2;	//Nodes needed;
const static int AROUND_CHANCE = 1;	//Chance to go around the ring
const static int INWARD_CHANCE = 2; //Chance to go inward to the next ring

class IO
{
public:
	IO();

	//Not used, random is better.
	static vector<Entity> readMap(string filename);

	//Generates a random maze 
	static Map * genMaze(Bin<EntityPhysics>* bin, Bin<EntityAI>* enemyBin, EntityPhysics * e, EntityAI *ai, unsigned int seed);

	~IO();
};

