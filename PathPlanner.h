/*
 * PathPlanner.h
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

using namespace std;
#include<string>

// map of directions
const int dirNum=8; // number of possible directions to go at any position
static int dirX[dirNum]={1, 1, 0, -1, -1, -1, 0, 1};
static int dirY[dirNum]={0, 1, 1, 1, 0, -1, -1, -1};

class PathPlanner {
public:
	string AStarPathFind( const int nRowStart, const int nColStart, const int nRowFinish, const int nColFinish, int** GridMap, const int Hight, const int Width );
	void PrintPath(int** GridMap,const int nRowStart, const int nColStart, const int Hight, const int Width, string route);
};

#endif
