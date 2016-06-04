/*
 * Laser.h
 *
 *  Created on: May 27, 2014
 *      Author: user
 */

#ifndef LASER_H_
#define LASER_H_

#include <math.h>
#include <libplayerc++/playerc++.h>
#include "Point.h"
#include "Map.h"

#include <vector>

using namespace PlayerCc;
using namespace std;


class Map;

class Laser
{

private:


	double convertIndexToDegree(int index) const;
	int convertDegreeToIndex(double degree) const;

public:
	LaserProxy& _laserProxy;
	Laser(LaserProxy& laserProxy) : _laserProxy(laserProxy)
	{
	}

	
	void getObstacles(double x, double y, double yaw, vector<Point>& obstacles) const;


	virtual ~Laser()
	{
	}
};

#endif /* LASER_H_ */
