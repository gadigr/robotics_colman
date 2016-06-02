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

///*
// * LocalizationManager.h
// */
//
//#include "Particle.h"
//#include "Globals.h"
//
//class LocalizationManager{
//	static LocalizationManager *localObject;
//	int** GridMap;
//	int nGridWidth;
//	int nGridHight;
//
//
//public:
//	Particle* arr_particles[PARTICLE_NUM];
//	void SetGrid(int** setGridMap,int setGridWidth,int setGridHight);
//	static LocalizationManager* getInstance();
//	void initParticle(double dStartY, double dStartX);
//	void UpdateBel(double DeltaX, double DeltaY, double Yaw, Robot* robot);
//	Location GetHigeBel();
//};
