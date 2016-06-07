/*
 * robot.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
// mai is
#ifndef ROBOT_H_
#define ROBOT_H_
#include<string.h>
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <vector>
using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient* _pc;
	Position2dProxy* _pp;

	double _x;
	double _y;
	double _yaw;
	double _oldYaw;
	double _oldX;
	double _oldY;
	int _laserCount;

public:
	Robot(char* ip, int port);
	std::vector<vector<int> >  resolutionMapAfterBlow;
	std::vector<vector<int> >  resolutionMapBeforeBlow;
	LaserProxy* _lp;
	int** _mapMatrixBeforeBlow;
	const char* mapName;
	double startX;
	double startY;
	double startYaw;
	double goalX;
	double goalY;
	double robotWidth;
	double robotLengt;
	double mapResolution;
	double gridResolution;
	double currentYaw;
	int gridHeight;
	int gridWidth;
	int totalResolution;
	void read();
	void setFirstpPos(double x, double y, double yaw);
	void setSpeed(float speed, float angularSpeed);
	float getLaserDistance(int index);
	double getXPosition();
	double getYPosition();
	double getGoalXPosition();
	double getGoalYPosition();
	double getOldYawPosition();
	double getOldYPosition();
	double getOldXPosition();
	double getYawPosition();
	int getLaserCount();
	LaserProxy* getLaser();
	void updatePosition(double x, double y, double yaw);
	void updateCurrPosition(double x, double y);
	void updateCurrPosition(double x, double y, double yaw);
	void setOdometryInProxyPosition(double x, double y, double yaw);
};

#endif /* ROBOT_H_ */
