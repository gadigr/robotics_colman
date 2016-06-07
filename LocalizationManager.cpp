/*
 * Localization.cpp
 */

#include "LocalizationManager.h"

#include <ctime>

Localization::Localization(Map* map) {
	this->map = map;

	xDelta = yDelta = yawDelta = 0;
}

// Create a new particle.
bool Localization::CreateParticles(float xDelta, float yDelta, float yawDelta, float belief, float expansionRadius, float yawRange, int childsCount)
{
	// In case we havn't reached the maximum particles allowed number, create a new particle.
	if (particles.size() + childsCount < MAX_PARTICLES_COUNT)
	{
		Particle* particle = new Particle(xDelta, yDelta, yawDelta, belief);
		particles.push_back(particle);
		vector<Particle*> childs;
		BreedParticle(particle, childsCount, expansionRadius, yawRange, childs);
		ChildsToParticles(childs);
		return true;
	}

	return false;
}

void Localization::initParticles(int amount){
	for (int i = 0; i < amount; i++){
		double x = (rand() % map->nMapWidth);
		double y = -(rand() % map->nMapHeight);
		double yaw = rand() % (int)(2*M_PI);

		while (map->GridOfTheMap[(int)-y][(int)x] == 1){
			x = (rand() % map->nMapWidth);
			y = -(rand() % map->nMapHeight);
		}
		Particle* p =new Particle(x, y,yaw,1);
		particles.push_back(p);
	}
}

float Localization::Random(float min, float max)
{
    return (max - min ) * ((float)rand() / (float)RAND_MAX )  + min;
}

double Localization::eval(Robot* r, Map* m)
{
	double sum = 0;
	double dx;
	double dy;
	double err;

	for (int i = 0; i < particles.size();i++){
		dx = particles[i]->xDelta - r->getXPosition() + (m->nMapWidth / 2);
		dy = -particles[i]->yDelta - (-r->getYPosition()) + (m->nMapHeight / 2);
		err = sqrt(dx*dx + dy*dy);
		sum += err;
	}

	return(sum /particles.size());

}

// Update the particles' in the vector.
void Localization::Update(double deltaX, double deltaY, double deltaYaw, LaserProxy* laserProxy, Robot* rob) {

	vector<int> childsToRemove;
	int particlesSize = particles.size();

	Particle* bestP = particles[0];

	for (int i = 0; i < particlesSize; i++)
	{
		Particle* particle = particles[i];
		particle->Update(deltaX, deltaY, deltaYaw, map, laserProxy, rob);
		float belif = particle->belief;

		// If belief is too low - remove the particle
		if ((belif <= LOW_BELIEF_MIN && particles.size() != 0) || belif == 0)
		{
			childsToRemove.push_back(i);
		}
		// If belief is high - high breed
		else if (belif >= HIGH_BELIEF_MIN &&
				 particles.size() - childsToRemove.size() < MAX_PARTICLES_COUNT)
		{


			Particle* newParticle = particle->CreateChild(1, 1, map);
			particles.push_back(newParticle);

			newParticle = particle->CreateChild(1, 1, map);
			particles.push_back(newParticle);
		}
		// If belief is normal - normal breed
		else if (particles.size() - childsToRemove.size() < MAX_PARTICLES_COUNT)
		{
			particle->age++;

			Particle* newParticle = particle->CreateChild(10, 2, map);
			particles.push_back(newParticle);
		}

		if (belif > bestP->belief)
		{
			bestP = particles[i];
		}
	}

//	 Removing the useless particles.
	if (childsToRemove.size() > 0)
	{
		for(int i = childsToRemove.size() - 1; i >=0 ; i--)
		{
			int indexToRemove = childsToRemove[i];
			particles.erase(particles.begin() + indexToRemove);
		}
	}

	// if we removed too many particles add some
	while(particles.size() < MAX_PARTICLES_COUNT) {
		Particle* newParticle = bestP->CreateChild(20, 3, map);
		particles.push_back(newParticle);
	}
}

