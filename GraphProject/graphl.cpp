#include "stdafx.h"
#include "graphl.h"

#include <iostream>

using namespace std;

GraphL::GraphL()
{
	size = 0;
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
	infile.get();

	adjacencyList = new GraphNode[size + 1];

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

		cout << endl;
	}
}

void GraphL::depthFirstSearch() const
{

}


GraphL::~GraphL()
{

}