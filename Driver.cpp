/*
 * Driver.cpp
 *
 *  Created on: May 30, 2016
 *      Author: colman
 */

#include "Driver.h"
#include <cmath>
#include <unistd.h>

Driver::Driver(Robot *robot) : robot(robot) {

}

double Driver::distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}



void Driver::moveToNextWaypoint(double x, double y) {
	robot->read();
	robot->read();
	double currX = robot->getXPosition();
	double currY = robot->getYPosition();
	double currYaw = robot->getYawPosition();
	cout << "x: " << currX << ", y: " << currY << ", Yaw: " << currYaw * 180/PI<<  endl;
	double dist = distance(currX, currY, x, y);

	double angle4 = atan2(y - currY, x - currX);
	//double asd = angle4 *180/M_PI;


	// TODO: change the robot angle until it is looking for the next waypoint
	// This calculation in the while is wrong
	while (abs((currYaw*180/M_PI) - angle4*180/M_PI) > angleTolerange) {

		// here we need to calc how to rotate the robot - left or right
		int direction;
		double currYawFull = currYaw*180/M_PI;
		double angleFull = angle4*180/M_PI;

		// Change it to 360 instead of the unsigned way
		if (currYawFull < 0) {
			currYawFull += 360;
		}
		if (angleFull < 0) {
			angleFull += 360;
		}
		// Set the direction
		// right = 1, left = -1
		if ((angleFull - currYawFull) >= 0) {
			direction = 1;
		}
		else {
			direction = -1;
		}

		// and rotate the robot a little
		//robot->setSpeed(0, yawSpeed*((angle4)/abs(angle4)));
		robot->setSpeed(0, yawSpeed*(direction));

		// read the robot angle again
		robot->read();
		currYaw = robot->getYawPosition();

		cout << "yaw: " << (currYaw) *180/ PI << " fin: " << angle4 *180/PI << endl;
	}



	while (distance(currX, currY, x, y) > slowSpeedRange) {
		robot->setSpeed(linearSpeed, 0);

		robot->read();
		currX = robot->getXPosition();
		currY = robot->getYPosition();
		currYaw = robot->getYawPosition();
			cout << ">fast  " << currX << ", " << currY << ", Yaw: " <<
					currYaw*180/PI<<  "   TO: " << x << ", " << y << " dist: " << distance(currX, currY, x, y) << " tol: " << slowSpeedRange << endl;
	}
	robot->setSpeed(0, 0);


	dist = distance(currX, currY, x, y);
	while (dist > tolerance) {
		robot->setSpeed(linearSpeed * slowSpeedRatio, 0);

		robot->read();
		currX = robot->getXPosition();
		currY = robot->getYPosition();
		currYaw = robot->getYawPosition();
		cout << ">slow   " << currX << ", " << currY << ", Yaw: " <<
				currYaw *180/M_PI <<  "   TO: " << x << ", " << y << " dist: " << distance(currX, currY, x, y) << " tol: " << tolerance <<  endl;

		dist = distance(currX, currY, x, y);

		// if the robot moved past its point
		if (dist > slowSpeedRange) {
			// get a new angle to fix position
			angle4 = atan2(y - currY, x - currX);
			// change the robots angle
			while (abs((currYaw*180/M_PI) - angle4*180/M_PI) > angleTolerange) {

				// here we need to calc how to rotate the robot - left or right
				int direction;
				double currYawFull = currYaw*180/M_PI;
				double angleFull = angle4*180/M_PI;

				// Change it to 360 instead of the unsigned way
				if (currYawFull < 0) {
					currYawFull += 360;
				}
				if (angleFull < 0) {
					angleFull += 360;
				}
				// Set the direction
				// right = 1, left = -1
				if ((angleFull - currYawFull) >= 0) {
					direction = 1;
				}
				else {
					direction = -1;
				}

				// and rotate the robot a little
				//robot->setSpeed(0, yawSpeed*((angle4)/abs(angle4)));
				robot->setSpeed(0, yawSpeed*(direction));

				// read the robot angle again
				robot->read();
				currYaw = robot->getYawPosition();

				cout << "yaw: " << (currYaw) *180/ PI << " fin: " << angle4 *180/PI << endl;
			}

		}


	}

	robot->setSpeed(0, 0);

}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}


