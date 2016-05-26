/*
 * Particle.cpp
 */

#include "Particle.h"
#include "ConfigurationManager.h"
#include "math.h"
#include "Globals.h"

Particle::Particle(double x, double y, double pYaw, double bel, int** map, int nGridWidth, int nGridHight) : _locationX(x), _locationY(y), _yaw(pYaw), _belief(bel), _particleMap(map), _GridWidth(nGridWidth), _GridHight(nGridHight)
{


}

Particle::~Particle()
{

}

void Particle::UpdateParticle(double deltaX, double deltaY, double deltaYaw, Robot* robot)
{
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double radYaw = (deltaYaw + _yaw);

	// Update robot location
	_locationX += (cos(radYaw) * distance);
	_locationY += (sin(radYaw) * distance);
	_yaw += deltaYaw;

	double progProb = calcProgressProb(deltaX, deltaY, deltaYaw);
	double obsProb = calcObsProb(robot);

	_belief *= COEFFICIENT * progProb * obsProb;

	if (_belief > 1)
		_belief = 1;
}


double Particle::getBelief()
{
	return _belief;
}

double Particle::calcProgressProb(double deltaX, double deltaY, double deltaYaw)
{
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double newProb = 0.2;

	if (deltaYaw == 0 && distance < MAX_PROB_DISTANCE)
	{
		newProb = 1;
	}
	else if ((deltaYaw < MAX_PROB_YAW) && (distance < MAX_PROB_DISTANCE))
	{
		newProb = 0.8;
	}
	else if (((deltaYaw < MAX_PROB_YAW) && (distance > MAX_PROB_DISTANCE)) ||
			((deltaYaw > MAX_PROB_YAW) && (distance < MAX_PROB_DISTANCE)))
	{
		newProb = 0.5;
	}

	return newProb;
}

double Particle::calcObsProb(Robot* robot)
{
	int hits = 0;
	int miss = 0;
	double dist;
	double currAngle;
	double diffX;
	double diffY;
	double curObsVal;

	ConfigurationMGR *pntConfiguration;
	pntConfiguration = pntConfiguration->getInstance();

	SetValFromRealLocation(_locationX, _locationY, 0);

	for (int i = 0; i < ANGLES_NUM; i++)
	{
		dist = robot->getLaserDistance(i);
		//cout << "dist in angle: " << i << " is " << dist << endl;

		currAngle = ((i * (0.36) - 120.0) / 180.0) * M_PI;
		double yawInRad = _yaw/180.0 * M_PI;

		// Calculating distance from obstacle
		diffX = dist * cos(yawInRad + currAngle);
		diffY = dist * sin(yawInRad + currAngle);

		// Setting the free spaces in the map
		for (double j = 0; j < 1 ; j += ((double)pntConfiguration->GridResolutionCM / 2.0))
		{
			SetValFromRealLocation(_locationX + (j * diffX) , _locationY + (j * diffY) , 0);
		}


		curObsVal = GetValFromRealLocation(diffX + _locationX, diffY + _locationY);

		// Calc hits, miss
		if (dist < MAX_OBS_DISTANCE)
		{
			SetValFromRealLocation(diffX + _locationX, diffY + _locationY, 1);

			if (curObsVal == 0)
				miss++;
			else if (curObsVal == 1)
				hits++;
		}
	}

	if (hits == 0)
		hits = 1;

	return (double)hits / (double)(hits + miss);
}


void Particle::SetValFromRealLocation(double x, double y, int value)
{
	ConfigurationMGR *pntConfiguration;
		pntConfiguration = pntConfiguration->getInstance();

	int xMapLocation = x / pntConfiguration->MapResolutionCM;
	int yMapLocation = y / pntConfiguration->MapResolutionCM;

	if (xMapLocation >= _GridWidth)
	{
		xMapLocation = _GridWidth - 1;
	}

	if (yMapLocation >= _GridHight)
	{
		yMapLocation = _GridHight - 1;
	}

	//cout << "puttig in " << xMapLocation << " , " << yMapLocation << " value " << value << endl;


	_particleMap[xMapLocation][yMapLocation] = value;
}


int Particle::GetValFromRealLocation(double x, double y)
{
	ConfigurationMGR *pntConfiguration;
		pntConfiguration = pntConfiguration->getInstance();


	int xMapLocation = x / pntConfiguration->MapResolutionCM;
	int yMapLocation = y / pntConfiguration->MapResolutionCM;

	if (xMapLocation >= _GridWidth)
	{
		xMapLocation = _GridWidth - 1;
	}

	if (yMapLocation >= _GridHight)
	{
		yMapLocation = _GridHight - 1;
	}

	return _particleMap[xMapLocation][yMapLocation];
}
