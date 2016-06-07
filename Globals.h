/*
 * Globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// calc const
#define PAI 3.1415
#define NORMAL 1.8
#define RESOLUTION 4

// laser
#define LASER_COUNT 666
#define LASER_SCOPE 240
#define OBSTACLE_DISTANCE 4

// Distance consts for missing aim in a bit
#define SAFETY_DIS_FROM_OBSTACLE 0.8
#define DIS_FROM_OBSTACLE 4

// Map
const int BLANK = 255;
const int FULL = 0;
const int NEW_FULL = 1;
const int PARTICLE_UPDATE_RATE = 5;

//particle
#define MAX_PARTICLES_COUNT 300
#define LOW_BELIEF_MIN 0.5
#define HIGH_BELIEF_MIN 0.7
#define BELIEF_MAGIC_NUMBER 0.9

// movment
#define RANGE_TO_CHECK 110
#define FORWARD_SPEED 0.4
#define TURN_SPEED 0.01
#define TURN_ANGLE 0.3
#define TURN_IN_PLACE_ANGLE 0.8

// turn in place
#define TOP_RIGHT 0.7853
#define TOP_LEFT  2.3561
#define DOWN_RIGHT -0.7853
#define DOWN_LEFT -2.617
#define RIGHT_ANGLE 0
#define LEFT_ANGLE 3.1415


struct Location {
		  double Xpos;
		  double Ypos;
		  double Yaw;;
		} ;

struct StartLocationType {
		  double Xpos;
		  double Ypos;
		  double Yaw;;
		} ;

struct GoalLocationType {
		int Xpos;
		int Ypos;
} ;


#endif /* GLOBALS_H_ */
