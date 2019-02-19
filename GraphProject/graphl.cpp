#include "stdafx.h"
#include "graphl.h"

#include <iostream>

using namespace std;

GraphL::GraphL()
{
	size = 0;
	adjacencyList = nullptr;
}

void GraphL::insertEdgeNode(int startVertex, int endVertex)
{
	EdgeNode *edgeNode = new EdgeNode;
	edgeNode->adjGraphNode = endVertex;
	edgeNode->nextEdge = nullptr;

	if (adjacencyList[startVertex].edgeHead != nullptr)
	{
		edgeNode->nextEdge = adjacencyList[startVertex].edgeHead;
		adjacencyList[startVertex].edgeHead = edgeNode;
	}
	else
	{
		adjacencyList[startVertex].edgeHead = edgeNode;
	}
}

void GraphL::buildGraph(ifstream& infile)
{
	infile >> size;
	
	if (size < 1)
	{
		return;
	}

	adjacencyList = new GraphNode[size + 1];

	string names = "";
	getline(infile, names);

	for (int i = 1; i <= size; i++)
	{
		adjacencyList[i].data = new NodeData;
		adjacencyList[i].data->setData(infile);
		adjacencyList[i].edgeHead = nullptr;
		adjacencyList[i].visited = false;
	}
	
	int startVertex = 0;
	int endVertex = 0;

	while (true)
	{
		infile >> startVertex >> endVertex;

		if (startVertex == 0 && endVertex == 0)
		{
			break;
		}

		if (infile.eof())
		{
			break;
		}

		insertEdgeNode(startVertex, endVertex);
	}
}

void GraphL::displayGraph() const
{
	cout << "Graph:" << endl;

	for (int currentVertex = 1; currentVertex <= size; currentVertex++)
	{
		cout << "Node " << currentVertex << setw(25) 
			<< *adjacencyList[currentVertex].data << endl;

		EdgeNode *temEdgeNode = adjacencyList[currentVertex].edgeHead;

		while (temEdgeNode != nullptr)
		{
			cout << "  edge " << currentVertex << " " << temEdgeNode->adjGraphNode << endl;
			temEdgeNode = temEdgeNode->nextEdge;
		}

		cout << endl << endl;
	}
}

void GraphL::depthFirstSearch(int vertex) const
{
	adjacencyList[vertex].visited = true;
	cout << vertex << " ";

	EdgeNode *currentEdge = adjacencyList[vertex].edgeHead;
	while (currentEdge != nullptr)
	{
		if (!adjacencyList[currentEdge->adjGraphNode].visited)
		{
			depthFirstSearch(currentEdge->adjGraphNode);
		}

		currentEdge = currentEdge->nextEdge;
	}
}

void GraphL::depthFirstSearch() const
{
	cout << "Depth First Search: ";

	for (int v = 1; v <= size; v++)
	{
		if (!adjacencyList[v].visited)
		{
			depthFirstSearch(v);
		}
	}

	cout << endl << endl;
}

void GraphL::removeHelper(EdgeNode *temEdgeNode)
{
	if (temEdgeNode != nullptr)
	{
		removeHelper(temEdgeNode->nextEdge);
	}
	delete temEdgeNode;
}

GraphL::~GraphL()
{
	if (adjacencyList != nullptr)
	{
		for (int currentVertex = 1; currentVertex <= size; currentVertex++)
		{
			EdgeNode *temEdgeNode = adjacencyList[currentVertex].edgeHead;
			
			removeHelper(temEdgeNode);
			delete adjacencyList[currentVertex].data;
		}
	}

	delete[] adjacencyList;
}