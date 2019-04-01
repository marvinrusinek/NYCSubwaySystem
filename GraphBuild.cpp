// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: GraphBuild.cpp
//------------------------------------------------------------------------
//
//        * * * * * GraphBuild Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the GraphBuild.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.
//
//------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GraphBuild.h"
#include "Miscellaneous.h"

//#define CLEAR while(getchar()!='\n')

const int TransferMark = 99;	// marker of transfer is set to 99

// Precondition: The function accepts a buffer (buf), and a line (ln) as its
// arguments.
// Postcondition: The function provides the line information.
bool GiveLineInfo(char *buf, Line& ln)
{
	char buff[MAX_FILE_LINE_LENGTH], *p, *pbuf;

	pbuf = buff;
	strcpy(pbuf, buf);
	p = strchr(pbuf, ':');
	
	if (p)
	{
		*p = '\0';
		ln.shortName = pbuf;
		pbuf = p+1;
		p = strchr(pbuf, ':');
		if (p)
		{
			*p = '\0';
			ln.longName = pbuf;
			pbuf = p+1;
			return (sscanf(pbuf,"%d",&ln.idNum)==1);
		}
	}
	return false;
}	

// Precondition: The function accepts verName, verNum, and a temporary
// station (tempSt) as its arguments.
// Postcondition: The function sets the station information.
void SetStationInfo(const string& verName, const int verNum, Station& tempSt)
{
	char str[20];
	sprintf(str,"Station_%d",verNum);
	tempSt.shortName = str;
	tempSt.longName = verName;
	tempSt.idNum = verNum;
}

// Precondition: The function accepts stations as an object.
// Postcondition: The function deletes station lists by using an iterative
// approach.
void KillStationList(StationList& stations)
{
	StationList::iterator p;
	for (p = stations.begin(); p != stations.end(); p++)
	{
		delete(*p);
		p = stations.erase(p);
	}
}

// Precondition: The function accepts the buffer (buff), verNum, and verName
// as its arguments.
// Postcondition: The function provides the vertex information by reading
// through the file, using the buffers.
bool GiveVertexInfo(char* buff, int& verNum, string& verName)
{
	bool flag = false;
	char buf[MAX_FILE_LINE_LENGTH], *p;
	int i;

	strcpy(buf, buff);
	
	for (i=0; buf[i] != '\0' && buf[i] == ' '; i++);
	if (buf[i] == '*') // the first not blank symbol should be '*'
	{
		p = strchr(buf,':');
		if (p)
		{
			*p = '\0';
		   verName = (buf + 1);
		      flag = (sscanf((p+1),"%d",&verNum)==1);
		}
	}
	return flag;
}

// Precondition: The function accepts a buffer (buf) and a link (ln) as its
// arguments.
// Postcondition: The function returns the fields for the linked vertex
// information.
bool GiveLinkedVertexInfo(char* buf, Link& ln)
{
	return (sscanf(buf,"%d:%d:%d:%d",&ln.linkVertex,&ln.type,
						&ln.len,&ln.line)==4);
}

// Precondition: The function accepts lns (lines), subwayGraph,
// subwayStations, and fileName as arguments.
// Postcondition: The function creates lines and their vertex lists.
void CreateLineAndVertexLists(Lines& lns, Graph& subwayGraph,
			      StationList& subwayStations, char* fileName)
{
	ifstream ins;
	Line ln;
	int dTransfer,defaultTransferValue; //this value must be present in file
	const int n = MAX_FILE_LINE_LENGTH;
	char buf[n];
	int firstInFileVertexNum = -1; // in case if it is not found 
	string firstInFileVertexName;
	bool lineFlag = true;

	ins.open(fileName);
	if (ins.fail())
	{
		cout << "File: " << fileName << " is not found" << endl;
		exit (1);
	}
	else
	{
		ins.getline(buf, n);
		while(!ins.eof())
		{
			if (lineFlag && GiveLineInfo(buf, ln))
				lns.AddToLineList(new Line(ln));
			else
				if (sscanf(buf,"%d",&dTransfer)==1)
				{
					lineFlag=false;
					defaultTransferValue = dTransfer;
					// if more than one Transfer value in
					// file the last one will be valid
					// only							
				}
				else
				    if (GiveVertexInfo(buf,firstInFileVertexNum,
						       firstInFileVertexName))
					break;

			ins.getline(buf, n);
		}
		if (firstInFileVertexNum < 0)
		{
			cout << "Any vertex is not found in the file: "
			     << fileName
			     << ".\nCheck your data and their format!" << endl;
			exit(1);
		}
        CreateVertexList(subwayGraph, subwayStations, firstInFileVertexNum,
			 firstInFileVertexName, defaultTransferValue, ins);
	}
	ins.close();
	ChangeTransferEdgesInVertexListForAdditionalOnes(subwayGraph);
	subwayGraph.PutLinkVertexPtrInVertexList();
}

