#pragma once
#include "reactphysics3d.h"	//Has to go before NCLGL or I get errors for redefining Vector3
#include <vector>
#include <stdlib.h>

template <class T>
class Bin
{
public:
	//Up to you to get the size of each element right
	Bin();
	Bin(size_t size, size_t elements);
	~Bin();

	std::vector<T *> *getVector() { return &v; }

	//void *operator [] (size_t index) { return start + size*index; }
	T *add(T *element);	
	void remove(T *element);
	void empty();



private:
	size_t size;	//Size of each element
	size_t elements;	//Number of elements
	void *start;	//Start of bin	
	bool *inUse;	//Is this element in use?
	std::vector<T *> v;	//Vector of pointers

	T *freeSpot();
	


};


