// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Main.cpp
// -------------------------------------------------------------------
//
// * * * * * * Compilation Instructions * * * * * *
//
// Type:
//
// g++ -c Edge.cpp Graph.cpp GraphBuild.cpp Lines.cpp Miscellaneous.cpp
//        Vertex.cpp
//
// g++ Edge.o Graph.o GraphBuild.o Lines.o Miscellaneous.o Vertex.o Main.cpp
//
// a.out (sampletown.data/newtown.data/nyc.data)
//
// ------------------------------------------------------------------------ 

#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include "GraphBuild.h"
#include "Miscellaneous.h"

void BuildGraphByGivenFileAndFindShortestPaths(char* fileName);

// Main Program.
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		BuildGraphByGivenFileAndFindShortestPaths(argv[1]);

		cout << "\n\t\t\tGood bye!\n";
	}
	else
		cout << "Usage: subway input_file_name\n";

	return EXIT_SUCCESS;
}

// Precondition: The function accepts a fileName as its argument.
// Postcondition: The function builds the graph for the given fileName and
// finds all of the shortest paths.
void BuildGraphByGivenFileAndFindShortestPaths(char* fileName)
{
		Lines subwayLines;
		Graph subwayGraph;
		StationList subwayStations;
		string departureStation, destinationStation;

		CreateLineAndVertexLists(subwayLines, subwayGraph,
					 subwayStations, fileName);
		
		while(ChooseTravelStations(departureStation, destinationStation,
					   subwayStations))
		{
		   Vertex* result = subwayGraph.DksAlgorithm(departureStation,
							    destinationStation);
		   PrintResult(result, subwayLines);
		}
		
		subwayLines.KillLineList();
		subwayGraph.KillVertexList();
		KillStationList(subwayStations);
}
