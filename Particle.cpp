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
Particle* Particle::CreateChild(float expansionRadius, float yawRange, Map* map)
{
    float newX = this->xDelta + Random(-expansionRadius, expansionRadius);
    float newY = (this->yDelta + Random(-expansionRadius, expansionRadius));
    float newYaw = this->yawDelta + Random(-yawRange, yawRange);

    while (((newX) < 0|| (newX) >= map->nMapWidth -10 ||
           -newY < 0 || (-newY) >= map->nMapHeight -10)||
        		   map->GridOfTheMap[(int)-newY][(int)newX] == 1){
    	newX = this->xDelta + Random(-expansionRadius, expansionRadius);
        newY = (this->yDelta + Random(-expansionRadius, expansionRadius));
    }

    return new Particle(newX, newY, newYaw, 0.51);
}

// Update the particle
void Particle::Update(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy, Robot* rob)
{
	this->xDelta += xDelta;
    this->yDelta += yDelta;
    this->yawDelta += yawDelta;

    double probByRobotDistance = 1 / sqrt(pow(this->yDelta - rob->getYPosition(), 2) - pow(this->xDelta - rob->getXPosition(), 2));

    // if the particle is out of the map or on obstacle
    if ((this->xDelta) < 0 || (this->xDelta) >= map->nMapWidth -10 ||
        -this->yDelta < 0 || (-this->yDelta) >= map->nMapHeight -10){
    	this->Respawn(map);
    }
    else if (map->GridOfTheMap[(int)-this->yDelta][(int)this->xDelta] == 1) {
    	this->Respawn(map);
    }
    else {

		// Calculating the belief of the particle, by using the probability by movement and laser scan.
		float predictionBelif = ProbabilityByMovement(xDelta, yDelta, yawDelta);// * this->belief;
		float probabilityByScan = ProbabilityByLaserScan(this->xDelta, this->yDelta, this->yawDelta, map, laserProxy, rob);
		this->belief = probabilityByScan * predictionBelif * BELIEF_MAGIC_NUMBER;
    }
}

void Particle::Respawn(Map * map) {
	this->xDelta = (rand() % map->nMapWidth);
	this->yDelta = -(rand() % map->nMapHeight);
	double yaw = rand() % (int)(2*M_PI);
	this->belief = 0.1;
	while (map->GridOfTheMap[(int)-this->yDelta][(int)this->xDelta] == 1){
		this->xDelta = (rand() % map->nMapWidth);
		this->yDelta = -(rand() % map->nMapHeight);
	}
}

float Particle::Random(float min, float max)
{
    return (max - min ) * ((float)rand() / (float)RAND_MAX )  + min;
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
float Particle::ProbabilityByLaserScan(float xRobotDelta, float yRobotDelta, float yawRobotDelta, Map* map, LaserProxy* laserProxy, Robot* rob)
{
	float totalHits = 0;
	float correctHits = 0;

	// Measures the position of the
	for (unsigned int index = 0; index < LASER_COUNT; index++)
	{
		double distance = laserProxy->GetRange(index)*10;

		// Takes the distance of the indexed obstacle from the laser (and from the robot)
		// If the laser cannot see an obstacle
		if (distance < 40)
		{
			// let's move to the next sample
			continue;
		}
		totalHits++;
		double indexDegree = (index) * 0.36 - 120;
		double indexRadian = (indexDegree) *M_PI / 180;
		double obstacleRadian = indexRadian + rob->getYawPosition();// ;
		double obstacleX = distance * cos(obstacleRadian) + xDelta;
		double obstacleY = distance * sin(obstacleRadian) + yDelta;


		// Check if we missed boundaries.
		if ((obstacleX) < 0 || (obstacleX) >= map->nMapWidth -10 ||
			 -obstacleY < 0 || (-obstacleY) >= map->nMapHeight -10)
		{
			continue;
		}

		// Check if there's a hit on an obstacle.
		if (map->GridOfTheMap[(int)-obstacleY][(int)obstacleX] == 1)
		{
			correctHits++;
		}

	}

	if (totalHits == 0)
		return 0;
	else
		return correctHits/totalHits;

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
