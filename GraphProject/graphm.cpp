// ------------------------------------- graphm.cpp -------------------------- 
// Chyanne Haugen (crhaugen@uw.edu) CSS 343 A (assignment #3)
// Creation Date: 2/5/19 
// Date of Last Modification: 2/19/19
// ----------------------------------------------------------------------------
// Purpose - graph class allows a graph to be represented 
//              in memory with an adjacency matrix.
//			 Feature:
//				- Finding shortest path 
//
// ----------------------------------------------------------------------------
// Notes:
//		-Class does not have all method that would be found in a normal graph
//			class.
//		-Adding to the graph can only happen with a file at creation
//
//      
// Assumptions:
//		-Data in the files will alway be correct and able to read.
//		-if size is zero no graph will be created
//
// ----------------------------------------------------------------------------

#include "limits.h"
#include"graphm.h"
#include <iomanip> 
#include <iostream>
#include <algorithm> 

using namespace std;

//------------------------ Default constructor -------------------------------
// Preconditions:   None
// Postconditions: - 2D matrix with everything set to 0/false/INT_MAX
//				   - cost matrix all set to INT_MAX
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

//------------------------ buildGraph -------------------------------
//Function calls insertEdgeNode()
// Preconditions:  matrix's are empty
// Postconditions: - cost matrix has node information
//				   - size is some number
//	Assumptions: if size is zero in the file just return
void GraphM::buildGraph(ifstream& infile)
{
	//reading and checking size
	infile >> size;

	if (size == 0)
	{
		return;
	}

	string names = "";

	getline(infile, names);

	//reading data into data matrix
	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile);
	}

	int startVertex = 0;
	int endVertex = 0;
	int weight = 0;

	//reading node information in to cost matrix
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

//------------------------ printShortestPath -------------------------------
//private function to print path between two nodes 
// Preconditions:  a start and end node, theres is something to read
// Postconditions: - path between start and end has been print it
void GraphM::printShortestPath(int startNode, int endNode) const
{
	if (T[startNode][endNode].path != 0)
	{
		printShortestPath(startNode, T[startNode][endNode].path);
	}

	cout << " " << endNode;
}

//------------------------ findNearestNeighbor -------------------------------
//private function to find close (in cost) neighbor to a node
// Preconditions:  a start node, there is something to read
// Postconditions: - closed node is returned
int GraphM::findNearestNeighbor(int sourceNode) const
{
	int smallestDist = INT_MAX;
	int indexOfSmallest = 0;

	for (int i = 1; i <= size; i++)
	{
		//if there is a smaller distance and we have not already been there
		if ((T[sourceNode][i].dist < smallestDist) && !T[sourceNode][i].visted)
		{
			smallestDist = T[sourceNode][i].dist;
			indexOfSmallest = i;
		}
	}
	return indexOfSmallest;
}

//------------------------ findShortestPath -------------------------------
//calls findNearestNeighbor and setAllVistedFalse to preform tasks
// Preconditions:  there is a graph with costs
// Postconditions: - shortest path from and to all nodes have been found
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


			//go through and check if current cost is less then new cost
			for (int i = 1; i <= size; i++)
			{

				//if there is a vaild not visted path check it
				if ((!T[source][i].visted) &&
					(C[nearestNeighbor][i] != INT_MAX))
				{

					//check if what we have is better the new path
					if ((T[source][i].dist > (T[source][nearestNeighbor].dist +
						C[nearestNeighbor][i])))
					{
						T[source][i].dist = T[source][nearestNeighbor].dist +
							C[nearestNeighbor][i];
						T[source][i].path = nearestNeighbor;
					}
				}
			}
		}
		setAllVistedFalse();
	}
}

//------------------------ setAllVistedFalse -------------------------------
//private helper function to set all nodes to false
// Preconditions:  there is a graph 
// Postconditions: - all visted node will be set to false
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

//------------------------ displayAll -------------------------------
// Preconditions:  there is a graph 
// Postconditions: - prints path and cost between all nodes
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

				//if there is a vaild cost see if its smaller
				if (T[currentVertex][neighbor].dist != INT_MAX &&
					T[currentVertex][neighbor].dist > 0)
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

//------------------------ printDataOnePath -------------------------------
//private helper function to print out data
// Preconditions:  there is a graph 
// Postconditions: - prints path between start and end node
void GraphM::printDataOnePath(int startNode, int endNode) const
{

	//if there is a path kind going down
	if (T[startNode][endNode].path != 0)
	{
		printDataOnePath(startNode, T[startNode][endNode].path);
	}

	cout << data[endNode] << endl;
}


//------------------------ display -------------------------------
//calls printDataOnePath to preform the print
// Preconditions:  there is a graph 
// Postconditions: - prints path between start and end node
//Assumption: if start and end nodes are the same dont print
void GraphM::display(int startNode, int endNode) const
{
	//if equal don't print
	if (startNode == endNode)
	{
		return;
	}

	cout << startNode << setw(4) << endNode << setw(4);

	//if there is a found cost between nodes
	if ((T[startNode][endNode].dist != INT_MAX) &&
		T[startNode][endNode].dist > 0)
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

//------------------------ deconstructor -------------------------------------
// Preconditions:  an graphm object
// Postconditions: - graphm object is gone
GraphM::~GraphM()
{

}
