/*
 * Driver.h
 *
 *  Created on: May 30, 2016
 *      Author: colman
 */

#ifndef DRIVER_H_
#define DRIVER_H_
#include "robot.h"
#include <math.h>

#define PI 3.14159265

class Driver {
private:
	const double angleTolerange = 1;
	const double tolerance = 0.2;
	const double slowSpeedRange = 10 * tolerance;
	const double linearSpeed = 0.3;
	const double yawSpeed = 0.2;
	const double slowSpeedRatio = 0.1;

	Robot *robot;
	double distance(double x1, double y1, double x2, double y2);

public:
	Driver(Robot *robot);
	void moveToNextWaypoint(double x, double y);
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
