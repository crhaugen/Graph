#include"graphm.h"


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


void GraphM::buildGraph(ifstream& infile)
{
	infile >> size;

	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile);
	}

	int startVertex = 0;
	int endVertex = 0;
	int weight = 0;

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

		insertEdge(startVertex, endVertex, weight);
	}

}

void GraphM::insertEdge(int startVertex, int endVertex, int weight)
{
	C[startVertex][endVertex] = weight;
}

void GraphM::removeEdge(int startVertex, int endVertex, int weight)
{
	C[startVertex][endVertex] = INT_MAX;
}

void GraphM::findShortestPath()
{

}

void GraphM::displayAll()
{

}

void GraphM::display(int fromNode, int toNode)
{

}

GraphM::~GraphM()
{

}