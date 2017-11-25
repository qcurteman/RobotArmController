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
// Decelaration file for CircleMovement class.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#ifndef  MATHFORROBOTARM
#define  MATHFORROBOTARM
#include <iostream>
using namespace std;

//Structure holding the two angels of the arms
struct AnglePair
{
	double Angle1;
	double Angle2;
};

//Structure to hold the X and Y coordinates you would like
//the robotic arm to move to
struct XYCoord
{
	double XCoord;
	double YCoord;
};


class RoboticMath
{
private:

	//Variable names of the structures to hold values per each instance of the class that is created
	AnglePair AnglePairStruct;
	XYCoord   XY_Coord;

	//Length of the arms of the Robot
	double    ArmLength1;
	double    ArmLength2;

	//Theta2() will be called before Theta1() because Theta1() needs needs Theta2's angle
	void      Theta2();
	//Function to compute the angle of Theta1
	void      Theta1();

	//Function to convert radians to degrees
	double    ConvertToDegrees(double);
public:

	//Function to call the AnglePair structure to display their values
	AnglePair getAnglePair();

	RoboticMath();

	void setXYValues(double, double);
	void setArmLength(double, double);

};

#endif MATHFORROBOTARM