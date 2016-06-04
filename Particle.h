/*
 * Particle.h
 *
 *  Created on: Jul 9, 2014
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Globals.h"
#include "Laser.h"
#include "robot.h"
#include "Map.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

class Particle
{
private:

	double _x;
	double _y;
	double _yaw;
	Map _map;
	double _belief;
	double probabilityMove(double deltaX, double deltaY, double deltaYaw);
	double probabilityMeasure(Robot* robot);
	double Gaussian(double mu, double sigma, double x);
	double distFromPoint(double x, double y);


public:
	Particle();

	void move(double deltaX, double deltaY, double deltaYaw);
	Particle create();
	double update(double deltaX, double deltaY, double deltaYaw, Robot* robot);
	double getBelief() const;
	Map& getMap();

	double getX() {return _x;};
	double getY(){return _y;};
	double getYaw(){return _yaw;};

	bool operator ==(const Particle& ref);
};

#endif /* PARTICLE_H_ */
