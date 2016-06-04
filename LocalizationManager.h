/*
 * LocalizationManager.h
 */
#ifndef LOCAL_H_
#define LOCAL_H_
#include "Particle.h"
#include "Globals.h"
#include <vector>

class LocalizationManager{
	static LocalizationManager *localObject;
	int** GridMap;
	int nGridWidth;
	int nGridHight;


public:
	Particle* arr_particles[PARTICLE_NUM];
	vector<Particle> _particles;
	void SetGrid(int** setGridMap,int setGridWidth,int setGridHight);
	static LocalizationManager* getInstance();
	void initParticles();
	void resampleParticles();
	Particle *getBestParticle();
	Point update(double deltaX, double deltaY, double deltaYaw,  Robot* robot);
	void UpdateBel(double DeltaX, double DeltaY, double Yaw, Robot* robot);
	Location GetHigeBel();
};

#endif
