// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Graph.cpp

#include <iostream>
#include <limits.h>
#include "Graph.h"

// Precondition: None.
// Postcondition: The function returns a reference to the Graph.
VertexList* Graph::GetVertexListPtr()
{
	return &graph;
}

// Precondition: The function takes the pointer to vertex v as its argument.
// Postcondition: The function inserts v at the end of the graph.
void Graph::AddToVertexList(Vertex* v)
{
	graph.insert(graph.end(), v);
}

// Precondition: Function takes a vertex id, vid, as its argument.
// Postcondition: Function returns the vertex pointer for the particular
// vertex id by using an iterator.
Vertex* Graph::GetVertexPtrByVertexId(const VertexId& vid)
{
	VertexList::iterator p;
	Vertex* temp = NULL;
	for (p = graph.begin(); p != graph.end(); p++)
	{
		if ((*p)->GetVertexId() == vid)
		{
			temp = *p;
			break;
		}
	}
	return temp;
}

// Precondition: None.
// Postcondition: Function places a linked vertex pointer into the vertex list.
void Graph::PutLinkVertexPtrInVertexList()
{
	VertexList::iterator pV;
	EdgeList::iterator pE;
	EdgeList* tempE;
	Vertex* vPtr;
	for (pV = graph.begin(); pV != graph.end(); pV++)
	{
		tempE = (*pV)->GetEdgeList();
		for(pE = tempE->begin(); pE != tempE->end(); pE++)
		{
			vPtr = GetVertexPtrByVertexId((*pE)->GetEndVertex());
			(*pE)->SetEndVertexPtr(vPtr);
		}
	}
}

// Precondition: None.
// Postcondition: Deletes the vertex list using iterative approach.
void Graph::KillVertexList()
{
	VertexList::iterator p = graph.begin();
	while (p != graph.end())
	{
		Vertex *temp = *p;
		temp -> KillEdgeList();
		delete temp -> GetEdgeList();
		delete temp;
		p = graph.erase(p);
	}
}

// Precondition: The function accepts the starting name of a station as its
// argument.
// Postcondition: The function initializes the algorithm variables using
// an iterative approach.
void Graph::InitializeAlgorithmVariables(const string& startStName)
{
	VertexList::iterator p;
	string stName;
	AlgVal tempVal;

	tempVal.inShortestPathPreviousVertex = NULL;
	tempVal.shortestPathFoundStatus = false;
	
	for (p = graph.begin(); p != graph.end(); p++)
	{
		stName = (*p)->GetName();
		if (stName == startStName)
			tempVal.shortestPathLength = 0;
		else
			tempVal.shortestPathLength = INT_MAX;
		
		(*p)->algValues = tempVal;
	}
}

// Precondition: None.
// Postcondition: The function returns temp, which is the next vertex to
// which the shortest path is found.
Vertex* Graph::GetNextVertexToWhichShortestPathFound()
{
	VertexList::iterator p;
	int iLen, minLength = INT_MAX;
	Vertex *temp = NULL;
	
	for (p = graph.begin(); p != graph.end(); p++)
	{
		AlgVal *av = &((*p)->algValues);
		if(!av->shortestPathFoundStatus && (iLen=av->shortestPathLength)
						    < minLength)
		{
			minLength = iLen;
			temp = (*p);
		}
	}

	if (temp)
		temp->algValues.shortestPathFoundStatus = true;

	return temp;
}

// Precondition: The function accepts the pointer to the next vertex and
// the end of station name as its arguments.
// Postcondition: The function returns a Boolean value true if the vertex
// is in the end of the station set, otherwise false.
bool Graph::IsVertexInEndStationSet(Vertex *nextVertex, const string& endStName)
{
	return (nextVertex && nextVertex->algValues.shortestPathFoundStatus
			&& nextVertex->GetName()==endStName);
}

// Precondition: The function accepts the pointer to the next vertex as
// its argument.
// Postcondition: The function recalculates the linked to nexter vertex
// vertices using an iterative approach.
void Graph::RecalculateLinkedToNextVertexVertices(Vertex *nextVertex)
{
	EdgeList::iterator pE;
	EdgeList* tempE;
	Vertex* vPtr;
	
	tempE = nextVertex->GetEdgeList();
	for(pE = tempE->begin(); pE != tempE->end(); pE++)
	{
		vPtr = (*pE)->GetEndVertexPtr();
		if (vPtr && !vPtr->algValues.shortestPathFoundStatus)
			if (vPtr->algValues.shortestPathLength >
				nextVertex->algValues.shortestPathLength +
					(*pE)->GetLength())
			{
			   vPtr->algValues.shortestPathLength =
			   nextVertex->algValues.shortestPathLength
				+ (*pE)->GetLength();
			   vPtr->algValues.inShortestPathPreviousVertex
				=nextVertex;
			}
	}
}

// Precondition: The function accepts the starting name and ending name for a
// particular station.
// Postcondition: The function uses Dijkstra's algorithm to determine the
// shortest path found, otherwise recalculates the linked to next vertex
// vertices, and returns the next vertex.
Vertex* Graph::DksAlgorithm(const string& startStName, const string& endStName)
{
	Vertex* nextVertex;
	bool shortestPathFound = false;
	
	InitializeAlgorithmVariables(startStName);
	do
	{
		nextVertex = GetNextVertexToWhichShortestPathFound();
		if (nextVertex)
			if (IsVertexInEndStationSet(nextVertex,endStName))
				shortestPathFound = true;
		    else
		       RecalculateLinkedToNextVertexVertices(nextVertex);
	} while(!(nextVertex == NULL || shortestPathFound));

	return nextVertex;
}
