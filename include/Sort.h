#pragma once
#include "D-Heap.h"

class DataInt : public Data {
public:
	DataInt(int elem);
};

class Heapsort {
public:
	static void heapsort(int *&arr, int n, int d);
};

//_______________________________________________________________________

DataInt::DataInt(int elem)
{
	this->prior = float(elem);
}

void Heapsort::heapsort(int *&arr, int n, int d = 4)
{
	Data** data = new Data*[n];
	for (int i = 0; i < n; i++)
		data[i] = new DataInt(arr[i]);
	DHeap* heap = new DHeap(d);
	heap->addSet(data, n);

	for (int i = n - 1; i >= 0; --i)
	{
		heap->transposition(0, i);
		arr[i] = (int)heap->erase()->prior;
		heap->immersion(0);
	}
	delete heap;
	for (int i = 0; i < n; i++)
		delete data[i];
	delete[]data;
}