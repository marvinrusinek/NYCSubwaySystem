// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Lines.cpp
//------------------------------------------------------------------------
//
//        * * * * * Lines Class Implementation File * * * * *
//
//------------------------------------------------------------------------
//
//      This file is an implementation for the Lines.h class.  In here,
//      the definitions of each member and non-member function are presented,
//      but the commentation is rather on the programming level than on
//      the information level.
//
//------------------------------------------------------------------------ 

#include "Lines.h"

// Precondition: the function accepts the line (ln) as its argument.
// Postcondition: The function inserts lines to the LineList.         
void Lines::AddToLineList(Line* ln)
{
	allLines.insert(allLines.end(), ln);
}

// Precondition: The function accepts lid (LongNameById) as its argument.
// Postcondition: The function obtains the longest name by id number.       
string Lines::GetLongNameByIdNum(const int lid)
{
	string temp = "***";
	LineList::iterator p;
	for (p = allLines.begin(); p != allLines.end(); p++)
		if ((*p)->idNum == lid)
		{
			temp = (*p)->longName;
			break;
		}
	return temp;
}

// Precondition: The function accepts lid as its argument.
// Postcondition: The function obtains the shortest name by id number.       
string Lines::GetShortNameByIdNum(const int lid)
{
	string temp = "***";
	LineList::iterator p;
	for (p = allLines.begin(); p != allLines.end(); p++)
		if ((*p)->idNum == lid)
		{
			temp = (*p)->shortName;
			break;
		}
	return temp;
}

// Precondition: None.
// Postcondition: The function deletes LineList using an iterative approach. 
void Lines::KillLineList()
{
	LineList::iterator p = allLines.begin();
	while (p != allLines.end())
	{
		delete (*p);
		p = allLines.erase(p);
	}
}
