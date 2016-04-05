#pragma once
#include <iostream> 
#include <algorithm>
#include "graphs.h"

#define maxSize 100
typedef int dataType;

class Data {
public:
	float prior;
};

class DHeap{
private:
	int minChild(int i);
protected:
	Data **keys;
	int d;
	int lid;			
public:
	DHeap(int d);
	DHeap(const DHeap &heap);
	~DHeap();

	void add(Data *&key);
	void addSet(Data **key, int num);
	Data* erase();
	Data* erase(int i);

	void transposition(int i, int j);
	void surfacing(int i);
	void immersion(int i);

	void spudding();

	int isFull();
	int isEmpty();


};


//_____________________________________________________________________________________________

DHeap::DHeap(int d)
{
	if (d <= 0)
		throw "";
	this->d = d;
	lid = -1;
	keys = new Data*[maxSize];
}

DHeap::DHeap(const DHeap &heap)
{
	this->d = heap.d;
	keys = new Data*[maxSize];
	for (int i = 0; i <= heap.lid; i++)
		keys[i] = heap.keys[i];
	this->lid = heap.lid;
}

DHeap::~DHeap()
{
	delete[] keys;
}

void DHeap::add(Data *&key)
{
	if (isFull())
		throw "";
	lid++;
	keys[lid] = key;
	surfacing(lid);
}

void DHeap::addSet(Data **key, int num)
{
	if (lid + num >= maxSize)
		throw "";
	for (int i = lid + 1; i < lid + num + 1; i++)
	{
		keys[i] = key[i - lid - 1];
	}
	lid += num;
	spudding();
}

Data* DHeap::erase()
{
	if (isEmpty())
		throw "DAryHeap: No data!";
	Data* key = keys[lid];
	lid--;
	return key;
}

Data* DHeap::erase(int i)
{
	if (isEmpty())
		throw "";
	if ((i < 0) || (i > lid))
		throw "";

	Data* key = keys[i];
	if (i == lid)
	{
		lid--;
		return key;
	}
	transposition(i, lid);
	lid--;
	immersion(i);
	return key;
}

void DHeap::transposition(int i, int j)
{
	if ((i < 0) || (j < 0) || (i > lid) || (j > lid))
		throw "";
	Data* tmp = keys[i];
	keys[i] = keys[j];
	keys[j] = tmp;
}

void DHeap::surfacing(int i)
{
	if ((i < 0) || (i > lid))
		throw "";

	int p = (i - 1) / d;
	while (i > 0) {
		if (keys[p]->prior < keys[i]->prior)
			break;
		transposition(p, i);
		i = p;
		p = (i - 1) / d;
	}
}

void DHeap::immersion(int i)
{
	if ((i < 0) || (i > lid))
		throw "";

	int c = minChild(i);
	while ((c != -1) && (keys[c]->prior < keys[i]->prior)){
		transposition(i, c);
		i = c;
		c = minChild(i);
	}
}

void DHeap::spudding()
{
	for (int i = lid; i >= 0; i--)
		immersion(i);
}

int DHeap::isFull()
{
	return lid >= maxSize - 1;
}

int DHeap::isEmpty()
{
	return lid == -1;
}

int DHeap::minChild(int i)
{
	int f = i*d + 1;
	if (f > lid)
		return -1;

	int l = std::min(i*d + d, lid);
	int c;

	Data* minKey = keys[f];
	c = f;
	for (int k = f + 1; k <= l; k++){
		if (minKey->prior > keys[k]->prior){
			minKey = keys[k];
			c = k;
		}
	}
	return c;
}