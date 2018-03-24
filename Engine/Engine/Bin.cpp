#include "Bin.h"

template <class T>
Bin<T>::Bin(size_t size = 1, size_t elements = 10)
{
	this->size = size;
	this->elements = elements;
	inUse = bool[elements];
	v = vector<T *>(elements);
	start = malloc(size * elements);
	for (int i = 0; i < elements; i++) {
		inUse[i] = false;
	}
}

template <class T>
Bin<T>::~Bin()
{
}

template<class T>
T * Bin<T>::freeSpot()
{
	for (int i = 0; i < elements; i++) {
		if (!inUse[i]) return (T *)(start + i*size);
	}
	return nullptr;
}

template<class T>
T *Bin<T>::add(const T &element) {
	if (T *pointer = freeSpot()) {
		memcpy(pointer, &element, sizeof(*element));
		v.insert(v.end(), pointer);
	}
	return pointer;
}

template<class T>
void Bin<T>::remove(T *element)
{
	v.erase(0);
}
