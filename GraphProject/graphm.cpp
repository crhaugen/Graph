#include"graphm.h"
#include <iomanip> 
#include <iostream>

using namespace std;

GraphM::GraphM()
{
	size = 0;

	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			T[i][j].path = 0;
			T[i][j].visted = false;
			T[i][j].dist = INT_MAX;

			C[i][j] = INT_MAX;
		}
	}
}


void GraphM::buildGraph(ifstream& infile)
{
	infile >> size;

	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile);
	}

	int startVertex = 0;
	int endVertex = 0;
	int weight = 0;

	while (true)
	{
		infile >> startVertex >> endVertex >> weight;

		if (startVertex == 0 && endVertex == 0 && weight == 0)
		{
			break;
		}

		if (infile.eof())
		{
			break;
		}

		insertEdge(startVertex, endVertex, weight);
	}

}

void GraphM::insertEdge(int startVertex, int endVertex, int weight)
{
	C[startVertex][endVertex] = weight;
}

void GraphM::removeEdge(int startVertex, int endVertex, int weight)
{
	C[startVertex][endVertex] = INT_MAX;
}

void GraphM::findShortestPath()
{

}

void GraphM::displayAll() const
{
	cout << "Description" << setw(25) 
		<< "From node  To node  Dijkstra's Path " << endl;

	for (int currentVertex = 1; currentVertex < size; currentVertex++)
	{
		cout << data[currentVertex] << setw(25);

		for (int neighbor = 1; neighbor < size; neighbor++)
		{
			if (currentVertex == neighbor) //no need to print info about itself
			{
				break;
			}

			cout << currentVertex << setw(10) << neighbor 
				<< T[currentVertex][neighbor].dist;

			//somehow get shortest path..
		}
	}
}

void GraphM::display(int startNode, int endNode) const
{

}

GraphM::~GraphM()
{

}