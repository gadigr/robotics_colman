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
bool Localization::CreateParticles(float xDelta, float yDelta, float yawDelta, float belief)
{
	return (CreateParticles(xDelta, yDelta, yawDelta, belief, EXPANSION_RADIUS, YAW_RANGE, HIGH_BREED));
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

// Update the particles' in the vector.
void Localization::Update(float deltaX, float deltaY, float deltaYaw, LaserProxy* laserProxy) {
	vector<Particle*> childsToAdd;
	vector<int> childsToRemove;
	int particlesSize = particles.size();

	// Update all the particles
	for (int i = 0; i < particlesSize; i++)
	{
		Particle* particle = particles[i];
		particle->Update(deltaX, deltaY, deltaYaw, map, laserProxy);

		float belif = particle->belief;

		// If belief is too low - remove the particle
		if (belif <= LOW_BELIEF_MIN)
		{
			childsToRemove.push_back(i);
		}
		// If belief is high - high breed
		else if (belif >= HIGH_BELIEF_MIN &&
				 ((particlesSize + HIGH_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT))
		{
			particle->age++;
			BreedParticle(particle, HIGH_BREED, childsToAdd);
		}
		// If belief is normal - normal breed
		else if ((particlesSize + NORMAL_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT)
		{
			particle->age++;
			BreedParticle(particle, NORMAL_BREED, childsToAdd);
		}
	}

	// Removing the useless particles.
	if (childsToRemove.size() > 0)
	{
		for(int i = childsToRemove.size() - 1; i >=0 ; i--)
		{
			int indexToRemove = childsToRemove[i];
			particles.erase(particles.begin() + indexToRemove);
		}
	}

	// Adding the new particles.
	if (childsToAdd.size() > 0)
	{
		ChildsToParticles(childsToAdd);
	}
}

// Create new children-particles, by using the best particles.
void Localization::BreedParticle(Particle* particle, int childCount, vector<Particle*>& childs) {

	// In case we havn't reached the maximum particles allowed number, create a new particle.
	if (particles.size() + childCount < MAX_PARTICLES_COUNT)
	{
		// Create new child-particles, and push them into the vector.
		for (int i = 0; i < childCount; i++)
		{
			Particle* child = particle->CreateChild();
			childs.push_back(child);
		}
	}
}

// Create new children-particles, by using the best particles.
void Localization::BreedParticle(Particle* particle, int childCount, float expansionRadius, float yawRange, vector<Particle*>& childs)
{
	// In case we havn't reached the maximum particles allowed number, create a new particle.
	if (particles.size() + childCount < MAX_PARTICLES_COUNT)
	{
		// Create new child-particles, and push them into the vector.
		for (int i = 0; i < childCount; i++)
		{
			Particle* child = particle->CreateChild(expansionRadius, yawRange);
				childs.push_back(child);
		}
	}
}

// This method return the particle with highest belief
Particle* Localization::BestParticle()
{
	// If there are no particles - we need to generate new ones
	if (particles.empty())
	{
		CreateParticles(xDelta, yDelta, yawDelta, 1, EMERGENCY_EXPANSION_RADIUS, EMERGENCY_YAW_RANGE,  PARTICLE_EMERGENCY_BREED);

		Particle* randomParticle = particles[rand() % particles.size()];

		xDelta = randomParticle->xDelta;
		yDelta = randomParticle->yDelta;
		yawDelta = randomParticle->yawDelta;

		return randomParticle;
	}

	// Put the first one as the best just for comparison
	Particle* bestParticle = particles[0];

	cout << "*** Choosing best particle ***" << endl;

	// Search for the best particale by it's belief.
	for (int i = 1; i < particles.size(); i++)
	{
		//cout << "[" << particles[i]->xDelta << "," << particles[i]->yDelta << "] Yaw: " << particles[i]->yawDelta << " b: " << particles[i]->belief << endl;

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
	for (int i = 0; i < childs.size(); i++)
	{
		particles.push_back(childs[i]);
	}
}

