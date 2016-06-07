/*
 * Particle.h
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "robot.h"
#include <math.h>

#include "Map.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
using namespace std;


class Map;

class Particle {
public:
	float xDelta;
	float yDelta;
	float yawDelta;
	float belief;
	int age;


	float Random(float min, float max);
	float ProbabilityByMovement(float xDelta, float yDelta, float yawDelta);
	float ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy, Robot* rob);

	void Respawn(Map * map);
	Particle(float xDelta, float yDelta, float yawDelta, float belief);
	Particle* CreateChild();
	Particle* CreateChild(float expansionRadius, float yawRange,  Map* map);
	void Update(float X_delta, float Y_delta, float Yaw_delta, Map* map, LaserProxy* lp, Robot* rob);

	float GetX();
	float GetY();
	float GetYaw();
};

#endif /* PARTICLE_H_ */
