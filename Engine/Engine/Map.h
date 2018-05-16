#pragma once
#include "Vector3.h";
#include <vector>
#include "EntityAI.h"

class Map
{
public:
	//Map();

	Map(int mapSize, float gridSize, bool *data);

	~Map();


	Vector2 Map::getTile(Vector3 pos) {
		pos.x += m_gridSize/2;
		pos.z -= m_gridSize/2;
		
		return Vector2(int((pos.x) / m_gridSize), int((abs(pos.z)) / m_gridSize));
	}

	void genRoute(EntityAI &e, Vector3 pos);
	

private:
	


	int m_mapSize;
	float m_gridSize;
	bool *m_data;

	class Node {
	public:
		Node *N, *E, *S, *W;
		Node *previous; //Used for backtracking
		float length;	//Travel time from starting point
		float distance; //Distance from end node.
		float weight;	//Weight of node (5 = rubble, 2 = path)
		Vector3 pos; //Position in world.

		Map *m;	//Map this node belongs to.


		void updateNeighbors() {
			if (N) N->updateLength(length + N->weight, this);
			if (E) E->updateLength(length + E->weight, this);
			if (S) S->updateLength(length + S->weight, this);
			if (W) W->updateLength(length + W->weight, this);
		}

		void updateLength(float l, Node *p) {
			if (length > l) {
				length = l;
				previous = p;
				m->binaryInsert(this);
			}
		}
	};

	Node *n;	//All nodes
	std::vector <Node *> v; //Nodes we are considering venturing to.

											   //Node *preComputed = new Node[MAP_WIDTH * MAP_HEIGHT * MAP_WIDTH * MAP_HEIGHT];

	void initNodes();
	void binaryInsert(Node * n); //Binary insert nodes into the vector, in order of (length+distance)
	void resetNodes();



};

