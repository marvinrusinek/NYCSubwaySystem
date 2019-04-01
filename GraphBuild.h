// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: GraphBuild.h

#ifndef GRAPHBUILD_H
#define GRAPHBUILD_H

#include <fstream>
#include <vector>
#include "Lines.h"
#include "Graph.h"

struct Link
{
	Link(){}
	Link(const Link& l):linkVertex(l.linkVertex),type(l.type),
		len(l.len),line(l.line){}	
	Link(const int iLv, const int iType, const int iLen, const int iLine):
		linkVertex(iLv), type(iType), len(iLen), line(iLine){}	
	int linkVertex, type, len, line;
};

typedef vector<Link*> LinkVertexArray;


void CreateLineAndVertexLists(Lines& lns,Graph& subwayGraph,
				StationList& subwayStations,char* fileName);
bool GiveLineInfo(char *buf, Line& ln);
void SetStationInfo(const string& verName,const int verNum, Station& tempSt);
bool GiveVertexInfo(char* buf, int& verNum, string& verName);
bool GiveLinkedVertexInfo(char* buf, Link& ln);
void CreateVertexList(Graph& subwayGraph, StationList& subwayStations,
			const int firstVerNum, const string& firstVerName,
			const int defaultTransferValue, ifstream& ins);
void CreateVertexAndPutItIntoVertexList(Graph& subwayGraph,LinkVertexArray* pLv,
					const int verNum,const string& verName);
void ChangeTransferEdgesInVertexListForAdditionalOnes(Graph& subwayGraph);
void KillStationList(StationList& stations);

#endif
