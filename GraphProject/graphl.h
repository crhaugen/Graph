#pragma once
#include "stdafx.h"
#include "nodedata.h"


struct EdgeNode; //forward reference for the compiler

struct GraphNode
{
	EdgeNode *edgeHead; //head of the list of edges
	NodeData *data;  //data information about each node
	bool visited;
};

struct EdgeNode
{
	int adjGraphNode; //subscript of the adjacent graph node
	EdgeNode *nextEdge;
};

class GraphL
{
private:
	GraphNode *adjacencyList; //assuming that highest node will always be input size.. 
	int size;

	void insertEdgeNode(int startVertex, int endVertex);

public:
	GraphL();
	
	void buildGraph(ifstream& infile);

	void displayGraph() const;

	void depthFirstSearch() const;


	~GraphL();

};