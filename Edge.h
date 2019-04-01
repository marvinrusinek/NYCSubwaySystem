// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Edge.h

#ifndef EDGE_H
#define EDGE_H

struct VertexId
{
	VertexId(){}
	VertexId(const VertexId& vid):iNum(vid.iNum),iLine(vid.iLine){}
	VertexId(const int num,const int line):iNum(num),iLine(line){}
	friend bool operator==(const VertexId& v1,const VertexId& v2);
	friend bool operator!=(const VertexId& v1,const VertexId& v2);
	int iNum;  	// station number
	int iLine; 	// line number
};

class Vertex;	// forward declaration

class Edge
{
	public:
	       Edge(){}
	       Edge(const VertexId& startV,const VertexId& endV,const int len); 
	       Edge(const Edge& e);
	       Edge& operator=(const Edge& e);
	       VertexId GetStartVertex();
	       VertexId GetEndVertex();
	       int GetLength();
	       Vertex* GetEndVertexPtr();
	       void SetEndVertex(const VertexId& endV);
	       void SetEndVertexPtr(Vertex* vPtr);

    private:
	       VertexId startVertex;	// start of vertex
	       VertexId endVertex;	// end of vertex
	       int length;		// length
	       Vertex *endVertexPtr;	// for algorithms efficiency needs
};

#endif
