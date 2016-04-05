#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>

#define maxVerticesSize 1000	

class edge {
public:
	int u;
	int v;
	float weight;

	edge(int u, int v, float weight);
};

class Graph {
private:
	int n;
	int m;
	int m_cur;
	edge** edges;
	int* vertices;
public:
	Graph(int n);
	Graph(int n, int m);
	~Graph();

	void genGraph(float minRange, float maxRange);
	void addEdge(int N, int K, float weight);
	void delEdge(int N, int K);

	int getVNum();
	int getEdgeSize();
	int getRealSize();
	edge** getEdgeSet();
	edge*  getEdge(int j);

	float getWeight(int N, int K);

	void print();
	

private:
	void genVertices(int &N, int &K);
	float genWeight(float minRange, float maxRange);
	void cleaner();
	int findEdge(int N, int K);
};


//________________________________________________________________________________________

using namespace std;

edge::edge(int u, int v, float weight)
{
	this->u = u;
	this->v = v;
	this->weight = weight;
}

Graph::Graph(int n)
{
	if ((n < 0) || (n > 45))
		throw "Неверные номера вершин";
	else
		this->n = n;
	this->m = n*(n - 1) / 2;
	m_cur = 0;
	vertices = new int[n];
	edges = new edge*[m];
}

Graph::Graph(int n, int m)
{
	if ((n < 0) || (n > 45))
		throw "Неверные номера вершин";
	else
		this->n = n;

	if ((m < 0) || (m > n*(n - 1) / 2))
		throw "Неверные номера рёбер";
	else
		this->m = m;

	m_cur = 0;

	vertices = new int[n];
	edges = new edge*[m];
}

Graph::~Graph()
{
	cleaner();
	delete[] edges;
	delete[]vertices;
}

void Graph::genVertices(int &N, int &K)
{
	do {
		N = rand() % n;
		K = rand() % n;
	} while ((N == K) || (findEdge(N, K) != -1));
}


float Graph::genWeight(float minRange, float maxRange)
{
	return rand() % (int)(maxRange - minRange - 1) + minRange;// + 1.0/(float)rand();	
}

void Graph::cleaner()
{
	for (int i = 0; i < m_cur; i++)
		delete edges[i];
}

void Graph::genGraph(float minRange, float maxRange)
{
	int u;
	int v;
	float weight;

	if (minRange > maxRange)
		throw "Неверные расстояния";

	if (!m_cur){
		cleaner();
		m_cur = 0;
	}

	srand(time(NULL));
	for (int i = 0; i < m; i++){
		genVertices(u, v);
		weight = genWeight(minRange, maxRange);
		edges[i] = new edge(u, v, weight);
		m_cur++;
	}
}

void Graph::addEdge(int u, int v, float weight)
{
	if (m_cur == m)
		throw "Граф полон";
	if (u == v)
		throw "Петли не допустимы";
	edges[m_cur] = new edge(u, v, weight);
	m_cur++;
}

int Graph::getVNum()
{
	return n;
}

int Graph::getEdgeSize()
{
	return m;
}

int Graph::getRealSize()
{
	return m_cur;
}

edge** Graph::getEdgeSet()
{
	return edges;
}

float Graph::getWeight(int u, int v)
{
	for (int j = 0; j < m_cur; j++)
		if ((edges[j]->v == v) &&
			(edges[j]->u == u) ||
			(edges[j]->u == v) &&
			(edges[j]->v == u))
			return edges[j]->weight;
	throw "Неверноле р!";
}

void Graph::print()
{

	for (int i = 0; i < n; i++)
	{
		cout << i << " : ";
		for (int j = 0; j < m_cur; j++)
		{
			if (edges[j]->u == i)
				cout << edges[j]->v << '(' << edges[j]->weight << ')' << ", ";
			if (edges[j]->v == i)
				cout << edges[j]->u << '(' << edges[j]->weight << ')' << ", ";
		}
		cout << endl;
	}
}

edge* Graph::getEdge(int j)
{
	return edges[j];
}

void Graph::delEdge(int N, int K)
{
	int j = findEdge(N, K);
	if (j == -1)
		throw "Graph: try delete non-existent edge";
	delete edges[j];
	edges[j] = edges[m_cur - 1];
	m_cur--;
}

int Graph::findEdge(int N, int K)
{
	for (int j = 0; j < m_cur; j++)
		if ((edges[j]->v= K) &&
			(edges[j]->u == N) ||
			(edges[j]->u == K) &&
			(edges[j]->v == N))
			return j;
	return -1;
}