/*
 * Particles.cpp
 */

#include "Particle.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;


Particle::Particle(float xDelta, float yDelta, float yawDelta, float belief)
{
	this->xDelta = xDelta;
	this->yDelta = yDelta;
	this->yawDelta = yawDelta;
	this->belief = belief;

	this->age = 1;
}
// Create a new child-particle.
Particle* Particle::CreateChild(float expansionRadius, float yawRange)
{
    float newX = this->xDelta + Random(-expansionRadius, expansionRadius);
    float newY = this->yDelta + Random(-expansionRadius, expansionRadius);
    float newYaw = this->yawDelta + Random(-yawRange, yawRange);
    return new Particle(newX, newY, newYaw, -1);
}

// Update the particle
void Particle::Update(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy)
{
//	this->xDelta += xDelta;
//    this->yDelta += yDelta;
//    this->yawDelta += yawDelta;

    // Calculating the belief of the particle, by using the probability by movement and laser scan.
    float predictionBelif = ProbabilityByMovement(xDelta, yDelta, yawDelta) * this->belief;
    float probabilityByScan = ProbabilityByLaserScan(this->xDelta, this->yDelta, this->yawDelta, map, laserProxy);
    this->belief = probabilityByScan * predictionBelif * BELIEF_MAGIC_NUMBER;

    // In case the belief is more than 1, put 1 instead.
    while (abs(this->belief) > 1) {
    	this->belief /= 10;
    }
}

float Particle::Random(float min, float max)
{
    float num = (float)rand() / RAND_MAX;
    return min + num * (max - min);
}

// calculate the distance. the more the distance is shorter - the better probability.
float Particle::ProbabilityByMovement(float xDelta, float yDelta, float yawDelta)
{
	float distance = sqrt(pow(xDelta,2) + pow(yDelta,2));

	if (distance < 1)
		return 1;

	if (distance < 3)
		return 0.9;

	if (distance < 5)
		return 0.7;

	if (distance < 7)
		return 0.5;

	if (distance < 9)
		return 0.3;

	return 0.1;
}

// Get the probability of this particle by using the laser scan.
float Particle::ProbabilityByLaserScan(float xRobotDelta, float yRobotDelta, float yawRobotDelta, Map* map, LaserProxy* laserProxy)
{
	float probability = 0;

	// Measures the position of the
	for (unsigned int index = 0; index < laserProxy->GetCount(); index++)
	{
		double distance = laserProxy->GetRange(index);

		// Takes the distance of the indexed obstacle from the laser (and from the robot)
		// If the laser cannot seet an obstacle
		if (distance >= 25)
		{
			// let's move to the next sample
			continue;
		}

		double indexDegree = (index) * 0.36 - 120;
		double indexRadian = (indexDegree) *M_PI / 180;
		double obstacleRadian = indexRadian + yawRobotDelta;
		double obstacleX = distance * cos(obstacleRadian) + xRobotDelta;
		double obstacleY = distance * sin(obstacleRadian) + yRobotDelta;
		double distanceFromparticle = sqrt(pow(obstacleX - xDelta, 2) + pow(obstacleY - yDelta, 2));
		probability += distanceFromparticle;
	}

	return probability;


	float mapWidth = map->nMapWidth;
	float mapHeight = map->nMapHeight;

	float x = xDelta;
	float y = yDelta;

	int xCoord = floor(x);
	int yCoord = floor(y);

	// In case we are out of bound, return a low probability.
	if (x < 0 || x >= mapWidth ||
	    y < 0 || y >= mapHeight)
	{
		return 0;
	}

	int** grid = map->GridOfTheMap;

	// In case there is an obstacle in this point, return a low probability.
	if (grid[yCoord][xCoord] == 1)
	{
		return 0;
	}

	int scans = laserProxy->GetCount();
	float maxRange = laserProxy->GetMaxRange();

	float totalHits = 0;
	float correctHits = 0;
	int boundaryMisses = 0;
	int nfloorObstacleX;
	int nfloorObstacleY;

	for(int i=0; i < scans; i++)
	{
		float range = laserProxy->GetRange(i);

		if (range < maxRange)
		{
			totalHits++;

			float bearing = laserProxy->GetBearing(i);

			float rangeInPixels = range * 100 / 2.5;
			float yawInRadians = yawDelta * M_PI / 180.0;

			float obstacleX = xDelta + rangeInPixels * cos(yawInRadians + bearing);
			float obstacleY = yDelta - rangeInPixels * sin(yawInRadians + bearing);

			// Check if we missed boundaries.
			if ((obstacleX) < 0 || (obstacleX) >= mapWidth -10 ||
					obstacleY < 0 || (obstacleY) >= mapHeight -10)
			{
				boundaryMisses++;

				continue;
			}

			nfloorObstacleX = floor(obstacleX);
			nfloorObstacleY = floor(obstacleY);

			// Check if there's a hit on an obstacle.
			if (grid[nfloorObstacleY][nfloorObstacleX] == 1)
			{

				correctHits++;
			}
		}
	}

	float accuracy = correctHits / totalHits;

	return accuracy;
}

// Create child-particle.
Particle* Particle::CreateChild()
{
    return CreateChild(EXPANSION_RADIUS, YAW_RANGE);
}

float Particle::GetX()
{
    return xDelta;
}

float Particle::GetY()
{
    return yDelta;
}

float Particle::GetYaw()
{
    return yawDelta;
}
