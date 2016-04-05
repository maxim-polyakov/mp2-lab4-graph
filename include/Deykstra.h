#pragma once
#include "graphs.h"
#include "D-Heap.h"
#include "queue.h"
#include <cfloat>

class DataFloat : public Data {
public:
	DataFloat(int v, float dist);
	int v;
};

class Deykstra {
public:
	static float* deykstra(Graph *&graph, int s);
};
//_______________________________________________________________________________

DataFloat::DataFloat(int v, float dist)
{
	this->v = v;
	prior = dist;
}

float* Deykstra::deykstra(Graph *&graph, int s)
{
	int n = graph->getVNum();
	if ((s < 0) || (s >= n))
		return 0;
	int m = graph->getRealSize();

	Data** dist = new Data*[n];
	int* up = new int[n];

	for (int i = 0; i < n; i++){
		up[i] = 0;
		dist[i] = new DataFloat(i, FLT_MAX);
	}
	dist[s]->prior = 0;

	Queue *queue = new Queue(dist, n, 4);

	edge** edges = graph->getEdgeSet();
	int edgeCount = m;
	while ((edgeCount != 0) && (!queue->isEmpty()))
	{
		Data* tmp = queue->pop();
		int v = ((DataFloat*)tmp)->v;
		int v0 = -1;
		float delta;
		for (int i = 0; i < m; i++)
		{
			v0 = -1;
			if (edges[i]->u == v)
				v0 = edges[i]->u;
			if (edges[i]->v == v)
				v0 = edges[i]->v;
			if (v0 == -1) continue;
			delta = dist[v0]->prior - (dist[v]->prior + graph->getWeight(v, v0));
			if (delta > 0){
				dist[v0]->prior = graph->getWeight(v, v0) + dist[v]->prior;
				up[v0] = v;
			}
		}
	}

	float *res = new float[n];
	for (int i = 0; i < n; i++)
		res[i] = dist[i]->prior;

	for (int i = 0; i < n; i++)
		delete dist[i];
	delete[]dist;
	delete queue;
	delete[]up;

	return res;
}