// Create new children-particles, by using the best particles.
void Localization::BreedParticle(Particle* particle, int childCount, vector<Particle*>& childs) {

	// In case we havn't reached the maximum particles allowed number, create a new particle.
	for (int i = 0; i < childCount && particles.size() + i < MAX_PARTICLES_COUNT; i++)
			{
			Particle* child = particle->CreateChild(5, 1, map);
			childs.push_back(child);
		}

}

// Create new children-particles, by using the best particles.
void Localization::BreedParticle(Particle* particle, int childCount, float expansionRadius, float yawRange, vector<Particle*>& childs)
{
	// In case we havn't reached the maximum particles allowed number, create a new particle.

		// Create new child-particles, and push them into the vector.
		for (int i = 0; i < childCount && particles.size() + i < MAX_PARTICLES_COUNT; i++)
		{
			Particle* child = particle->CreateChild(expansionRadius, yawRange, map);
				childs.push_back(child);
		}

}

// This method return the particle with highest belief
Particle* Localization::BestParticle()
{

	// Put the first one as the best just for comparison
	Particle* bestParticle = particles[0];

	cout << "*** Choosing best particle ***" << endl;

	// Search for the best particale by it's belief.
	for (int i = 1; i < particles.size(); i++)
	{
		// If the belief of the current particle is bigger than the biggest we found
		if ((particles[i]->belief) > (bestParticle->belief))
				//&& particles[i]->age < bestParticle->age)
		{
			bestParticle = particles[i];
		}
	}

	xDelta = bestParticle->xDelta;
	yDelta = bestParticle->yDelta;
	yawDelta = bestParticle->yawDelta;

	return bestParticle;
}

void Localization::ChildsToParticles(vector<Particle*> childs)
{
	for (int i = 0;
		particles.size() < MAX_PARTICLES_COUNT && i<childs.size();
		i++)
	{
		particles.push_back(childs[i]);
	}
}



///*
// * LocalizationManager.cpp
// */
//
//# include "LocalizationManager.h"
//using namespace std;
//
//
//LocalizationManager*  LocalizationManager::localObject = 0;
//
//LocalizationManager* LocalizationManager::getInstance()
//{
//	if (!localObject){
//
//		localObject = new LocalizationManager();
//	}
//	return localObject;
//}
//
//void LocalizationManager::SetGrid(int** setGridMap,int setGridWidth,int setGridHight)
//
//{
//	GridMap = setGridMap;
//	nGridWidth = setGridWidth;
//	nGridHight = setGridHight;
//}
//
//void LocalizationManager::initParticle(double dStartY, double dStartX)
//{
//	for (int i = 0; i < PARTICLE_NUM; i++)
//				{
//					double x = (rand() % 10) - 5 + (dStartY);
//					double y = (rand() % 10) - 5 +(dStartX);
//					double yaw = rand() % (int)(ANGLES_NUM);
//					if(GridMap[(int)x][(int)y]==0)
//					{
//						GridMap[(int)x][(int)y] = 5;
//
//						Particle* p =new Particle(x, y,yaw,1,GridMap,nGridWidth,nGridHight);
//						arr_particles[i] = p;
//					}
//					else
//					{
//						i--;
//					}
//				}
//}
//
//
//void LocalizationManager::UpdateBel(double DeltaX, double DeltaY, double Yaw, Robot* robot)
//{
//	for (int i = 0; i < PARTICLE_NUM; i++)
//	{
//		//cout << arr_particles[i]->getX() << " ---- " << arr_particles[i]->getY() << endl;
//		arr_particles[i]->UpdateParticle(DeltaX,DeltaY,Yaw,robot);
//		//cout << arr_particles[i]->getBelief() << endl;
//	}
//}
//
//Location LocalizationManager::GetHigeBel()
//{
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
//	}
//
