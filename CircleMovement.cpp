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
// This class calculates the points along an arc. 
// 
// Effects: 
// The expected ussage is: 
// 1. Enter a starting location, ending location and center point of a circle to create an arc.
// 2. Calculations are made to determine all the points that are needed to create the arc.
// 3. Points are returned to then be captured by a "LineMovement" object to 
//    calculate the line made between each point along the arc.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#define  _USE_MATH_DEFINES
#include "CircleMovement.h"
#include <iostream>
#include <cmath>

using namespace std;

void CircleMovement::setStartXY(double X, double Y)
{
	StartLocation.PointX = X;
	StartLocation.PointY = Y;
}

void CircleMovement::setEndXY(double X, double Y)
{
	EndLocation.PointX = X;
	EndLocation.PointY = Y;
}

void CircleMovement::setDirection(int direc)
{
	if (direc == 3)
		direction = false;
	else
		direction = true;
}

void CircleMovement::setDivisor(double divisor)
{
	step_divisor = divisor;
}

CircleMovement::CircleMovement()
{
	radius = 1;
	step_divisor = 1;
	CircleCenter.PointX = 1;
	CircleCenter.PointY = 1;
}

void CircleMovement::setRadius()
{
	radius = sqrt(pow((CircleCenter.PointX - StartLocation.PointX), 2) + pow((CircleCenter.PointY - StartLocation.PointY), 2));
}

void CircleMovement::setCircleCenter(double X, double Y)
{
	CircleCenter.PointX = X;
	CircleCenter.PointY = Y;
}

void CircleMovement::setNumberOfSteps()
{
	double tempStartAngle, tempEndAngle;
	number_of_steps = 0;

	//Calculate the starting angle and ending angle baised on what our starting points and ending points are
	StartAngle = (acos((StartLocation.PointX - CircleCenter.PointX) / radius));
	EndAngle   = (acos((EndLocation.PointX - CircleCenter.PointX) / radius));

	//If user wants to draw a complete circle, add PI (180 degrees) to compensate for more movement
	if ((StartLocation.PointX == EndLocation.PointX) && (StartLocation.PointY == EndLocation.PointY))
	{
		EndAngle += M_PI;
	}

	tempStartAngle = StartAngle;
	tempEndAngle = EndAngle;

	//Set the number of steps to be move by subtracting our step_divisor from our starting
	//angle until our starting angle is less than our Ending angle 
	tempEndAngle = -tempEndAngle;
	while (tempStartAngle > tempEndAngle)
	{
		tempStartAngle -= step_divisor;
		number_of_steps++;
	}
}

int CircleMovement::getNumberOfSteps()
{
	return number_of_steps;
}

CirclePointXY* CircleMovement::move_in_circle(double StartX, double StartY, double EndX, double EndY, double CntrX, double CntrY, int direc, double divisor)
{
	setStartXY(StartX, StartY);
	setEndXY(EndX, EndY);
	setDirection(direc);
	setDivisor(divisor);
	setCircleCenter(CntrX, CntrY);
	setRadius();

	setNumberOfSteps();

	//Size variable to hold the number of times our for loop will iterate
	int size = getNumberOfSteps();

	double tempAngle = StartAngle;

	CircleXYStep = new CirclePointXY[size];
	//Counter Clockwise
	if (!direction)
	{
		setCounterClockwisePoints(StartX, StartY, EndX, EndY, CntrX, CntrY);
	}

	for (int count = 0; count < size; count++)
	{
		CircleXYStep[count].PointX = CircleCenter.PointX + (radius * cos(tempAngle));
		CircleXYStep[count].PointY = CircleCenter.PointY + (radius * sin(tempAngle));
		tempAngle -= step_divisor;
	}


	return CircleXYStep;
}

void CircleMovement::setCounterClockwisePoints(double StartX, double StartY, double EndX, double EndY, double CenterX, double CenterY)
{
	double slope = 0;
	double y_intercept = 0;
	double variable = 0;

	slope = (EndY - StartY) / (EndX - StartX);
	y_intercept = EndY - (slope * EndX);

	variable = (CenterX + ((CenterY - y_intercept) * slope)) / (1 + pow(slope, 2));

	CircleCenter.PointX = (2 * variable) - CenterX;
	CircleCenter.PointY = (2 * variable * slope) - CenterY + (2 * y_intercept);
}

CircleMovement::~CircleMovement()
{
	delete[] CircleXYStep;
}