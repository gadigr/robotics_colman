/*
 * ConfigurationManager.h
 *
 *  Created on: May 26, 2016
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

using namespace std;

#include<string>
#include "Globals.h"

class ConfigurationMGR{

	static ConfigurationMGR *configMgr;
	ConfigurationMGR();

public:
	static ConfigurationMGR* getInstance();
	StartLocationType StartLocation;
	GoalLocationType Goal;
	double MapResolutionCM, GridResolutionCM, RobotSize;
	size_t Pos;
	string  mapLocation;

private:
	void ReadParametersFile();

};

#endif
