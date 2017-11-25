//************************************************************************
// Copyright � 2016, "Q's Programming" 
// All rights reserved. 
// 
// Author: 
// "Quentin Curteman" 
// 
// Department: 
// COMSC11 C++ Programming Department 
// 
// Purpose: 
// Decelaration file for Parser class.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#ifndef PARSER
#define PARSER
#include <iostream>
#include <fstream>
using namespace std;


struct ParserPnts
{
	double XPnt;
	double YPnt;
	double IPnt;
	double JPnt;
};

class Parser
{
private:
	ParserPnts XYIJPnts;		//Holds the XY points that the robot arm will move to
	ifstream   InputStream;     //Variable that reads in the info from the text file
	ParserPnts *getGCodeInfo();	//Opens the text file and extracts info and sets variables
	ParserPnts *XYIJPntr;
	int *DirectionPtr;

	//Determines if it is a line, circle, clockwise, counter clockwise
	//1 = move in line
	//2 = move in circle clockwise
	//3 = move in circle counterclockwise
	//int     Direction;
	int     number_of_lines;
	void    setNumberOfLines();

public:

	int  getNumberOfLines();
	int  getDirection(int);
	ParserPnts* ReadTxtFile();
	Parser();
	~Parser()
	{
		delete[]XYIJPntr;
		delete[]DirectionPtr;
	}
};

#endif PARSER