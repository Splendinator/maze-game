#include "Bin.h"
#include "EntityPhysics.h"

template <class T>
Bin<T>::Bin()
{
}


template <class T>
Bin<T>::Bin(size_t size, size_t elements)
{
	this->size = size;
	this->elements = elements;
	inUse = new bool[elements];
	v = vector<T *>(elements);
	start = malloc(size * elements);
	for (int i = 0; i < elements; i++) {
		inUse[i] = false;
	}
	v.clear();
}

template <class T>
Bin<T>::~Bin()
{
	delete[] inUse;
	free(start);
}

template<class T>
T * Bin<T>::freeSpot()
{
	for (int i = 0; i < elements; i++) {
		if (!inUse[i]) 
			return (T *)((unsigned long long int)start + i*size);
	}
	return nullptr;
}

template<class T>
T *Bin<T>::add(const T &element) {
	T *pointer = freeSpot();

	if (pointer) {
		memcpy(pointer, &element, sizeof(element));
		v.insert(v.end(), pointer);
		inUse[pointer - start] = true;
		
	}
	return pointer;
}

template<class T>
void Bin<T>::remove(T *element)
{
	//v.erase(0);
}

template class Bin<EntityPhysics>;
template class Bin<int>;
