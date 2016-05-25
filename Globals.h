/*
 * Globals.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// waypoints
typedef enum
{
	none,
	Up,
	Down,
	Left,
	Right,
	DownRight,
	DownLeft,
	UpRight,
	UpLeft
} PositionState;

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

//particle
#define DELTA_FROM_SON 1
#define DELTA_YAW 0.1
#define DIRECTIONS_YAW 3
#define DIRECTION 5
#define MAX_PARTICLES 100
#define NORMAL_NUM 2


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



#endif /* GLOBALS_H_ */
