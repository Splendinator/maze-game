#include "Map.h"




Map::Map(int mapSize, float gridSize, bool *data)
{
	m_mapSize = mapSize;
	m_gridSize = gridSize;
	m_data = data;

	n = new Node[mapSize * mapSize];

	initNodes();
	resetNodes();
}


void Map::resetNodes() {
	v.clear();
	for (int j = 0; j < m_mapSize * m_mapSize; ++j) {
			n[j].length = 20000;
			n[j].previous = nullptr;
	}
}

//I = x axis
//J = z axis
//Starting at (0,0)

void Map::initNodes() {

	for (int j = 0; j < m_mapSize; ++j) {
		for (int i = 0; i < m_mapSize; ++i) {
			n[j * m_mapSize + i].m = this;
			n[j * m_mapSize + i].weight = !m_data[j * m_mapSize + i];
			n[j * m_mapSize + i].pos = Vector3(i *m_gridSize, 0, -j * m_gridSize);
			cout << (n[j * m_mapSize + i].weight ? "." : "#");
		}
		cout << endl;
	}

	for (int j = 0; j < m_mapSize; ++j) {
		for (int i = 0; i < m_mapSize; ++i) {
			//cout << "Node " << j * m_mapSize + i << ":";
			if (n[j * m_mapSize + i].weight) {
				n[j * m_mapSize + i].N = n[(j + 1) * m_mapSize + (i + 0)].weight ? &n[(j + 1) * m_mapSize + (i + 0)] : nullptr;
				n[j * m_mapSize + i].E = n[(j - 0) * m_mapSize + (i + 1)].weight ? &n[(j - 0) * m_mapSize + (i + 1)] : nullptr;
				n[j * m_mapSize + i].S = n[(j - 1) * m_mapSize + (i + 0)].weight ? &n[(j - 1) * m_mapSize + (i + 0)] : nullptr;
				n[j * m_mapSize + i].W = n[(j - 0) * m_mapSize + (i - 1)].weight ? &n[(j - 0) * m_mapSize + (i - 1)] : nullptr;
			}
			else {
				n[j * m_mapSize + i].N = n[j * m_mapSize + i].E = n[j * m_mapSize + i].S = n[j * m_mapSize + i].W = nullptr;
			}
			//cout << " " << n[j * m_mapSize + i].N << " " << n[j * m_mapSize + i].E << " " << n[j * m_mapSize + i].S << " " << n[j * m_mapSize + i].W << endl;
		}
	}
}

void Map::binaryInsert(Node *n) {

	//Handle empty vector.
	if (v.empty()) {
		v.insert(v.begin(), n);
		return;
	}

	int LGap = (v.size()) / 2, RGap = (v.size() - 1) / 2;
	int index = v.size() / 2;

	while (LGap + RGap > 0) {

		if ((v.at(index)->length + v.at(index)->distance) > (n->length + n->distance)) {
			index -= (LGap + 1) / 2;
			RGap = (LGap - 1) / 2;
			LGap = LGap - RGap - 1;
		}
		else {
			index += (RGap + 1) / 2;
			LGap = (RGap - 1) / 2;
			RGap = RGap - LGap - 1;
		}
	}

	v.insert(v.begin() + index + int((v.at(index)->length + v.at(index)->distance) < (n->length + n->distance)), n);

}


void Map::genRoute(EntityAI &e, Vector3 pos)
{
	Vector2 start = getTile(pos);
	Vector2 end = getTile(*(Vector3 *)&e.body->getTransform().getPosition());



	if (start.x == end.x && start.y == end.y) return;	//Handle edge case that you are already on correct tile.

	Node *temp;

	resetNodes();


	int sx = start.x,
		sy = start.y,
		ex = end.x,
		ey = end.y;

	//Generate initial distance for use with A*
	for (int i = 0; i < m_mapSize * m_mapSize; ++i) {
		n[i].distance = 0;
	}

 	n[sy * m_mapSize + sx].length = 0;
	n[sy * m_mapSize + sx].updateNeighbors();


	//While a path has not yet been found...
	while (!n[ey * m_mapSize + ex].previous) {

		if (v.empty()) return;

		temp = v.front();
		v.erase(v.begin());
		temp->updateNeighbors();

		;
	}


	//Work backwards from end node to find optimal path.
	while (n[ey * m_mapSize + ex].previous != nullptr) {

		e.moves->insert(e.moves->end(), n[ey * m_mapSize + ex].pos);

		end = getTile(n[ey * m_mapSize + ex].previous->pos);
		ex = end.x;
		ey = end.y;
	}

}


Map::~Map()
{
}
