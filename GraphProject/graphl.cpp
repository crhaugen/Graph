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
//		-if size in file is zero graph will not be created
//
// ----------------------------------------------------------------------------
#include "graphl.h"
#include <iostream>

using namespace std;

//------------------------ Default constructor -------------------------------
// Preconditions:   None
// Postconditions: - adjacencyList points to NULL
//				   - size is zero
GraphL::GraphL()
{
	size = 0;
	adjacencyList = NULL;
}

//------------------------ insertEdgeNode -------------------------------
//private helper function used by buildGraph to insert a node
// Preconditions:  adjacencyList points to null
// Postconditions: - adjacencyList points to some nodes
//				   - size is zero
void GraphL::insertEdgeNode(int startVertex, int endVertex)
{
	//Creating a new Edgenode in go in the graph
	EdgeNode *edgeNode = new EdgeNode;
	edgeNode->adjGraphNode = endVertex;
	edgeNode->nextEdge = NULL;

	//inserting at the head like you would a linked list
	if (adjacencyList[startVertex].edgeHead != NULL)
	{
		edgeNode->nextEdge = adjacencyList[startVertex].edgeHead;
		adjacencyList[startVertex].edgeHead = edgeNode;
	}
	else
	{
		adjacencyList[startVertex].edgeHead = edgeNode;
	}
}

//------------------------ buildGraph -------------------------------
//Function calls insertEdgeNode()
// Preconditions:  adjacencyList points to null, size is zero
// Postconditions: - adjacencyList points to nodes
//				   - size is some number
//	Assumptions: if size is zero in the file just return
void GraphL::buildGraph(ifstream& infile)
{
	infile >> size;

	if (size < 1)
	{
		return;
	}

	//creating an array of GraphNode with size from file
	adjacencyList = new GraphNode[size + 1];

	string names = "";
	getline(infile, names);

	//setting data from file
	for (int i = 1; i <= size; i++)
	{
		adjacencyList[i].data = new NodeData;
		adjacencyList[i].data->setData(infile);
		adjacencyList[i].edgeHead = NULL;
		adjacencyList[i].visited = false;
	}

	int startVertex = 0;
	int endVertex = 0;

	//setting vertex with data from file
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

//------------------------ displayGraph -------------------------------
// Preconditions:  adjacencyList points to some nodes
// Postconditions: - graph has been printed out
//	Assumptions: if size is zero just return
void GraphL::displayGraph() const
{
	if (size == 0)
	{
		return;
	}

	cout << "Graph:" << endl;

	for (int currentVertex = 1; currentVertex <= size; currentVertex++)
	{
		cout << "Node " << currentVertex << setw(25)
			<< *adjacencyList[currentVertex].data << endl;

		//temp pointer to go down each list
		EdgeNode *temEdgeNode = adjacencyList[currentVertex].edgeHead;

		//while not at end of edges for that node prints out
		while (temEdgeNode != NULL)
		{
			cout << "  edge " << currentVertex << " "
				<< temEdgeNode->adjGraphNode << endl;
			temEdgeNode = temEdgeNode->nextEdge;
		}

		cout << endl << endl;
	}
}

//------------------------ depthFirstSearch -------------------------------
//private helper function to preform a depth first search
// Preconditions:  adjacencyList points to some nodes
// Postconditions: - graph has been printed out in dfs order
void GraphL::depthFirstSearch(int vertex) const
{
	//set current vertex visted to true are print
	adjacencyList[vertex].visited = true;
	cout << vertex << " ";

	//go down the nodes into pointers hit null
	EdgeNode *currentEdge = adjacencyList[vertex].edgeHead;
	while (currentEdge != NULL)
	{
		if (!adjacencyList[currentEdge->adjGraphNode].visited)
		{
			depthFirstSearch(currentEdge->adjGraphNode);
		}

		currentEdge = currentEdge->nextEdge;
	}
}

//------------------------ depthFirstSearch -------------------------------
//calls depthFirstSearch(int) function to preform a depth first search
// Preconditions:  adjacencyList points to some nodes
// Postconditions: - graph has been printed out in dfs order
//	Assumptions: if size is zero just return
void GraphL::depthFirstSearch() const
{
	if (size == 0)
	{
		return;
	}

	cout << "Depth First Search: ";

	//while there are node that have not been visted, vist them
	for (int v = 1; v <= size; v++)
	{
		if (!adjacencyList[v].visited)
		{
			depthFirstSearch(v);
		}
	}

	cout << endl << endl;
}

//------------------------ removeHelper -------------------------------
//private function to remove edgeNode in list
// Preconditions:  temEdgeNode points to some edge
// Postconditions: - All memory will be freed from graph
void GraphL::removeHelper(EdgeNode *temEdgeNode)
{
	if (temEdgeNode != NULL)
	{
		removeHelper(temEdgeNode->nextEdge);
	}
	delete temEdgeNode;
}

//------------------------ deconstructor -------------------------------------
// Preconditions:  adjacencyList points to some edge
// Postconditions: - All memory will be freed from graph
GraphL::~GraphL()
{
	//while adjacencyList pointer is not null keep deleting
	if (adjacencyList != NULL)
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