// Precondition: The function takes the subwayGraph, subwayStations,
// firstVerNum, firstVerName, defaultTransferValue, and the ins stream as its
// arguments.
// Postcondition: The function creates a vertex list.
void CreateVertexList(Graph& subwayGraph, StationList& subwayStations,
		      const int firstVerNum, const string& firstVerName,
		      const int defaultTransferValue, ifstream& ins) 
			// 'ins' must point to the next file line
			// after the first vertex line and it does point to
			// when we call this function from the function
			// 'CreateLineAndVertexLists'
{
	bool flagEOF, dTransferFlag = true;
	const int n = MAX_FILE_LINE_LENGTH;
	char buf[n];
	int verNum, verNum1;
	string verName, verName1;
	Link tempLink;
	Station tempSt;
	LinkVertexArray *pLv = new LinkVertexArray;
	
	verNum = firstVerNum;
	verName = firstVerName;
	
	Link dTransfer(verNum, 2, defaultTransferValue, TransferMark);
	ins.getline(buf, n);
	while(true)
	{
		if ((flagEOF=(ins.eof()!=0)) || GiveVertexInfo(buf, verNum1,
							       verName1))
		{
			if (dTransferFlag)
				pLv->push_back(new Link(dTransfer));
			SetStationInfo(verName, verNum, tempSt);
			subwayStations.push_back(new Station(tempSt));
			CreateVertexAndPutItIntoVertexList(subwayGraph, pLv,
							   verNum, verName);
			// all the vertices will be created
			// on all the lines that are related
			// to this station name in 'CreateVertexAndPut...'
			if (flagEOF)
				break;
			else
			{
				verNum = verNum1;
				verName = verName1;
				dTransferFlag = true;
				dTransfer.linkVertex = verNum;
			}
		}
		else
			if (GiveLinkedVertexInfo(buf, tempLink))
			{
				pLv -> push_back(new Link(tempLink));
				if (dTransfer.linkVertex == tempLink.linkVertex
				       && dTransfer.line == tempLink.line)
				{
					dTransferFlag = false;
				}
			}
		ins.getline(buf, n);
	}
	delete pLv;
}

// Precondition: The function accepts the subwayGraph, the linked verted
// array pLv, verNum, and verName.
// Postcondition: The function creates a vertex and then puts it into the
// vertex list.
void CreateVertexAndPutItIntoVertexList(Graph& subwayGraph,LinkVertexArray* pLv,
                        		const int verNum,const string& verName)
{
	LinkVertexArray::iterator p;
	int iL,iLine;
	
	while(!pLv->empty())
	{
		iLine = pLv->front()->line;
		if (iLine != TransferMark)
		{
			// Create new edgelist object
			EdgeList *edl = new EdgeList;
			VertexId startV(verNum, iLine);
			Vertex vrt(verName, startV, edl);
			bool iteratorFlag = true;
			for (p = pLv->begin(); p != pLv->end();)
			{
				if ((iL=(*p)->line)==iLine || iL==TransferMark)
				{
					//create edge object and put in edgelist
					VertexId endV((*p)->linkVertex, iL);
					if (startV != endV)
					{
						vrt.InsertInEdgeList(new Edge(
							startV,endV,(*p)->len));
						if(iL != TransferMark)
						{
							delete (*p);
							p = pLv->erase(p);
							iteratorFlag = false;
						}
					}
				}
				if (iteratorFlag)
					p++;
				else
					iteratorFlag = true;
			}
			// put new vertex in vertexlist
			subwayGraph.AddToVertexList(new Vertex(vrt));
			if (edl->empty())
				delete edl;
		}
		else
		{
			p = pLv->begin();
			delete(*p);
			pLv->erase(p);
		}
	}
}

// Precondition: The function accepts the subwayGraph as its argument.
// Postcondition: The function modifies the transfer edges in the vertex
// list for additional transfers.
void ChangeTransferEdgesInVertexListForAdditionalOnes(Graph& subwayGraph)
{
	VertexList *vrtLst = subwayGraph.GetVertexListPtr();
	VertexList::iterator vlExt, vlInt;
	
	for(vlExt = vrtLst->begin(); vlExt != vrtLst->end(); vlExt++)
	{
		EdgeList *elt = (*vlExt)->GetEdgeList();
		EdgeList::iterator p = elt->begin();
		while(p != elt->end())
		{
			VertexId vid = (*p)->GetEndVertex();
			if (vid.iLine == TransferMark)
			{
				for(vlInt=vrtLst->begin(); vlInt!=vrtLst->end();
				    vlInt++)
				    if (vid.iNum==(*vlInt)->GetVertexId().iNum)
				    {
					VertexId endV(vid.iNum,(*vlInt)->
						      GetVertexId().iLine);
					VertexId startV=(*p)->GetStartVertex();
					if (!(startV == endV))
					{
						(*p) -> SetEndVertex(endV);
						elt->push_back(new Edge(*(*p)));
					}
				    }
				delete (*p);
				p = elt->erase(p);
			}
			else
				p++;
		}
	}
}
