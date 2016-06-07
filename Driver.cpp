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

void Driver::moveToNextWaypoint(double x, double y, Localization *loc) {
	robot->read();
	robot->read();
	double currX = robot->getXPosition();
	double currY = robot->getYPosition();
	double currYaw = robot->getYawPosition();
	double oldX = currX;
	double oldY = currY;
	double oldYaw = currYaw;
	Map m;
	double dist = distance(currX, currY, x, y);
	int div = 0;
	double angle = atan2(y - currY, x - currX);


	m.saveMapWithParticles(loc);
	// This calculation in the while is wrong

	while (abs((currYaw*180/M_PI) - angle*180/M_PI) > angleTolerange) {

			// here we need to calc how to rotate the robot - left or right
			int direction;
			double currYawFull = currYaw*180/M_PI;
			double angleFull = angle*180/M_PI;

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
			robot->setSpeed(0, yawSpeed*(direction));

			// read the robot angle again
			robot->read();

			currYaw = robot->getYawPosition();

			// sometimes update particles and print location
			div++;
			if(div % PARTICLE_UPDATE_RATE == 0){

				loc->Update(robot->getXPosition() - oldX,
								robot->getYPosition() - oldY,
								robot->getYawPosition() - oldYaw,
								robot->_lp, robot);


				m.saveMapWithParticles(loc);
				oldX = currX;
				oldY = currY;
				oldYaw = currYaw;
				div = 0;
				cout << "x: " << robot->getXPosition() << " y: " << robot->getXPosition() << " yaw: " << (currYaw) *180/ PI << endl;
			}
		}


	m.saveMapWithParticles(loc);

	// Move fast to until near obstacle
	while (distance(currX, currY, x, y) > slowSpeedRange) {
		robot->setSpeed(linearSpeed, 0);

		robot->read();

		currX = robot->getXPosition();
		currY = robot->getYPosition();
		currYaw = robot->getYawPosition();

		div++;
		if(div % PARTICLE_UPDATE_RATE == 0){

			loc->Update(robot->getXPosition() - oldX,
							robot->getYPosition() - oldY,
							robot->getYawPosition() - oldYaw,
							robot->_lp, robot);


			m.saveMapWithParticles(loc);
			oldX = currX;
			oldY = currY;
			oldYaw = currYaw;
			div = 0;
			cout << "x: " << robot->getXPosition() << " y: " << robot->getXPosition() << " yaw: " << (currYaw) *180/ PI << endl;
		}
	}

	// go slow until reach close to waypoint
	dist = distance(currX, currY, x, y);
	while (dist > tolerance) {
		robot->setSpeed(linearSpeed * slowSpeedRatio, 0);

		robot->read();

		div++;
		if(div % PARTICLE_UPDATE_RATE == 0){

			loc->Update(robot->getXPosition() - oldX,
							robot->getYPosition() - oldY,
							robot->getYawPosition() - oldYaw,
							robot->_lp, robot);
			oldX = currX;
			oldY = currY;
			oldYaw = currYaw;
			div = 0;
			m.saveMapWithParticles(loc);
			cout << "x: " << robot->getXPosition() << " y: " << robot->getXPosition() << " yaw: " << (currYaw) *180/ PI << endl;

		}

		currX = robot->getXPosition();
		currY = robot->getYPosition();
		currYaw = robot->getYawPosition();

		dist = distance(currX, currY, x, y);

		// if the robot moved past its point
		if (dist > slowSpeedRange) {
			// get a new angle to fix position
			angle = atan2(y - currY, x - currX);
			// change the robots angle
			while (abs((currYaw*180/M_PI) - angle*180/M_PI) > angleTolerange) {

				// here we need to calc how to rotate the robot - left or right
				int direction;
				double currYawFull = currYaw*180/M_PI;
				double angleFull = angle*180/M_PI;

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
//				// and rotate the robot a little

				robot->setSpeed(0, yawSpeed*(direction));

				// read the robot angle again
				robot->read();

				div++;
				if(div % PARTICLE_UPDATE_RATE == 0){

					loc->Update(robot->getXPosition() - oldX,
									robot->getYPosition() - oldY,
									robot->getYawPosition() - oldYaw,
									robot->_lp, robot);
					oldX = currX;
					oldY = currY;
					oldYaw = currYaw;
					div = 0;
					m.saveMapWithParticles(loc);
					cout << "x: " << robot->getXPosition() << " y: " << robot->getXPosition() << " yaw: " << (currYaw) *180/ PI << endl;

				}
				currYaw = robot->getYawPosition();
			}
		}
	}

	robot->setSpeed(0, 0);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}


