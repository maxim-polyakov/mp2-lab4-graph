#pragma once
#include "D-Heap.h"
#include "graphs.h"
#include "queue.h"
#include "shared.h"


class DataEdge : public Data {
public:
	DataEdge(edge *e);
	edge *e;
};

class Kruskal {
public:
	static Graph* kruskal(Graph *&graph);
};


DataEdge::DataEdge(edge *e)
{
	this->e = e;
	prior = e->weight;
}

Graph* Kruskal::kruskal(Graph *&graph)
{
	int n = graph->getVNum();
	int m = graph->getRealSize();
	Graph *tree = new Graph(n);

	Shared *set = new Shared(n);
	for (int i = 0; i < n; i++)
		set->singleton(i);

	Data **data = new Data*[m];
	for (int i = 0; i < m; i++)
		data[i] = new DataEdge(graph->getEdgeSet()[i]);

	Queue *queue = new Queue(data, m, 4);

	int treeEdgeSize = 0;
	while ((treeEdgeSize < n - 1) && (!queue->isEmpty()))
	{
		Data* tmp = queue->pop();
		int u = ((DataEdge*)tmp)->e->u;
		int v = ((DataEdge*)tmp)->e->v;
		int weight = ((DataEdge*)tmp)->e->weight;
		int An = set->defineSet(u);
		int Ak = set->defineSet(v);
		if (An != Ak)
		{
			set->association(An, Ak);
			tree->addEdge(u, v, weight);
			treeEdgeSize++;
		}
	}

	for (int i = 0; i < m; i++)
		delete data[i];
	delete[]data;
	delete set;
	delete queue;

	return tree;
}