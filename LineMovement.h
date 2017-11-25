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
// Decelaration file for LineMovement class.
// 
// Revision History 
// 01/26/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#ifndef LINEMOVEMENT
#define LINEMOVEMENT
struct LinePointXY
{
	double X;
	double Y;
};

class LineMovement
{
private:

	LinePointXY Pt1;
	LinePointXY Pt2;

	LinePointXY *PntArray;

	double Length;
	double UnitStep;
	double AngleToGo;
	double Distiterator;

public:
	//Constructor to set a defalut Length and to initalize
	//an object of the class Line
	LineMovement();

	LinePointXY* move_in_line(double X1, double Y1, double X2, double Y2, double UnitStep);

	void    setLength(LinePointXY Pt1, LinePointXY Pt2);
	double  getLength();
	void    setNumberOfSteps();
	double  getAngleFromXY(LinePointXY Pt1, LinePointXY Pt2);
	double  getLineSteps();

	LinePointXY getNextPoint(double Angle, double Distiterator);

	void    NullPntArray()
	{
		PntArray = 0;
	}
	LinePointXY *getPntArray()
	{
		return PntArray;
	}

	~LineMovement();
};

#endif LINEMOVEMENT