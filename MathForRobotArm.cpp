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
// This program finds the angles on a robotic arm 
// 
// Effects: 
// The expected ussage is: 
// 1. Enter in length of 2 arms on robot 
// 2. Enter in desired x and y position 
// 3. Return the angles calculated
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "MathForRobotArm.h"
using namespace std;

RoboticMath::RoboticMath()
{
	ArmLength1 = 0;
	ArmLength2 = 0;

	XY_Coord.XCoord = 0;
	XY_Coord.YCoord = 0;
}

void RoboticMath::setXYValues(double X, double Y)
{
	XY_Coord.XCoord = X;
	XY_Coord.YCoord = Y;
}

void RoboticMath::setArmLength(double L1, double L2)
{
	ArmLength1 = L1;
	ArmLength2 = L2;
}

void RoboticMath::Theta2()
{
	//Calculating the Angle of Theta2
	AnglePairStruct.Angle2 = acos((pow(XY_Coord.XCoord, 2.0)
		+ pow(XY_Coord.YCoord, 2.0) - ((pow(ArmLength1, 2.0)
		+ pow(ArmLength2, 2.0)))) / (2.0 * ArmLength1 * ArmLength2));
}

void RoboticMath::Theta1()
{
	//Calculating the Angle of Theta1
	AnglePairStruct.Angle1 = (asin((ArmLength2 * sin(AnglePairStruct.Angle2)) /
		(sqrt(pow(XY_Coord.XCoord, 2.0)
		+ pow(XY_Coord.YCoord, 2.0)))))
		+ (atan(XY_Coord.YCoord / XY_Coord.XCoord));
}

AnglePair RoboticMath::getAnglePair()
{
	//Call functions to solve for our 2 angles
	Theta2();
	Theta1();

	//Change the 2 angles recieved into degrees
	AnglePairStruct.Angle1 = ConvertToDegrees(AnglePairStruct.Angle1);
	AnglePairStruct.Angle2 = ConvertToDegrees(AnglePairStruct.Angle2);

	return AnglePairStruct;
}

double RoboticMath::ConvertToDegrees(double Angle)
{
	double AngleInDegrees;

	return AngleInDegrees = Angle * (180 / M_PI);
}