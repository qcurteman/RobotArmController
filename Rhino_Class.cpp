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
// Communication with the Robotic arm
// 
// Effects: 
// The expected ussage is: 
// 1. Establish a connection with the Robotic arm
// 2. Move the arm to it's home position. (90 degree angle)
// 3. Handle requests for moving to XY Locations
// 
// Revision History 
// 02/01/2016 "Quentin Curteman" 
// - Original Version 
// 
//************************************************************************
#include <iostream>
#include <string> 
#include <Windows.h>
#include "Rhino_Class.h"
#include "tserial.h"
#include "MathForRobotArm.h"
using namespace std;

Rhino_Communication::Rhino_Communication(double L1, double L2)
{
	SerialPort.connect("COM1", 9600, spEVEN);
	CurrentPositionPntr = &CurrentPosition;

	Movement.setArmLength(L1, L2);
}

bool Rhino_Communication::switch_status(char motor)
{
	//Set the motor variable to either 1, 2, 3, 4, 5, or 6 to work
	//with the case statements
	motor -= 66;

	char switch_stat;
	//Array to hold the bit number that represents the motor character
	//C is 1 D is 2 E is 4 and so on
	int bit_array[6] = { 1, 2, 4, 8, 16, 32 };
	int bit_usage;

	switch (motor)
	{
	case 1: bit_usage = 0;
		break;
	case 2: bit_usage = 1;
		break;
	case 3: bit_usage = 2;
		break;
	case 4: bit_usage = 3;
		break;
	case 5: bit_usage = 4;
		break;
	case 6: bit_usage = 5;
		break;
	default: cout << "How did you make it say this?" << endl;
		break;
	}

	//Sending inqury to robot asking for the status of its switches
	SerialPort << 'I';
	//Give the robot a minute
	Sleep(5);

	SerialPort >> switch_stat;
	switch_stat -= 32;

	if (switch_stat & bit_array[bit_usage])
	{
		(switch_stat & motor);
		return 1;
	}
	else
	{
		(switch_stat & motor);
		return 0;
	}
}

//Function to display the status of the motor
int Rhino_Communication::motor_status(int count)
{
	char motor_stat_array[2][3] = { { 'D', '?', '\0' },
									{ 'E', '?', '\0' }};
	char response;
	Sleep(5);

	SerialPort << motor_stat_array[count];

	Sleep(5);

	response = SerialPort.getChar() - 32;

	return response;
}

void Rhino_Communication::HomeDirection(char motor, char Direction)
{
	if (motor == 'D')
	{
		if (Direction == '+')
			HomePosition(0, '+');
		else
			HomePosition(0, '-');
	}
	else
	{
		if (Direction == '+')
			HomePosition(1, '+');
		else
			HomePosition(1, '-');
	}
}

bool Rhino_Communication::HomePosition(int motor, char Direction)
{
	//2D array to store the information to send the motors to their home positions
	char robotArray[2][4] = { { 'D', '+', '1', '\0' },
							  { 'E', '-', '1', '\0' } };
	
	robotArray[0][1] = Direction;
	robotArray[1][1] = Direction;

	//Variable to store whether the robot is home or not. 0 not home, 1 home
	bool Home = 0;

	//for loop that checks if the robot is home and reacts accordingly
		if (switch_status(robotArray[motor][0]))
		{
			do
			{
				cout << motor_status(motor) << endl;
				SerialPort << robotArray[motor];
			} while(switch_status(robotArray[motor][0]));
		}
	
	//Set the location of X and Y's click status to 
	//750 each meaning that both angles are at 90 degrees
	x_click_location = 750;
	y_click_location = 750;
	CurrentPosition.Xcoord = 9;
	CurrentPosition.Ycoord = 9;

	return Home;
}

