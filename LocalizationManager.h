/*
 * Localization.h
 */

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include <vector>
using namespace std;

#include "Particle.h"
#include "Map.h"

class Localization {
private:
	Map* map;
	vector<Particle*> particles;

	float xDelta;
	float yDelta;
	float yawDelta;

	void ChildsToParticles(vector<Particle*> childs);
	void BreedParticle(Particle* particle, int dwChildCount, vector<Particle*>& childs);
	void BreedParticle(Particle* particle, int ChildCount, float dExpansionRadius, float dYawRange, vector<Particle*>& childs);

public:
	bool CreateParticles(float xDelta, float yDelta, float yawDelta, float belief);
	bool CreateParticles(float xDelta, float yDelta, float yawDelta, float belief, float expansionRadius, float yawRange, int childsCount);

	Localization(Map* map);
	void Update(float xDelta, float yDelta, float yawDelta, LaserProxy* laserProxy);
	Particle* BestParticle();

};

#endif /* LOCALIZATION_H_ */

