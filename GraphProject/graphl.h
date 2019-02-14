#pragma once
#include "stdafx.h"

const int MAXNODES = 101; //per assignment instructions

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
	GraphNode *adjacencyList[MAXNODES];

public:
	GraphL();





	~GraphL();

};