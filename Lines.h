// Marvin Rusinek
// ID: 0009099
// CS202 Fall 2000
// Section Letter: C
// Assignment: NYC Subway System
// Filename: Lines.h             

#ifndef LINES_H
#define LINES_H

#include <list>
#include <string>

using namespace std;

struct Line
{
	Line(){}
	Line(const Line& ln):shortName(ln.shortName),
		longName(ln.longName),idNum(ln.idNum){}
	string shortName;
	string longName;
	int idNum;
};

typedef Line Station;
typedef list<Line*> LineList;
typedef list<Station*> StationList;

class Lines
{
	public:
		Lines(){}
		void AddToLineList(Line* ln);
		string GetLongNameByIdNum(const int lid);
		string GetShortNameByIdNum(const int lid);
		void KillLineList();

	private:
		LineList allLines;
};

#endif