double Rhino_Communication::move_to_xy(double X, double Y)
{

	double tempDistance1, tempDistance2;

	Movement.setXYValues(X, Y);

	CurrentPosition.Xcoord = X;
	CurrentPosition.Xcoord = Y;

	AnglePair AnglePairStruct1;

	AnglePairStruct1 = Movement.getAnglePair();

	cout << "Angle1: " << AnglePairStruct1.Angle1 << " Angle2: " << AnglePairStruct1.Angle2 << endl;

	//Divide the angles by how much 1 clicks movement is based on the motor being moved
	tempDistance1 = AnglePairStruct1.Angle1 / .12;
	tempDistance2 = AnglePairStruct1.Angle2 / .12;

	cout << "distance E: " << tempDistance1 << " distance D: " << tempDistance2 << endl;

	//Move motor E
	move_intervals(tempDistance1, 1);

	//Move motor D
	move_intervals(tempDistance2, 0);

	return 0;
}

double Rhino_Communication::move_intervals(double num_of_clicks, int motor)
{
	//Array holding the amount the robot will move per interval
	char temp_movement[5] = { '0', '0', '0', '2', '\0' };
	char extra_movement[4] = { '0', '0', '0', '\0' };

	//Variable to hold the number of times the motor of choice will move by 10 clicks
	int  movement_amount;

	//Variable that will hold the ammount the robot needs to move toward the desired location
	double temp_move_amount;

	//Variable to hold the amount left over from the number of clicks needed to move
	int  extra_moves;

	//When motor == 1 it is going to move motor E, otherwise move motor D
	if (motor == 1)
	{
		temp_movement[0]  = 'E';
		extra_movement[0] = 'E';
	}
	else
	{
		temp_movement[0] = 'D';
		extra_movement[0] = 'D';
	}

	//If the number of movements is 0 then do nothing
	if (num_of_clicks == 0)
	{
		return 0;
	}
	//If the number is greater than 0 break it up into intervals
	else
	{
		//Determining which way to go from the home postition
		if (motor == 1)
		{
			if (num_of_clicks < x_click_location)
			{
				temp_move_amount = x_click_location - num_of_clicks;
				x_click_location = num_of_clicks;
				temp_movement[1] = '+';
				extra_movement[1] = '+';

				//Compensation for D motor
				y_click_location -= temp_move_amount;

			}
			else
			{
				temp_move_amount = num_of_clicks - x_click_location;
				x_click_location = num_of_clicks;
				temp_movement[1] = '-';
				extra_movement[1] = '-';

				//Compensation for D motor
				y_click_location += temp_move_amount;

			}
		}
		else 
		{
			if (num_of_clicks < y_click_location)
			{
				temp_move_amount = y_click_location - num_of_clicks;
				y_click_location = num_of_clicks;
				temp_movement[1] = '+';
				extra_movement[1] = '+';
			}
			else
			{
				temp_move_amount = num_of_clicks - y_click_location;
				y_click_location = num_of_clicks;
				temp_movement[1] = '-';
				extra_movement[1] = '-';
			}
		}

		//If the decimal amount is greater than 5, add one to num_of_clicks to make sure
		//that if it rounds up to 10, later when the extra is added 
		//through the modulus, it doesn't add 9 when it should add 0
		temp_move_amount += decimal_movement(temp_move_amount);

		//Make these two variables equal to each other so that the
		//compensation movement will be the same amount
		movement_amount = static_cast<int>(temp_move_amount) / 2;

		/*********************************************************/
		/*****************MOVMENT OF THE MOTORS*******************/
		/*********************************************************/

		while (movement_amount > 0)
		{
			SerialPort << temp_movement;
			movement_amount--;

			while (motor_status(motor) > 0)
			{
				Sleep(5);
			}
		}


		/*********************************************************/
		/*********************EXTRA MOVEMENT**********************/
		/*********************************************************/

		extra_moves = static_cast<int>(temp_move_amount) % 2;
		extra_moves += 48;
		extra_movement[2] = static_cast<char>(extra_moves);
		SerialPort << extra_movement;

		
		cout << "X click Location: " << x_click_location << " Y click Location: " << y_click_location << endl;

		return 0;
	}
}

double Rhino_Communication::decimal_movement(double num_of_clicks)
{
	int tempMovement;
	num_of_clicks /= 10.0;
	tempMovement = 10.0 * (num_of_clicks - static_cast<int>(num_of_clicks));

	if (tempMovement > 4.0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}