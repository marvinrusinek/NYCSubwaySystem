// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Vertex.h

#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include <string>
#include "Edge.h"

using namespace std;

typedef list<Edge*> EdgeList;


struct AlgorithmValues
{
		bool shortestPathFoundStatus;
		int shortestPathLength;
		Vertex *inShortestPathPreviousVertex;
};

typedef AlgorithmValues AlgVal;

class Vertex
{
	public:
		Vertex(){}
		Vertex(const Vertex& v):name(v.name),id(v.id),edges(v.edges){}
		Vertex(const string& name1,const VertexId& vid,EdgeList* edl);
		string GetName();
		VertexId GetVertexId();
		EdgeList* GetEdgeList();
		void InsertInEdgeList(Edge* newEdge);
		void KillEdgeList();
		//algorithm values
		AlgVal algValues; 
	private:
		string name;		// name
		VertexId id;		// vertex id
		EdgeList* edges;	// list of edges
};

#endif
