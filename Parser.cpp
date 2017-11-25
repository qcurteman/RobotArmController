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
// This class parses the information input by a G-Code document 
// 
// Effects: 
// The expected ussage is: 
// 1. A G-Code document is input.
// 2. Return a pointer pointing to the beginning of an array containing points
//    to draw a picture based on the G-Code.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"

using namespace std;

Parser::Parser()
{
	XYIJPnts.XPnt = 0;
	XYIJPnts.YPnt = 0;
	XYIJPnts.IPnt = 0;
	XYIJPnts.JPnt = 0;

	XYIJPntr = &XYIJPnts;
}

ParserPnts* Parser::getGCodeInfo()
{
	//Text is set directly from the file to this string. The string is parsed through
	//to find information about how to move the robot
	string GCodeString;

	//Array takes in characters from GCodeString and holds them temporarily
	//the array is then created into string which is then turned into a double
	char   DummyArray[20];
	char   tempDirection;

	//Open the file to read text from it
	InputStream.open("Sample_TestFile.txt");

	int array_location = 0;
	int size = getNumberOfLines();

	XYIJPntr     = new ParserPnts[size];
	DirectionPtr = new int[size];

	if (InputStream.peek() == 'G')
	{
		while (GCodeString != "M00")
		{
			getline(InputStream, GCodeString);
			tempDirection = GCodeString[2];
			DirectionPtr[array_location] = tempDirection - '0';

			for (unsigned int count = 0; count < GCodeString.length(); count++)
			{
				if (GCodeString[count] == 'X')
				{
					unsigned int string_index = count + 1;		//Add 1 to it so we dont get the X, only want the decimal numbers
					int array_index = 0;				//Set decimal numbers in the index from 0 to how ever many decimal numbers there are		
					while ((GCodeString[string_index] != 'Y') && (GCodeString[string_index] != 'J') && (GCodeString[string_index] != 'I') && (GCodeString[string_index] != '\n') && (string_index + 1 <= GCodeString.length()))
					{
						DummyArray[array_index] = GCodeString[string_index];

						if (string_index + 1 <= GCodeString.length())
							string_index++;
						array_index++;
						count++;
					}
					string DummyString(DummyArray);
					XYIJPnts.XPnt = stod(DummyString);

					//Reset the Array for future use
					for (int i = 0; i < 20; i++)
						DummyArray[i] = 0;
				}

				if (GCodeString[count] == 'Y')
				{
					unsigned int string_index = count + 1;		//Add 1 to it so we dont get the Y, only want the decimal numbers
					int array_index = 0;				//Set decimal numbers in the index from 0 to how ever many decimal numbers there are		
					while ((GCodeString[string_index] != 'X') && (GCodeString[string_index] != 'J') && (GCodeString[string_index] != 'I') && (GCodeString[string_index] != '\n') && (string_index + 1 <= GCodeString.length()))
					{
						DummyArray[array_index] = GCodeString[string_index];

						if (string_index + 1 <= GCodeString.length())
							string_index++;
						array_index++;
						count++;
					}
					string DummyString(DummyArray);
					XYIJPnts.YPnt = stod(DummyString);

					//Reset the Array for future use
					for (int i = 0; i < 20; i++)
						DummyArray[i] = 0;
				}

				//If it is a circle, extract IJ points
				if (GCodeString[count] == 'I')
				{
					unsigned int string_index = count + 1;		//Add 1 to it so we dont get the I, only want the decimal numbers
					int array_index = 0;				//Set decimal numbers in the index from 0 to how ever many decimal numbers there are		
					while ((GCodeString[string_index] != 'J') && (GCodeString[string_index] != '\n') && (string_index + 1 <= GCodeString.length()))
					{
						DummyArray[array_index] = GCodeString[string_index];

						if (string_index + 1 <= GCodeString.length())
							string_index++;
						array_index++;
						count++;
					}
					string DummyString(DummyArray);
					XYIJPnts.IPnt = stod(DummyString);

					//Reset the Array for future use
					for (int i = 0; i < 20; i++)
						DummyArray[i] = 0;
				}

				if (GCodeString[count] == 'J')
				{
					unsigned int string_index = count + 1;		//Add 1 to it so we dont get the J, only want the decimal numbers
					int array_index = 0;				//Set decimal numbers in the index from 0 to how ever many decimal numbers there are		
					while ((GCodeString[string_index] != 'I') && (GCodeString[string_index] != '\n') && (string_index + 1 <= GCodeString.length()))
					{
						DummyArray[array_index] = GCodeString[string_index];

						if (string_index + 1 <= GCodeString.length())
							string_index++;
						array_index++;
						count++;
					}
					string DummyString(DummyArray);
					XYIJPnts.JPnt = stod(DummyString);

					//Reset the Array for future use
					for (int i = 0; i < 20; i++)
						DummyArray[i] = 0;
				}

			}

			XYIJPntr[array_location].XPnt = XYIJPnts.XPnt;
			XYIJPntr[array_location].YPnt = XYIJPnts.YPnt;
			XYIJPntr[array_location].IPnt = XYIJPnts.IPnt;
			XYIJPntr[array_location].JPnt = XYIJPnts.JPnt;

			XYIJPnts.XPnt = XYIJPnts.YPnt = XYIJPnts.IPnt = XYIJPnts.JPnt = 0;
			array_location++;
		}
	}
	else
	{
		cout << "Not a G";
	}

	return XYIJPntr;
}


void Parser::setNumberOfLines()
{
	int      NumberOfLines = 0;
	string   Line;
	ifstream TxtFile("Sample_TestFile.txt");

	while (getline(TxtFile, Line))
		NumberOfLines++;

	number_of_lines = NumberOfLines;

}

int Parser::getNumberOfLines()
{
	return number_of_lines;
}

ParserPnts* Parser::ReadTxtFile()
{
	setNumberOfLines();
	
	return getGCodeInfo();
}

int Parser::getDirection(int count)
{
	return DirectionPtr[count];
}