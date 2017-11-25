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
// This is the Main to run the whole program
// 
// Effects: 
// The expected ussage is: 
// 1. User enters information about robot arm lengths
// 2. Home Robot Arms
// 3. Move either to a point or a line
// 
// Revision History 
// 03/18/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#include <iostream>
#include <string> 
#include <Windows.h>
#include "Rhino_Class.h"
#include "tserial.h"
#include "MathForRobotArm.h"
#include "LineMovement.h"
#include "CircleMovement.h"
#include "Parser.h"
using namespace std;

/*G-CODE NOTES

Standard input: G01X7.34Y3.667

Always has a G then a 0 after and then the third number determines if it is a line or a circle

1= move in line
2= move in circle clockwise
3= move in circle counterclockwise

example of move in circle

G03X6.3544Y3.221I9.04J6.784

XY are points to move to
IJ are are the center point of the circle


Steps to run the G code class

1) open the file
2) read first character in file. If it's a G continue
3) Peek skip next character and peek at 3rd character. 
4) if 1, move in line. If 2, move in circle clockwise. If 3, move in circle counterclocksise
5) Make a function with overloaded parameters so if 1 is needed, then use that one and if 2 or 3 is needed enter more numbers
6) Peek at 4th character to determine if it is an XY or IJ
7) Determined from step 6, peek at as many characters after the 4th character that are numbers unitl you get to another character and repeat
*/


int main()
{
	//Variables to hold information from the user
	double Arm1, Arm2;
	double x_coord, y_coord;

	char Direction, motor;

	int again = 1;
	int MovementChoice;

	cout << "What is the length of Arm 1?: ";
	cin >> Arm1;
	cout << "What is the length of Arm 2?: ";
	cin >> Arm2;

	Rhino_Communication RobotStatus(Arm1, Arm2);
	LineMovement        Line1;
	CircleMovement      Circle1;
	Parser              GCodeEntry;

	//Move first robot arm home
	cout << "Home      \n";
	cout << "Motor:     (E/D): ";
	cout << "Direction: (+/-): ";
	cout << endl;
	system("pause");

	//Move second robot arm home
	cout << "Home      \n";
	cout << "Motor:     (E/D): ";
	cout << "Direction: (+/-): ";
	cout << endl;
	system("pause");
	
	ParserPnts    *GCodePntr   = GCodeEntry.ReadTxtFile();
	LinePointXY   *LinePntr;
	CirclePointXY *CirclePntr;
	CirclePointXY *CirclePntr2;

	for (unsigned int index = 0; index < GCodeEntry.getNumberOfLines(); index++)
	{
		int Q = GCodeEntry.getDirection(index);

		//If the GCode wants to draw a line
		if ((GCodePntr->IPnt == 0) && (GCodePntr->JPnt == 0))
		{
										  //Current Position                 X                                        Y
			LinePntr = Line1.move_in_line(RobotStatus.CurrentPositionPntr->Xcoord, RobotStatus.CurrentPositionPntr->Ycoord, 
										  GCodePntr->XPnt, GCodePntr->YPnt, .05);//Moving to this XY point from current position and the divisor

			for (int count = 0; count < Line1.getLineSteps(); count++)
			{
				RobotStatus.move_to_xy(LinePntr->X, LinePntr->Y);
				LinePntr++;
			}
			delete[] Line1.getPntArray();
			Line1.NullPntArray();
		}
		//If the GCode wants to draw a circle
		else
		{										//Current Position                  X                                      Y
			CirclePntr = Circle1.move_in_circle(RobotStatus.CurrentPositionPntr->Xcoord, RobotStatus.CurrentPositionPntr->Ycoord, 
												GCodePntr->XPnt, GCodePntr->YPnt, //Moving to this XY point from current position
												GCodePntr->IPnt, GCodePntr->JPnt, //Center Point of the desired circle
												GCodeEntry.getDirection(index), .125); //Clockwise or counterclockwise and divisor
			CirclePntr2 = CirclePntr;

			for (int i = 0; i < Circle1.getNumberOfSteps(); i++)
			{
				while ((i + 1) < Circle1.getNumberOfSteps())
				{
					CirclePntr2++;
					break;
				}

				//Call function to create all the point intervals in a dynamically allocated array
				LinePntr = Line1.move_in_line(CirclePntr->PointX, CirclePntr->PointY, CirclePntr2->PointX, CirclePntr2->PointY, .05);

				for (int count = 0; count < Line1.getLineSteps(); count++)
				{
					RobotStatus.move_to_xy(LinePntr->X, LinePntr->Y);
					LinePntr++;
				}
				CirclePntr++;
				delete[] Line1.getPntArray();
				Line1.NullPntArray();
			}
		}
		GCodePntr++;
	}


	//Move first robot arm home
	cout << "Home      \n";
	cout << "Motor:     (E/D): ";
	cin >> motor;
	cout << "Direction: (+/-): ";
	cin >> Direction;
	RobotStatus.HomeDirection(motor, Direction);
	cout << endl;
	system("pause");

	//Move second robot arm home
	cout << "Home      \n";
	cout << "Motor:     (E/D): ";
	cin >> motor;
	cout << "Direction: (+/-): ";
	cin >> Direction;
	RobotStatus.HomeDirection(motor, Direction);
	cout << endl;
	system("pause");

	return 0;
}