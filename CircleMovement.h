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
#ifndef CIRCLEMOVEMENT
#define CIRCLEMOVEMENT

struct CirclePointXY
{
	double PointX;
	double PointY;
};

class CircleMovement
{
private:

	//Vertex Point of the desired circle
	CirclePointXY CircleCenter;
	//Start XY point of the circle
	CirclePointXY StartLocation;
	//Ending XY point of the circle
	CirclePointXY EndLocation;
	//Pointer to hold all the points that the circle will hold
	CirclePointXY *CircleXYStep;

	//Radius
	double radius;
	//Value that determines how many steps will be in between each point
	double step_divisor;
	double StartAngle;
	double EndAngle;
	double angle_steps;
	//Number of steps that are required to go from point A to point B
	int    number_of_steps;

	//Clockwise or counterclockwise
	//User enter 0 = Clockwise 1 = Counterclockwise
	bool   direction;

	void   setCounterClockwisePoints(double, double, double, double, double, double);
	void   setStartXY(double, double);
	void   setEndXY(double, double);
	void   setDirection(int);
	void   setDivisor(double);
	void   setNumberOfSteps();
	void   setRadius();
	void   setCircleCenter(double, double);

public:

	CircleMovement();
    
	//Get the number of steps require to complete the circle
	int  getNumberOfSteps();
	//							  StrtX   StrtY   EndX    EndY    CntrX   CntrY   Direc UnitSteps
	CirclePointXY* move_in_circle(double, double, double, double, double, double, int, double);

	//Destructor to delete the dynamically allocated array created to hold the circle points
	~CircleMovement();
};

#endif CIRCLEMOVEMENT