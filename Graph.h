// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Graph.h

//------------------------------------------------------------------------
//
//        * * * * * Graph Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the Graph.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.
//
//------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

typedef list<Vertex*> VertexList;

class Graph
{
	public:
		Graph(){}
		void AddToVertexList(Vertex* v);
		VertexList* GetVertexListPtr();
		Vertex* GetVertexPtrByVertexId(const VertexId& vid);
		void PutLinkVertexPtrInVertexList();
		void InitializeAlgorithmVariables(const string& startStName);
		Vertex* GetNextVertexToWhichShortestPathFound();
		bool IsVertexInEndStationSet(Vertex *nextVertex, const string& 
					     endStName);
		void RecalculateLinkedToNextVertexVertices(Vertex *nextVertex);
		Vertex* DksAlgorithm(const string& startStName, const string&
				     endStName);
		void KillVertexList();

	private:
		VertexList graph;	// a graph of the vertex list
};

#endif
