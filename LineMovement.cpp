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
// The class calculates points required to make a line between two points.
// 
// Effects: 
// The expected ussage is: 
// 1. Enter starting point and ending point.
// 2. Calculations are made to determine points between the starting and ending points.
// 3. Calculated points are returned to be captured by "MathForRobotArm" object to
//    to communicate to the robot where to move.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#define _USE_MATH_DEFINES
#include "LineMovement.h"
#include "Rhino_Class.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

LineMovement::LineMovement()
{
	Length = 1;
}

LinePointXY* LineMovement::move_in_line(double X1, double Y1, double X2, double Y2, double UnitStepAmount)
{
	//Setting the points provided by the user into structures
	Pt1.X = X1;
	Pt1.Y = Y1;

	Pt2.X = X2;
	Pt2.Y = Y2;

	//Set the length of the between point 1 and point 2 
	setLength(Pt1, Pt2);
	//Set the the unit steps ammount that the user has input
	UnitStep = UnitStepAmount;

	//Display information for test purposes
	cout << "Length:     " << getLength() << endl;
	cout << "Angle :     " << getAngleFromXY(Pt1, Pt2) << endl;
	cout << "Unit Steps: " << getLineSteps() << endl;

	//Compute the angle that will be used to get to the point 2 from point 1
	AngleToGo = getAngleFromXY(Pt1, Pt2);

	//Get the number of steps that our robot will be moving in each direction by each arm
	setNumberOfSteps();

	return getPntArray();
}

void LineMovement::setLength(LinePointXY Pt1, LinePointXY Pt2)
{
	double XLen;
	double YLen;

	if (Pt1.X < 0)
	if (Pt2.X < 0)
		XLen = Pt1.X - Pt2.X;
	else
		XLen = -Pt1.X + Pt2.X;
	else

	if (Pt2.X < 0)
		XLen = Pt1.X + -Pt2.X;
	else
		XLen = Pt1.X - Pt2.X;

	if (Pt1.Y < 0) //neg

	if (Pt2.Y < 0)
		YLen = Pt1.Y + Pt2.Y;
	else
		YLen = -Pt1.Y - Pt2.Y;
	else
	if (Pt2.Y < 0)
		YLen = Pt1.Y + -Pt2.Y;
	else
		YLen = Pt1.Y - Pt2.Y;
	Length = sqrt(pow((XLen), 2) + pow((YLen), 2));
}

double LineMovement::getLength()
{
	return Length;
}

void LineMovement::setNumberOfSteps()
{
	//Variable to hold the size of the dynamically allocated array that will
	//hold all the xy positions that the robot will move to by intervals
	int size;

	Distiterator = (Pt2.X > Pt1.X) ? UnitStep : -UnitStep;
	LinePointXY PntXYHolder;
	size = getLineSteps();

	//Dynamically allocate the array
	PntArray = new LinePointXY[size];

	for (unsigned travers = 0; travers < getLineSteps(); travers++)
	{

		PntXYHolder = getNextPoint(AngleToGo, Distiterator);
		PntArray[travers].X = PntXYHolder.X;
		PntArray[travers].Y = PntXYHolder.Y;

		Distiterator += (Pt2.X > Pt1.X) ? UnitStep : -UnitStep;

		cout << fixed << showpoint << setprecision(1)
			<< "X: " << PntXYHolder.X << "   Y: " << PntXYHolder.Y << endl;
	}
	
}

double LineMovement::getAngleFromXY(LinePointXY Pt1, LinePointXY Pt2)
{
	//Changed the X and Y points because it was the wrong way
	double Rads = atan((Pt2.Y - Pt1.Y) / (Pt2.X - Pt1.X));
	return Rads;
}

double LineMovement::getLineSteps()
{
	return int(Length / UnitStep);
}

LinePointXY LineMovement::getNextPoint(double Angle, double Distiterator)
{
	LinePointXY ReturnXY;
	ReturnXY.X = (Distiterator * cos(Angle)) + Pt1.X;
	ReturnXY.Y = (Distiterator * sin(Angle)) + Pt1.Y;
	return ReturnXY;
}

LineMovement::~LineMovement()
{
	cout << "Destructor" << endl;
	if (PntArray != 0)
	{
		delete[] PntArray;
		PntArray = 0;
	}
}