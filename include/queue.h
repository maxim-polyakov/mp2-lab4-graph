#pragma once
#include "D-Heap.h"

class Queue {
private:
	DHeap *heap;
public:
	Queue(int d = 4);
	Queue(const Queue &queue);
	Queue(Data **keys, int num, int d = 4);
	~Queue();

	void push(Data *&key);
	Data* pop(int i);
	Data* pop();

	int isFull();
	int isEmpty();
};

Queue::Queue(int d)
{
	heap = new DHeap(d);
}

Queue::Queue(const Queue &queue)
{
	this->heap = new DHeap(*(queue.heap));
}

Queue::Queue(Data **keys, int num, int d)
{
	heap = new DHeap(d);
	heap->addSet(keys, num);
}

Queue::~Queue()
{
	delete heap;
}

void Queue::push(Data *&key)
{
	heap->add(key);
}

Data* Queue::pop()
{
	return heap->erase(0);
}

int Queue::isFull()
{
	return heap->isFull();
}

int Queue::isEmpty()
{
	return heap->isEmpty();
}
