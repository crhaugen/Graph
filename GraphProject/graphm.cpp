#include "stdafx.h"

#include"graphm.h"
#include <iomanip> 
#include <iostream>
#include <algorithm> 

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
	infile.get();

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

void GraphM::removeEdge(int startVertex, int endVertex)
{
	C[startVertex][endVertex] = INT_MAX;
}

int GraphM::findNearestNeighbor(int sourceNode) const
{
	int smallestDist = INT_MAX;
	int indexOfSmallest = 0;

	for (int i = 1; i <= size; i++)
	{
		if (T[sourceNode][i].dist < smallestDist && !T[sourceNode][i].visted)
		{
			smallestDist = T[sourceNode][i].dist;
			indexOfSmallest = i;
		}
	}
	return indexOfSmallest;
}

void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;

		for (int neighbor = 1; neighbor <= size; neighbor++)
		{
			//find nearest neighbor that has not been visted
			int nearestNeighbor = findNearestNeighbor(source);
			
			//mark it as visted
			T[source][nearestNeighbor].visted = true;

			for (int i = 1; i <= size; i++)
			{
				//if there is a path and that path has not been visted check it
				if (C[nearestNeighbor][i] != INT_MAX 
					&& !T[nearestNeighbor][i].visted)
				{
					//distance is the smaller of current distance 
					//and new distance
					T[source][i].dist = min(T[source][i].dist, 
						T[source][nearestNeighbor].dist + C[nearestNeighbor][i]);

					//path to smallest is either current path or new neighbor.
					if (T[source][i].dist > T[source][nearestNeighbor].dist +
						C[nearestNeighbor][i])
					{
						T[source][i].path = nearestNeighbor;
					}
				}
			}
		}
	}
}

void GraphM::displayAll() const
{
	cout << "Description" << setw(60) 
		<< "From node  To node  Dijkstra's Path " << endl;

	for (int currentVertex = 1; currentVertex <= size; currentVertex++)
	{
		cout << data[currentVertex] << endl;

		for (int neighbor = 1; neighbor <= size; neighbor++)
		{
			cout << setw(40);

			if (currentVertex != neighbor)
			{
				cout << currentVertex << setw(10) << neighbor << setw(10);

				if (T[currentVertex][neighbor].dist != INT_MAX)
				{
					cout << T[currentVertex][neighbor].dist;
					//somehow get shortest path..
				}
				else
				{
					cout << "---";
				}
				cout << endl;
			}
			
		}
	}
}

void GraphM::display(int startNode, int endNode) const
{

}

GraphM::~GraphM()
{

}