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
// Declaration file for the Rhino_Class
// 
// Revision History 
// 02/01/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#ifndef RHINO_CLASS
#define RHINO_CLASS
#include <iostream>
#include "tserial.h"
#include "MathForRobotArm.h"
#include "LineMovement.h"
using namespace std;

struct LineXY
{
	double Xcoord;
	double Ycoord;
};

class Rhino_Communication
{
private:
	double x_click_location, y_click_location;

	//Create an instance of the Tserial class in our private so our public functions can use it 
	//to communicate to the robot
	Tserial     SerialPort;

	//Instance of RoboticMath that will be used through out the functions
	RoboticMath Movement;

	LineMovement Line1;

	LineXY  CurrentPosition;
	LineXY* LineXYArray;

	//Function to figure out what the switches status' are
	bool   switch_status(char);
	//Function to determine what the motor status' are
	int    motor_status(int);

	//If the number of movements is over 127, it goes into this function
	//to be broken up into intervals of movements
	double move_intervals(double, int);

	//Function to determine if the robot needs to move 1 extra click to its xy-coord
	double decimal_movement(double);

	

public:

	//Function that can be used after the arm lengths have been set already to move the robot
	//back to the home position after already being used
	bool HomePosition(int, char);

	void HomeDirection(char, char);

	Rhino_Communication();

	Rhino_Communication(double, double);

	//Function to move the robot arms to an xy-coordinate
	double  move_to_xy(double, double);

	LineXY* CurrentPositionPntr;

};

#endif RHINO_CLASS