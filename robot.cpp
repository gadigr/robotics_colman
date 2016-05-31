/*
 * robot.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "robot.h"
#include "Globals.h"
#include "math.h"

Robot::Robot(char* ip, int port){
	_pc = new PlayerCc::PlayerClient(ip,port);
	_pp = new PlayerCc::Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
//	_pp->SetOdometry(2.2,-2.875,0.34);
	_pp->SetOdometry(2.175,-2.875,0.785);

	int i;
	for(i=0;i<15;i++)
			{
				_pp->SetOdometry(2.175,-2.875,0.785);
			}
	for(i=0;i<15;i++)
			{
	_pc->Read();
			}

		// Init the old position in the middle of the map
		_oldX = startX / RESOLUTION;
		_oldY = startY / RESOLUTION;
		_oldYaw = DTOR(startYaw);

		// the first time is from configuration file
		_x = _oldX;
		_y = _oldY;
		_yaw = _oldYaw;
		_laserCount = _lp->GetCount();

}

void Robot::setFirstpPos(double x, double y, double yaw){
	_pp->SetOdometry(x, y, yaw);
}

// Methods
void Robot::read()
{
	_pc->Read();
	double xx = _pp->GetXPos();
	double yy = _pp->GetYPos();
	_x = (double)((xx * 100)/gridResolution) + (double)gridWidth/2;
	_y = -(-(double)((yy* 100)/gridResolution) + (double)gridHeight/2);
	_yaw = _pp->GetYaw();


}
double Robot::getOldYawPosition()
{
 return _oldYaw;
}
double Robot::getOldYPosition()
{
	return _oldY;
}
double Robot::getOldXPosition()
{
 return _oldX;
}
LaserProxy* Robot::getLaser()
{
	return _lp;
}
double Robot::getYawPosition()
{
	return _yaw;
}
double Robot::getXPosition()
{
	return _x ;
}

double Robot::getYPosition()
{
	return _y ;
}

double Robot::getGoalXPosition()
{
	return goalX / RESOLUTION;
}
double Robot::getGoalYPosition()
{
	return goalY / RESOLUTION;
}
int Robot::getLaserCount()
{
	return _laserCount;
}


void Robot::setSpeed(float speed, float angularSpeed)
{
	_pp->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserDistance(int index)
{
	return (*_lp)[index];
}

void Robot::updatePosition(double x, double y, double yaw)
{
	_oldX = x;
	_oldY = y;
	_oldYaw = yaw;

}

void Robot::updateCurrPosition(double x, double y, double yaw)
{
	_x = x;
	_y = y;
	_yaw = yaw;
}
