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

//particle
#define DELTA_FROM_SON 1
#define DELTA_YAW 0.1
#define DIRECTIONS_YAW 3
#define DIRECTION 5
#define MAX_PARTICLES 1000
#define NORMAL_NUM 2
#define PARTICLE_NUM 500
#define ANGLES_NUM 666
#define PARTICLE_ERROR_RANGE 5
#define PARTICLE_MAGIC_NUMBER 2

#define INIT_PARTICLE_COUNT 10
#define PARTICLE_KILL_THRESHOLD 0.2
#define PARTICLE_BIRTH_THRESHOLD 0.6

#define PARTICLE_COUNT 50

#define PARTICLE_PROB_MOV_YAW 120
#define PARTICLE_PROB_MOV_DISTANCE 1

#define PARTICLE_SPREAD_MODULO 10

// movment
#define RANGE_TO_CHECK 110
#define FORWARD_SPEED 0.4
#define TURN_SPEED 0.01
#define TURN_ANGLE 0.3
#define TURN_IN_PLACE_ANGLE 0.8


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
