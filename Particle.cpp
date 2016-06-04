#include "Particle.h"

Particle::Particle() :
	_map()
{
	_belief = 1;
	_x = 0;
	_y = 0;
	_yaw = 0;
}

double Particle::probabilityMove(double deltaX, double deltaY, double deltaYaw)
{
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	double absoluteYaw = abs(deltaYaw);

	if ((absoluteYaw == 0) && (distance < PARTICLE_PROB_MOV_DISTANCE))
	{
		return 1;
	}
	else if ((distance < PARTICLE_PROB_MOV_DISTANCE) && (absoluteYaw < PARTICLE_PROB_MOV_YAW))
	{
		return 0.8;
	}
	else if (((distance > PARTICLE_PROB_MOV_DISTANCE) && (absoluteYaw < PARTICLE_PROB_MOV_YAW)) ||
			 ((distance < PARTICLE_PROB_MOV_DISTANCE) && (absoluteYaw > PARTICLE_PROB_MOV_YAW)))
	{
		return 0.6;
	}

	return 0.2;
}

double Particle::probabilityMeasure(Robot* robot)
{
	int hits = 0;
	int miss = 0;
	double dist;
	double currAngle;
	double diffX;
	double diffY;
	double curObsVal;

	double prob = 1;

	for (unsigned int index = 0; index < robot->getLaserCount(); index++)
	{
		double distance = robot->getLaserDistance(index);
		// If the laser cannot seet an obstacle
		if (distance >= 25)
		{
			// let's move to the next sample
			continue;
		}
		double indexDegree = (index) * 0.36 - 120;
		double indexRadian = (indexDegree) *M_PI / 180;
		double obstacleRadian = indexRadian + robot->getYawPosition();
		double obstacleX = distance * cos(obstacleRadian) + robot->getXPosition();
		double obstacleY = distance * sin(obstacleRadian) + robot->getYPosition();
//		m.putPixel(obstacleX, obstacleY);
		dist = distFromPoint(obstacleX, obstacleY);

		double var = Gaussian(dist, 5, distance);
		prob *= var;
	}

	//SetValFromRealLocation(_locationX, _locationY, 0);

//	for (int i = 0; i < ANGLES_NUM; i++)
//	{
//		dist = robot->getLaserDistance(i);
//		cout << "dist in angle: " << i << " is " << dist << endl;
//
//		currAngle = ((i * (0.36) - 120.0) / 180.0) * M_PI;
//		double yawInRad = _yaw/180.0 * M_PI;
//
//		// Calculating distance from obstacle
//		diffX = dist * cos(yawInRad + currAngle);
//		diffY = dist * sin(yawInRad + currAngle);
////		double yPos = (sin(pp.GetYaw()*(180/PI) - SENSORS_ANGLES[i]) * sp[i]) + pp.GetYPos();
////		double xPos = (cos(pp.GetYaw()*(180/PI) - SENSORS_ANGLES[i]) * sp[i]) + pp.GetXPos();
//
//		_belief *= distFromPoint(diffX, diffY);
//	}

	return prob;

}

double Particle::Gaussian(double mu, double sigma, double x){
	double ret = exp(-pow(mu-x,2)/pow(sigma, 2)/2)/sqrt(2*M_PI*pow(sigma, 2));
	return ret;
}

double Particle::distFromPoint(double x, double y) {
	return sqrt(pow(_x - x, 2) + pow(_y - y, 2));
}

void Particle::move(double deltaX, double deltaY, double deltaYaw)
{
	_x += deltaX;
	_y += deltaY;
	_yaw += deltaYaw;
}

double Particle::update(double deltaX, double deltaY, double deltaYaw, Robot* robot)
{
	// ---------------
	// Update Particle x, y, yaw
	move(deltaX, deltaY, deltaYaw);

	double probability = probabilityMove(deltaX, deltaY, deltaYaw);
	double previewsBelief = _belief * probability;

//	// ---------------
//	// Update Map
//
//	double matchPercent;
//	try
//	{
//		matchPercent = _map.update(_x, _y, _yaw, laser);
//	}
//	catch (...)
//	{
//		matchPercent=0;
//	}

	// ---------------
	// Update Belief
	//cout << (PARTICLE_MAGIC_NUMBER * previewsBelief * matchPercent) << "= "<< PARTICLE_MAGIC_NUMBER << "*" << _belief << "*" << probability << "*" << matchPercent << '\n';
	_belief = PARTICLE_MAGIC_NUMBER * previewsBelief;

	if (_belief > 1) _belief=1;

	return _belief;
}



Particle Particle::create()
{
	Particle newPar;
	//initialize random seed
	srand(time(NULL));

	newPar._x = _x + (rand() % PARTICLE_ERROR_RANGE);
	newPar._y = _y + (rand() % PARTICLE_ERROR_RANGE);
	newPar._yaw = _yaw + (rand() % PARTICLE_ERROR_RANGE);

	newPar._map = _map;

	return newPar;
}
Map& Particle::getMap()
{
	return _map;
}
bool Particle::operator ==(const Particle& ref)
{
	if (_x == ref._x &&
		_y == ref._y &&
		_yaw == ref._yaw &&
		_belief == ref._belief)
	{
		return true;
	}

	return false;
}

double Particle::getBelief() const
{
	return _belief;
}
