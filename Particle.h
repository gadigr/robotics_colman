/*
 * Particle.h
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#include "Map.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

#define NORMAL_BREED 5
#define HIGH_BREED 20
#define MAX_PARTICLES_COUNT 250
#define EXPANSION_RADIUS 1
#define YAW_RANGE 6
#define LOW_BELIEF_MIN 0.5
#define HIGH_BELIEF_MIN 0.85
#define BELIEF_MAGIC_NUMBER 2
#define PARTICLE_LIFES_NUM 5
#define EMERGENCY_EXPANSION_RADIUS EXPANSION_RADIUS * 2
#define EMERGENCY_YAW_RANGE YAW_RANGE * 2
#define PARTICLE_EMERGENCY_BREED MAX_PARTICLES_COUNT - 2
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.1F)
#define WAYPOINT_RADIUS 4
#define DETECT_EVASION_RADIUS 0.6

class Particle {
public:
	float xDelta;
	float yDelta;
	float yawDelta;
	float belief;
	int age;

	float Random(float min, float max);
	float ProbabilityByMovement(float xDelta, float yDelta, float yawDelta);
	float ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy);

	Particle(float xDelta, float yDelta, float yawDelta, float belief);
	Particle* CreateChild();
	Particle* CreateChild(float expansionRadius, float yawRange);
	void Update(float X_delta, float Y_delta, float Yaw_delta, Map* map, LaserProxy* lp);

	float GetX();
	float GetY();
	float GetYaw();
};

#endif /* PARTICLE_H_ */


///*
// * Particle.h
//*/
//
//#ifndef PARTICLE_H_
//#define PARTICLE_H_
//
//
//#include "Map.h"
//#include "robot.h"
//
//class Particle{
//
//	#define MAX_PROB_DISTANCE  (2)
//	#define MAX_PROB_YAW (150)
//	#define MAX_OBS_DISTANCE (5)
//	#define COEFFICIENT (1.5)
//
//	protected:
//		int** _particleMap;
//		double _locationX;
//		double _locationY;
//		double _yaw;
//		double _belief;
//		int _GridWidth;
//		int _GridHight;
//
//	public:
//		Particle(double x, double y, double pYaw, double bel, int** map,int nGridWidth, int nGridHight);
//		virtual ~Particle();
//		void UpdateParticle(double deltaX, double deltaY, double deltaYaw, Robot* robot);
//		double getBelief();
//		double calcProgressProb(double deltaX, double deltaY, double deltaYaw);
//		double calcObsProb(Robot* robot);
//		double getX() { return _locationX; }
//		double getY() { return _locationY; }
//		double getYaw() { return _yaw; }
//		int GetValFromRealLocation(double x, double y);
//		void SetValFromRealLocation(double x, double y, int value);
//
//};
//
//#endif
