#pragma once
#include "stdafx.h"
#include "nodedata.h"

const int MAXNODES = 101; //per assignment instructions

class GraphM
{
private:

	struct TableType
	{
		bool visted;
		int dist;
		int path;
	};

	NodeData data[MAXNODES];
	int C[MAXNODES][MAXNODES];
	int size;
	TableType T[MAXNODES][MAXNODES];
	int findNearestNeighbor(int sourceNode) const;
	void setAllVistedFalse();

	string shortestPaths[MAXNODES][MAXNODES];
	void getShortestPaths();


public:
	GraphM();
	
	void buildGraph(ifstream& infile);
	void findShortestPath();
	void displayAll() const;
	void display(int fromNode, int toNode) const;

	~GraphM();
};
