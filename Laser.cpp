/*
 * Laser.cpp
 *
 *  Created on: May 27, 2014
 *      Author: user
 */

#include "Laser.h"

double Laser::convertIndexToDegree(int index) const
{
	return (index * 0.36) - 120;
}

int Laser::convertDegreeToIndex(double degree) const
{
	return (degree + 120) / 0.36;
}

void Laser::getObstacles(double x, double y, double yaw, vector<Point>& obstacles) const
{
	// Clear the data structure
	obstacles.clear();

	for (unsigned int index = 0; index < _laserProxy.GetCount(); index++)
	{
		double distance = _laserProxy[index] * 10;

		// If the laser cannot seet an obstacle
		if (distance >= 25)
		{
			// let's move to the next sample
			continue;
		}

		double indexDegree = convertIndexToDegree(index);
		double indexRadian = indexDegree*M_PI/180;

		double obstacleRadian = indexRadian + yaw;

		double obstacleX = distance * cos(obstacleRadian) + x;
		double obstacleY = distance * sin(obstacleRadian) + y;

		Point point(obstacleX, obstacleY);

		obstacles.push_back(point);
	}
}

