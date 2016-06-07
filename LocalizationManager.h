/*
 * Localization.h
 */

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include <vector>
#include <libplayerc++/playerc++.h>
using namespace std;
using namespace PlayerCc;
#include "Particle.h"
#include "Map.h"
#include "robot.h"

class Map;
class Particle;

class Localization {
private:
	Map* map;


	float xDelta;
	float yDelta;
	float yawDelta;

	float Random(float min, float max);
	void ChildsToParticles(vector<Particle*> childs);
	void BreedParticle(Particle* particle, int dwChildCount, vector<Particle*>& childs);
	void BreedParticle(Particle* particle, int ChildCount, float dExpansionRadius, float dYawRange, vector<Particle*>& childs);

public:
	void initParticles(int amount);
	vector<Particle*> particles;
	bool CreateParticles(float xDelta, float yDelta, float yawDelta, float belief, float expansionRadius, float yawRange, int childsCount);
	double eval(Robot* r, Map* m);
	Localization(Map* map);
	void Update(double xDelta, double yDelta, double yawDelta, LaserProxy* laserProxy, Robot* rob);
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
