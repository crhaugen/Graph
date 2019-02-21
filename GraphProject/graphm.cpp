
#include "stdafx.h"
#include "limits.h"
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

	if (size < 1)
	{
		return;
	}

	string names = "";

	getline(infile, names);

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


void GraphM::printShortestPath(int startNode, int endNode) const
{
	if (T[startNode][endNode].path != 0)
	{
		printShortestPath(startNode, T[startNode][endNode].path);
	}

	cout << " " << endNode;
}


int GraphM::findNearestNeighbor(int sourceNode) const
{
	int smallestDist = INT_MAX;
	int indexOfSmallest = 0;

	for (int i = 1; i <= size; i++)
	{
		if ((T[sourceNode][i].dist < smallestDist) && !T[sourceNode][i].visted)
		{
			smallestDist = T[sourceNode][i].dist;
			indexOfSmallest = i;
		}
	}
	return indexOfSmallest;
}

void GraphM::findShortestPath()
{
	int nearestNeighbor = 0;
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;

		for (int neighbor = 1; neighbor <= size; neighbor++)
		{
			//find nearest neighbor that has not been visted
			 nearestNeighbor = findNearestNeighbor(source);

			//mark it as visted
			T[source][nearestNeighbor].visted = true;


			for (int i = 1; i <= size; i++)
			{

				if ((!T[source][i].visted) && (C[nearestNeighbor][i] != INT_MAX))
				{

					if ((T[source][i].dist > (T[source][nearestNeighbor].dist + C[nearestNeighbor][i])))
					{
						T[source][i].dist = T[source][nearestNeighbor].dist + C[nearestNeighbor][i];
						T[source][i].path = nearestNeighbor;
					}
				}
			}
		}
		setAllVistedFalse();
	}
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

void GraphM::printDataOnePath(int startNode, int endNode) const
{

	if (T[startNode][endNode].path != 0)
	{
		printDataOnePath(startNode, T[startNode][endNode].path);
	}

	cout << data[endNode] << endl;
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

				if (T[currentVertex][neighbor].dist != INT_MAX && T[currentVertex][neighbor].dist > 0)
				{
					cout << T[currentVertex][neighbor].dist << "   ";

					if (currentVertex != neighbor)
					{
						printShortestPath(currentVertex, neighbor);
					}
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
	if (startNode == endNode)
	{
		return;
	}

	cout << startNode << setw(4) << endNode << setw(4);

	if ((T[startNode][endNode].dist != INT_MAX) && T[startNode][endNode].dist > 0)
	{
		cout << T[startNode][endNode].dist << setw(10);
		printShortestPath(startNode, endNode);
		cout << endl;

		printDataOnePath(startNode, endNode);
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
