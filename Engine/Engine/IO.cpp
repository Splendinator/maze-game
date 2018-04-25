#include "IO.h"



IO::IO()
{
}

vector<Entity> IO::readMap(string filename)
{
	vector<Entity> v;



	return v;
}

void change(node *node, unsigned int index, direction d) {
	
	//Coordinate x = index % nodes
	//Coordinate y = index / nodes;
	
	switch (d)
	{
	case NORTH:
		node[index].n = false;		//Knock down north wall
		if (index / nodes > 0) node[index - nodes].s = false;	//Knock down above node's south wall
		break;
	case EAST:
		node[index].e = false;
		if (index % nodes < nodes - 1) node[index + 1].w = false;
		break;
	case SOUTH:
		node[index].s = false;
		if (index / nodes < nodes - 1) node[index + nodes].n = false;
		break;
	case WEST:
		node[index].w = false;
		if (index % nodes > 0) node[index - 1].e = false;
	}
	
	
}

//Generates a random passage (knocks down a random wall) for a given node.
//Takes node array, x and y index of node you want to change, and chances to go n,e,s,w.
void randomPassage(node *node, unsigned int index, int n, int e, int s, int w) {

	//If a passageway already exists, dont make another one.
	n *= node[index].n;
	e *= node[index].e;
	s *= node[index].s;
	w *= node[index].w;

	if (n + e + s + w == 0) {
		cout << "Error:" << index << endl; return;
	}

	int random = rand() % (n + e + s + w);
	
	//Create a passageway based off random number.
		 if (random < n)				change(node, index, NORTH); 
	else if (random < n + e)			change(node, index, EAST);
	else if (random < n + e + s)		change(node, index, SOUTH);
	else  /*(random < n + e + s + w)*/	change(node, index, WEST);
}

void IO::genMaze(Bin<EntityPhysics>* bin, EntityPhysics *e, unsigned int seed)
{
	srand(seed);

	bool map[MAP_SIZE*MAP_SIZE];
	node node[nodes * nodes];
	int aring;

	for (int ring = 0; ring < nodes / 2; ++ring) {	//For each ring (starting at outer ring going inwards)

		aring = (nodes - 1 - ring);	//Inverse ring

		//*** CORNERS ***
		randomPassage(node, ring + ring*nodes, 0, 1, 1, 0);	//Top left corner of current ring (Can only go east or south)
		randomPassage(node, aring + ring*nodes, 0, 0, 1, 1);	//Top right corner;
		randomPassage(node, ring + aring*nodes, 1, 1, 0, 0);	//Bottom left corner;
		randomPassage(node, aring + aring*nodes, 1, 0, 0, 1);	//Bottom right corner;

		//*** ROWS ***
		for (int i = ring + 1; i < aring; ++i) {
			randomPassage(node, i + ring*nodes, 0, AROUND_CHANCE, INWARD_CHANCE, AROUND_CHANCE);	//North row
			randomPassage(node, aring + i*nodes, AROUND_CHANCE, 0, AROUND_CHANCE, INWARD_CHANCE);	//East row
			randomPassage(node, i + aring*nodes, INWARD_CHANCE, AROUND_CHANCE, 0, AROUND_CHANCE);	//South row
			randomPassage(node, ring + i*nodes, AROUND_CHANCE, INWARD_CHANCE, AROUND_CHANCE, 0);	//West row
		}

	}

	//*** INTIATE MAP ***
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			map[i + j*MAP_SIZE] = !(i % 2 == 1 && j % 2 == 1);
		}
	}
	for (int i = 0; i < nodes-1; ++i) {
		for (int j = 0; j < nodes; ++j) {
			map[(i+1)*2 + (j*2+1)*MAP_SIZE] = node[i + j*nodes].e;
			map[(j*2+1) + (i+1)*2*MAP_SIZE] = node[j + i*nodes].s;
		}
	}
	

	//*** POPULATE BIN ***
	EntityPhysics *temp;
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (map[i + j*MAP_SIZE]) {
				temp = bin->add(e);
				temp->applySubSystems();
				temp->move(Vector3(i*e->getScale().x * 2 , e->getScale().y, -j*e->getScale().z * 2));
				temp->body->setType(rp3d::STATIC);
				
			}
		}
	}


}

IO::~IO()
{
}
