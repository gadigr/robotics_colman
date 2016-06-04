/*
 * LocalizationManager.cpp
 */

# include "LocalizationManager.h"
using namespace std;


LocalizationManager*  LocalizationManager::localObject = 0;

LocalizationManager* LocalizationManager::getInstance()
{
	if (!localObject){

		localObject = new LocalizationManager();
	}
	return localObject;
}

void LocalizationManager::SetGrid(int** setGridMap,int setGridWidth,int setGridHight)

{
	GridMap = setGridMap;
	nGridWidth = setGridWidth;
	nGridHight = setGridHight;


}

void LocalizationManager::initParticles()
{
//	for (int i = 0; i < PARTICLE_NUM; i++)
//	{
//		double x = (rand() % nGridWidth);
//		double y = (rand() % nGridHight);
//		double yaw = rand() % (int)(2*M_PI);
//		while (GridMap[(int)y][(int)x] == 1)
//		{
//
//			x = (rand() % nGridWidth);
//			y = (rand() % nGridHight);
//
//		}
//		Particle* p =new Particle(x, y,yaw,1,GridMap,nGridWidth,nGridHight);
//		arr_particles[i] = p;
//	}

	for (int i = 0; i < INIT_PARTICLE_COUNT; i++)
			{
				//initialize random seed
				srand(time(NULL));

				double particleX =  (rand() % PARTICLE_SPREAD_MODULO) / PARTICLE_SPREAD_MODULO;
				double particleY = (rand() % PARTICLE_SPREAD_MODULO) / PARTICLE_SPREAD_MODULO;
				double particleYaw = (rand() % PARTICLE_SPREAD_MODULO) / PARTICLE_SPREAD_MODULO;

				Particle newParticle;
				newParticle.move(particleX,particleY,particleYaw);
				_particles.push_back(newParticle);
			}
}


Point LocalizationManager::update(double deltaX, double deltaY, double deltaYaw, Robot* robot){
	vector<Particle> toRemove;
	Particle bestParticle = _particles[0];

	// Loop the existing particles
	for (int iter = 0; iter != _particles.size(); iter++)
	{
//		Particle& particle = *iter;

		double belief = _particles[iter].update(deltaX, deltaY, deltaYaw, robot);

		// If the particle should be killed
		if (belief <= PARTICLE_KILL_THRESHOLD && _particles.size() != 0 || belief == 0)
		{
			// save the particle for removal
			toRemove.push_back(_particles[iter]);
		}
		// If we can produce more particles
		// If particle should duplicate
		else if (belief >= PARTICLE_BIRTH_THRESHOLD &&
				_particles.size() <= PARTICLE_COUNT)
		{
			Particle newParticle = _particles[iter].create();
			_particles.push_back(particle);
		}

		// get best particle for creation of more
		if (belief > bestParticle->getBelief())
		{
			bestParticle = iter;
		}
	}

	// deleting the particles
	for (list<Particle>::iterator iter = toRemove.begin(); iter != toRemove.end(); iter++)
	{
		_particles.remove(*iter);
	}

	if (_particles.size() == 0)
	{
		int bp=9;
		bp++;
	}

	// Creating from the best part
	for (size_t parCount = _particles.size(); parCount <= PARTICLE_COUNT &&
	bestParticle != _particles.end(); parCount++)
	{
		Particle newParticle = bestParticle->create();
		_particles.push_back(newParticle);
	}

	Point p(bestParticle->getX(),bestParticle->getY());

	return p;
}

Location LocalizationManager::GetHigeBel()
{
//	Location rLocation;
//	double nMax=-999;
//
//	for (int i = 0; i < PARTICLE_NUM; i++)
//		{
//			if(arr_particles[i]->getBelief() > nMax)
//			{
//				nMax = arr_particles[i]->getBelief();
//				rLocation.Xpos = arr_particles[i]->getX();
//				rLocation.Ypos = arr_particles[i]->getY();
//				rLocation.Yaw = arr_particles[i]->getYaw();
//			}
//		}
//
//		return (rLocation);
	}

