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

		C[startVertex][endVertex] = weight;
	}
}


void GraphM::getShortestPath(int startNode, int endNode, int startIndex, int endIndex, int index) 
{
	if (T[startNode][endNode].path != 0)
	{
		getShortestPath(startNode, T[startNode][endNode].path, startIndex, endIndex, index++);
	}

	P[startIndex][endIndex].shortestPath[index] = endNode;
}

void GraphM::getShortestPaths() 
{
	for (int startNode = 1; startNode <= size; startNode++)
	{
		for (int endNode = 1; endNode <= size; endNode++)
		{
			if (startNode != endNode)
			{
				int index = 0;
				getShortestPath(startNode, endNode, startNode, endNode, index);
			}
		}
	}
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
					//path to smallest is either current path or through new neighbor.
					if (T[source][i].dist > T[source][nearestNeighbor].dist +
						C[nearestNeighbor][i])
					{
						T[source][i].dist = 
							T[source][nearestNeighbor].dist + C[nearestNeighbor][i];
						
						T[source][i].path = nearestNeighbor;
					}
				}
			}
		}
		setAllVistedFalse();
	}
	getShortestPaths();
}

void GraphM::setAllVistedFalse()
{
	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			T[i][j].visted = false;
		}
	}
}

void GraphM::printOnePath(int startNode, int endNode) const
{
	for (int i = 1; i < MAXNODES; i++)
	{
		if (P[startNode][endNode].shortestPath[i] == 0)
		{
			break;
		}

		cout << P[startNode][endNode].shortestPath[i];
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
					cout << T[currentVertex][neighbor].dist << "   ";

					printOnePath(currentVertex, neighbor);
				}
				else
				{
					cout << "---";
				}
				cout << endl;
			}
			
		}
	}
	cout << setw(1);
}

void GraphM::display(int startNode, int endNode) const
{
	cout << startNode << setw(4) << endNode << setw(4);

	if (T[startNode][endNode].dist != INT_MAX)
	{
		cout << T[startNode][endNode].dist << setw(10);
		printOnePath(startNode, endNode);
		cout << endl;
		
		for (int i = 1; i < MAXNODES; i++)
		{
			if (P[startNode][endNode].shortestPath[i] == 0)
			{
				break;
			}

			cout << data[i] << endl;
		}
 	}
	else
	{
		cout << "  ---" << endl;
	}

	cout << endl;
}

GraphM::~GraphM()
{

}