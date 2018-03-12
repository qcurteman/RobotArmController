# RobotArmController

Claw arm Program (Example of game programming) Spring 2016

## Description:
- This was a class project where I learned advanced C++ techniques by creating a group of programs to control a robotic arm.
- I was able to apply the math I learned in calculus and linear algebra into this program to calculate points to draw lines and circles.
- I was able to create multiple classes that all worked together to draw pictures using the robotic arm onto a whiteboard.

## Process: 
- First, I created the classes “Rhino_Class” and “MathForRobotArm” which handle moving the robot arm to its home position and moving the robot to a XY position.
- Next, I made the class “LineMovement”. This class reads in two points, a starting point and an ending point, and calculates points in between the starting and ending points to draw a line.
- Next, I made the class “CircleMovement” that uses a starting point, ending point, and center point of a circle to calculate multiple lines needed to create the arc. These points are then sent to a “LineMovement” object to draw the arc.
- The final class that I made was the “Parser” class. This class reads in a text file that is composed of G-Codes. This is a special language created for drawing pictures. The class parses the G-Codes to determine what points to send to the “CircleMovement” class.

## Difficulties Faced:
- This was the class that our teacher introduced pointers. I struggled for a while with understanding how they worked, but eventually I was able to figure out how to use them to increment arrays.

## New Skills Acquired:
- I think that the best skill I learned from this was how to create and communicate between classes in a big project. It was very cool having every class working together.
- I learned some basics of game programming by considering the robotic arm to be an avatar and controlling it with my program. 
- I learned how to implement algorithms into my program to produce data. I used the equations for a circle and a line to produce points in terms of x, y positions, and then use that data to control the robotic arm.

## Pictures!
<img width="858" alt="mainpic" src="https://user-images.githubusercontent.com/28938321/33309485-1c626428-d3d3-11e7-8174-edec0f411c4c.png">
<img width="721" alt="circle" src="https://user-images.githubusercontent.com/28938321/33309483-1ad9641c-d3d3-11e7-81b6-fdc1a993dc41.png">
