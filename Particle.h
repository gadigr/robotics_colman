/*
 * Particle.h
*/

#ifndef PARTICLE_H_
#define PARTICLE_H_


#include "Map.h"
#include "robot.h"

class Particle{

	#define MAX_PROB_DISTANCE  (2)
	#define MAX_PROB_YAW (150)
	#define MAX_OBS_DISTANCE (5)
	#define COEFFICIENT (1.5)

	protected:
		int** _particleMap;
		double _locationX;
		double _locationY;
		double _yaw;
		double _belief;
		int _GridWidth;
		int _GridHight;

	public:
		Particle(double x, double y, double pYaw, double bel, int** map,int nGridWidth, int nGridHight);
		virtual ~Particle();
		void UpdateParticle(double deltaX, double deltaY, double deltaYaw, Robot* robot);
		double getBelief();
		double calcProgressProb(double deltaX, double deltaY, double deltaYaw);
		double calcObsProb(Robot* robot);
		double getX() { return _locationX; }
		double getY() { return _locationY; }
		double getYaw() { return _yaw; }
		int GetValFromRealLocation(double x, double y);
		void SetValFromRealLocation(double x, double y, int value);

};

#endif
