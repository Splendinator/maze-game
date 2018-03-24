#pragma once
#include <vector>
#include <stdlib.h>

template <class T>
class Bin
{
public:
	//Up to you to get the size of each element right
	Bin(size_t size = 1, size_t elements = 10);
	~Bin();

	std::vector<T *> getVector() { return v; }

	//void *operator [] (size_t index) { return start + size*index; }
	T *add(const T &element);	
	void remove(T *element);



private:
	size_t size;	//Size of each element
	size_t elements;	//Number of elements
	void *start;	//Start of bin	
	bool *inUse;	//Is this element in use? (quicker than dynamically working it out)
	std::vector<T *> v;	//Vector of pointers

	T *freeSpot();
	


};

