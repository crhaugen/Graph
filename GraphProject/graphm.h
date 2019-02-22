// ------------------------------------- graphm.cpp -------------------------- 
// Chyanne Haugen (crhaugen@uw.edu) CSS 343 A
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

#pragma once
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



	NodeData data[MAXNODES]; //holds info about nodes
	int C[MAXNODES][MAXNODES]; //holds node and cost info
	int size; //size of graph
	TableType T[MAXNODES][MAXNODES]; //traveling info about nodes

									 //------------------------ findNearestNeighbor ------------------------------
									 //private function to find close (in cost) neighbor to a node
									 // Preconditions:  a start node, there is something to read
									 // Postconditions: - closed node is returned
	int findNearestNeighbor(int sourceNode) const;

	//------------------------ setAllVistedFalse -------------------------------
	//private helper function to set all nodes to false
	// Preconditions:  there is a graph 
	// Postconditions: - all visted node will be set to false
	void setAllVistedFalse();

	//------------------------ printShortestPath -------------------------------
	//private function to print path between two nodes 
	// Preconditions:  a start and end node, theres is something to read
	// Postconditions: - path between start and end has been print it	
	void printShortestPath(int startNode, int endNode) const;

	//------------------------ printDataOnePath -------------------------------
	//private helper function to print out data
	// Preconditions:  there is a graph 
	// Postconditions: - prints path between start and end node
	void printDataOnePath(int startNode, int endNode) const;

public:
	//------------------------ Default constructor ------------------------------
	// Preconditions:   None
	// Postconditions: - 2D matrix with everything set to 0/false/INT_MAX
	//				   - cost matrix all set to INT_MAX
	GraphM();

	//------------------------ buildGraph -------------------------------
	//Function calls insertEdgeNode()
	// Preconditions:  matrix's are empty
	// Postconditions: - cost matrix has node information
	//				   - size is some number
	//	Assumptions: if size is zero in the file just return
	void buildGraph(ifstream& infile);

	//------------------------ findShortestPath -------------------------------
	//calls findNearestNeighbor and setAllVistedFalse to preform tasks
	// Preconditions:  there is a graph with costs
	// Postconditions: - shortest path from and to all nodes have been found
	void findShortestPath();

	//------------------------ displayAll -------------------------------
	// Preconditions:  there is a graph 
	// Postconditions: - prints path and cost between all nodes
	void displayAll() const;

	//------------------------ display -------------------------------
	//calls printDataOnePath to preform the print
	// Preconditions:  there is a graph 
	// Postconditions: - prints path between start and end node
	//Assumption: if start and end nodes are the same dont print
	void display(int fromNode, int toNode) const;

	//------------------------ deconstructor -------------------------------------
	// Preconditions:  an graphm object
	// Postconditions: - graphm object is gone
	~GraphM();
};
