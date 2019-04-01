// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Edge.cpp
//------------------------------------------------------------------------
//
//        * * * * * Edge Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the Edge.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.                                                
//
//------------------------------------------------------------------------

#include "Edge.h"

// Non-member friend operator for equality check.
bool operator==(const VertexId& v1, const VertexId& v2)
{
	return (v1.iNum==v2.iNum && v1.iLine==v2.iLine);
}

// Non-member friend operator for inequality check.
bool operator!=(const VertexId& v1,const VertexId& v2)
{
	return !(v1 == v2);
}

// Constructor for class Edge.
Edge::Edge(const VertexId& startV,const VertexId& endV,const int len):
	   startVertex(startV),endVertex(endV),length(len)
{
} 

// Default constructor.
Edge::Edge(const Edge& e)
{
	startVertex = e.startVertex;
	endVertex = e.endVertex;
	length = e.length;
	endVertexPtr = e.endVertexPtr;
}

// Non-member friend operator for assignment check.
Edge& Edge::operator=(const Edge& e)
{
	if (this != &e)
	   Edge(e);
	return *this;
}

// Precondition: None.
// Postcondition: Returns the start vertex of the edge.
VertexId Edge::GetStartVertex()
{
	return startVertex;
}

// Precondition: None.
// Postcondition: Returns the end vertex of the edge.
VertexId Edge::GetEndVertex()
{
	return endVertex;
}

// Precondition: None.
// Postcondition: Returns the length of the edge.
int Edge::GetLength()
{
	return length;
}

// Precondition: None.
// Postcondition: Returns the pointer to the end vertex of the edge.
Vertex* Edge::GetEndVertexPtr()
{
	return endVertexPtr;
}

// Precondition: Function accepts a vertex as its argument.
// Postcondition: Sets the end vertex pointer to the vertex pointer, vPtr.
void Edge::SetEndVertexPtr(Vertex* vPtr)
{
	endVertexPtr = vPtr;
}

// Precondition: Function accepts endV as its argument.
// Postcondition: Sets the value of the end vertex to endV.
void Edge::SetEndVertex(const VertexId& endV)
{
	endVertex = endV;
}
