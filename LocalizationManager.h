/*
 * LocalizationManager.h
 */

#include "Particle.h"
#include "Globals.h"

class LocalizationManager{
	static LocalizationManager *localObject;
	int** GridMap;
	int nGridWidth;
	int nGridHight;


public:
	Particle* arr_particles[PARTICLE_NUM];

	void SetGrid(int** setGridMap,int setGridWidth,int setGridHight);
	static LocalizationManager* getInstance();
	void initParticles();
	void resampleParticles();
	Particle *getBestParticle();
	void update(double deltaX, double deltaY, double deltaYaw);
	void UpdateBel(double DeltaX, double DeltaY, double Yaw, Robot* robot);
	Location GetHigeBel();
};
