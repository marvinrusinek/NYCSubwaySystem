// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Miscellaneous.cpp
//------------------------------------------------------------------------
//
//        * * * * * Miscellaneous Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the Miscellaneous.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.
//
//------------------------------------------------------------------------  

#include <stdio.h>
#include <iomanip>
#include "Miscellaneous.h"

// Precondition: The function accepts a string as its argument.
// Postcondition: The function enables the conversion to uppercase.
void MakeUpperCase(char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		str[i] = toupper(str[i]);
}

// Precondition: The function accepts a string as its argument.
// Postcondition: The function deletes the spaces between strings and
// shifts after deleting them.
void DeleteSpaces(char* str)
{
	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ')
			str[j++] = str[i];
	str[j] = '\0';
}

int GetTwoCharStringMatchValue(char* str1, char* str2)
{
	int i = -1;
	
	MakeUpperCase(str1);
	MakeUpperCase(str2);
	DeleteSpaces(str1);
	DeleteSpaces(str2);

	if (strcmp(str1, str2))
	{
		// Find the length of the biggest common substring
		// starting from the beginning of the strings;
		// if the strings are equal, the length is -1 (equality mark)
		for (i = 0; str1[i] != '\0' && str2[i] != '\0' 
			 && str1[i] == str2[i]; i++);
	}
	return i;
}

// Precondition: The function accepts the strings text and stationName,
// and the list of subwayStations.
// Postcondition: This function allows for the entry of a string value.
void EnterStringValue(char* text, string& stationName,
					  StationList& subwayStations)
{
	const int n = MAX_FILE_LINE_LENGTH;
	char str[n];
	
	EnterCharValue(text, str, n);
	stationName = str;
	stationName = GetBestMatchFromStationList(stationName, subwayStations);
}

// Precondition: The function accepts text and val as values.
// Postcondition: The function allows for the entry and checking of an
// integer value.
void EnterIntValue(char *text, int& val)
{
	bool flag;	
	do
	{
		cout << text;
		if (scanf("%d",&val) == 1)
		{
			cout << "You have entered: " << val << endl;
			flag = true;
		}
		else
		{
			cout << "Format violation. Please, try again!" << endl;
			flag = false;
		}
		CLEAR;
	} while(!flag);
}

// Precondition: The function accepts two string values, and a length value.
// Postcondition: The function allows for the entry of a char value.       
void EnterCharValue(char *text, char* str, const int len)
{
	int i, iLen;
	char c, *ptr, cc[2];

	iLen = (len > 1) ? (len - 1) : 1;
	do
	{
		cout << text;
		for (i = 0; i < iLen && (c = getchar()) != '\n'; i++)
			str[i] = c;
		if (i)
		{
			if (iLen > 1)
			{
				str[i] = '\0';
				ptr = str;
			}
			else
			{
				cc[0] = str[0];
				cc[1] = '\0';
				ptr = cc;
			}

			cout << "You have entered: " << ptr << endl;
		}
		else
			cout << "Your typed nothing. Please, try again!" <<endl;
		if (c != '\n')
			CLEAR;
	} while(!i);
}

// Precondition: The function accepts two strings as its arguments.
// Postcondition: The function returns two character string matching values.
int GetTwoStringMatchValue(const string& strn1, const string& strn2)
{
	const int n = MAX_FILE_LINE_LENGTH;
	char str1[n], str2[n];
	
	strcpy(str1, strn1.c_str());
	strcpy(str2, strn2.c_str());
	return GetTwoCharStringMatchValue(str1, str2);
}

// Precondition: The function takes stationName and subwayStations as its
// arguments.
// Postcondition: The function obtains the best match from the StationList.
string GetBestMatchFromStationList(const string& stationName,
				   StationList& subwayStations)
{
	StationList::iterator p;
	string bestStr, tempStr;
	int best = -1, temp;
	for (p = subwayStations.begin(); p != subwayStations.end(); p++)
	{
		tempStr = (*p)->longName;
		temp = GetTwoStringMatchValue(stationName, tempStr);
		if (temp < 0)
			return tempStr;
		else
			if (temp > best)
			{
				best = temp;
				bestStr = tempStr;
			}
	}
	return bestStr;
}

// Precondition: The function accepts departureStation, destinationStation,
// and subwayStations as its arguments.
// Postcondition: The function chooses travel stations by returning a Boolean
// value true to signify the shortest path, otherwise false.
bool ChooseTravelStations(string& departureStation, string& destinationStation,
			  StationList& subwayStations)
{
	int val;
	int flag = true;
	char yesNo;
	
	do
	{
		do
		{
		   cout << "\n\tChoose One of the Following Options, please."
			<< endl << endl;
		   cout << " 1. Find Shortest Path Between Two Subway ";
		   cout << "Stations" << endl;
		   cout << " 2. Exit" << endl;
		   EnterIntValue("Enter Your Choice, please: ", val);
		}  while (!(val==1 || val==2));
		if (val == 2)
			return false;
		EnterStringValue("Type Departure Station Name: ",
				 departureStation, subwayStations);
		EnterStringValue("Type Destination Station Name: ",
				 destinationStation, subwayStations);
		cout << "\n\tYour Choice Looks Like:" << endl;
		cout << "Departure Station:  " << departureStation << endl;
		cout << "Destination Station: " << destinationStation << endl;
		if (departureStation == destinationStation)
		{
			cout << "Stations must have different names. Try again!"
			     << endl;
			yesNo = 'n';
		}
		else
		   EnterCharValue("Please, Confirm Your Choice (Y/N): ", &yesNo,
				  1);
	} while(!(yesNo=='Y' || yesNo=='y'));
	return true;
}

// Precondition: The function accepts result and subwayLines as arguments.
// Postcondition: The function prints the shortest path information,
// accompanied by the long and short names by id number; that is, the line
// and the station letter designation.
void PrintResult(Vertex* result, Lines& subwayLines)
{
	Vertex* temp, *next;
	bool transferStatus = true;
	int i = 0;
	int curLine, nextLine;
	if (result)
	{
		cout << "\n\t\tShortest Path Information" << endl;
		do
		{
			temp = result;
			next = '\0';
			while(temp->algValues.inShortestPathPreviousVertex)
			{
			   next = temp;
			   temp = temp->algValues.inShortestPathPreviousVertex;
			}
			if (next)
			{
			   next->algValues.inShortestPathPreviousVertex = NULL;
			   nextLine = next->GetVertexId().iLine;;
			}
			curLine = temp->GetVertexId().iLine;
			if (transferStatus || curLine != nextLine || !next)
			{
				cout << endl << setw(3) << ++i << ". Station: "
				     << temp->GetName() << endl;
				cout << "     Line: "
				     << subwayLines.GetLongNameByIdNum(curLine)
				     << " ("
				     << subwayLines.GetShortNameByIdNum(curLine)
				     << ")" << endl;
				transferStatus = false;
			}
			if (curLine != nextLine)
				transferStatus = true;
		} while(temp != result);
	}
	else
		cout << "No path is available. Check your information, please!"
		     << endl;
}
