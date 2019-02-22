// ------------------------------------- graphl.cpp -------------------------- 
// Chyanne Haugen (crhaugen@uw.edu) CSS 343 A
// Creation Date: 2/5/19 
// Date of Last Modification: 2/19/19
// ----------------------------------------------------------------------------
// Purpose - graph class allows a graph to be represented 
//              in memory with an adjacency list.
//			 Feature:
//				- Memory allocation and deallocation is handed by the class
//				- A depth first search of the graph can be preformed
//
// ----------------------------------------------------------------------------
// Notes:
//		-Class does not have all method that would be found in a normal graph
//			class.
//		-Adding to the graph can only happen with a file at creation
//
//		-For some reason using "nullptr" was not working when I ran on linux
//			so I'm just using NULL.
//      
// Assumptions:
//		-Data in the files will alway be correct and able to read.
//		-if size is zero no graph will be created
//
// ----------------------------------------------------------------------------

#pragma once

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
	GraphNode * adjacencyList; //pointer to graph
	int size; //number of nodes in graph

			  //------------------------ insertEdgeNode -------------------------------
			  //private helper function used by buildGraph to insert a node
			  // Preconditions:  adjacencyList points to null
			  // Postconditions: - adjacencyList points to some nodes
			  //				   - size is zero
	void insertEdgeNode(int startVertex, int endVertex);

	//------------------------ depthFirstSearch -------------------------------
	//private helper function to preform a depth first search
	// Preconditions:  adjacencyList points to some nodes
	// Postconditions: - graph has been printed out in dfs order
	void depthFirstSearch(int vertex) const;

	//------------------------ removeHelper -------------------------------
	//private function to remove edgeNode in list
	// Preconditions:  temEdgeNode points to some edge
	// Postconditions: - All memory will be freed from graph
	void removeHelper(EdgeNode *temEdgeNode);

public:
	//------------------------ Default constructor -------------------------------
	// Preconditions:   None
	// Postconditions: - adjacencyList points to NULL
	//				   - size is zero
	GraphL();

	//------------------------ buildGraph -------------------------------
	//Function calls insertEdgeNode()
	// Preconditions:  adjacencyList points to null, size is zero
	// Postconditions: - adjacencyList points to nodes
	//				   - size is some number
	//	Assumptions: if size is zero in the file just return
	void buildGraph(ifstream& infile);

	//------------------------ displayGraph -------------------------------
	// Preconditions:  adjacencyList points to some nodes
	// Postconditions: - graph has been printed out
	//	Assumptions: if size is zero just return
	void displayGraph() const;

	//------------------------ depthFirstSearch -------------------------------
	//calls depthFirstSearch(int) function to preform a depth first search
	// Preconditions:  adjacencyList points to some nodes
	// Postconditions: - graph has been printed out in dfs order
	//	Assumptions: if size is zero just return
	void depthFirstSearch() const;

	//------------------------ deconstructor -------------------------------------
	// Preconditions:  adjacencyList points to some edge
	// Postconditions: - All memory will be freed from graph
	~GraphL();

};