// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Miscellaneous.h

#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <iostream>
#include <string>
#include "Lines.h"
#include "Vertex.h"
using namespace std;

#define MAX_FILE_LINE_LENGTH  120
#define CLEAR while(getchar()!='\n')

void MakeUpperCase(char* str);
void DeleteSpaces(char* str);
int GetTwoCharStringMatchValue(char* str1, char* str2);
int GetTwoStringMatchValue(const string& strn1, const string& strn2);
bool ChooseTravelStations(string& departureStation, string& destinationStation,
			  StationList& subwayStations);
void EnterStringValue(char* text, string& stationName,
		      StationList& subwayStations);
string GetBestMatchFromStationList(const string& stationName,
				   StationList& subwayStations);
void EnterIntValue(char* text, int& val);
void EnterCharValue(char* text, char* str, const int len);
void PrintResult(Vertex* result, Lines& subwayLines);

#endif
