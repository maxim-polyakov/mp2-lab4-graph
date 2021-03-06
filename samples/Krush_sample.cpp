#include <iostream>
#include <fstream>
#include <cstring>

#include "graphs.h"
#include "Krush.h"

using namespace std;

int main(int argc, char **argv)
{
	Graph *graph;
	int n;
	int m;
	if (argc == 5)				
	{
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		int minRange = atoi(argv[3]);
		int maxRange = atoi(argv[4]);

		graph = new Graph(n, m);
		graph->genGraph(minRange, maxRange);
		graph->print();
	}
	else if (argc == 2)	{		
		string filename(argv[1]);
		ifstream input(filename);
		
		if (!input)
		{
			cout << "";
			return 2;
		}
		input >> n;
		graph = new Graph(n);
		float weight;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < i; j++)
				input >> weight;
			for (int j = i; j < n; j++){
				weight = 0;
				input >> weight;
				if (weight != 0)
					graph->addEdge(i, j, weight);
			}
		}
	}
	else return 1;

	Graph *tree = Kruskal::kruskal(graph);

	std::cout << std::endl;
	tree->print();

	fstream output;
	output.open("tree.txt", fstream::in | fstream::out);
	if (output)
		remove("tree.txt");			
	ofstream ofs("tree.txt");		
	output << n << endl;			

	float **matrix = new float*[n]; 
	for (int i = 0; i < n; i++)
		matrix[i] = new float[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;

	m = graph->getRealSize();
	edge* edge;
	for (int j = 0; j < m; j++) {	
		edge = graph->getEdge(j);
		matrix[edge->u][edge->v] = edge->weight;
		matrix[edge->u][edge->v] = edge->weight;
	}

	for (int i = 0; i < n; i++) {	
		for (int j = 0; j < n; j++)
			output << matrix[i][j] << ' ';
		output << endl;
	}

	for (int i = 0; i < n; i++)		
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;

	m = tree->getRealSize();
	for (int j = 0; j < m; j++)	{	
		edge = tree->getEdge(j);
		matrix[edge->u][edge->v] = edge->weight;
		matrix[edge->u][edge->v] = edge->weight;
	}

	output << endl;
	for (int i = 0; i < n; i++)	{	
		for (int j = 0; j < n; j++)
			output << matrix[i][j] << ' ';
		output << endl;
	}

	output.close();
	delete graph;
	delete tree;
	return 0;
}
