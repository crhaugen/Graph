#pragma once
#include "stdafx.h"
#include "nodedata.h"
#include <iomanip> 

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
	GraphNode *adjacencyList; 
	int size;

	void insertEdgeNode(int startVertex, int endVertex);
	void depthFirstSearch(int vertex) const;
	void removeHelper(EdgeNode *temEdgeNode);

public:
	GraphL();
	
	void buildGraph(ifstream& infile);

	void displayGraph() const;

	void depthFirstSearch() const;


	~GraphL();

};