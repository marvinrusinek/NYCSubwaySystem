// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Vertex.cpp
//------------------------------------------------------------------------
//
//        * * * * * Vertex Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the Vertex.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.
//
//------------------------------------------------------------------------  

#include "Vertex.h"


Vertex::Vertex(const string& name1, const VertexId& vid,
				EdgeList* edl):name(name1), id(vid), edges(edl)
{
}

// Precondition: None.
// Postcondition: Function returns the vertex id.
VertexId Vertex::GetVertexId()
{
	return id;
}

// Precondition: None.
// Postcondition: Function returns the edge list.
EdgeList* Vertex::GetEdgeList()
{
	return edges;
}

// Precondition: The function accepts a newEdge as its argument.
// Postcondition: The newEdge is inserted into the edge list.
void Vertex::InsertInEdgeList(Edge* newEdge)
{
	edges->insert(edges->end(), newEdge);
}

// Precondition: None.
// Postcondition: The function deletes the edge list of a vertex by using
// an iterative approach.
void Vertex::KillEdgeList()
{
	EdgeList::iterator p = edges->begin();
	while (p != edges->end())
	{
		delete (*p);
		p = edges->erase(p);
	}
}

// Precondition: None.
// Postcondition: The function returns the name of the vertex.
string Vertex::GetName()
{
	return name;
}
