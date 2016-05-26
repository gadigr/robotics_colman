/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "ConfigurationManager.h"
#include "robot.h"


int main() {
	Robot* robot = new Robot("localhost", 6665);

	ReadConfigurationFile(robot);

	Map map(robot->mapResolution, robot->robotWidth);
	map.loadMap("roboticLabMap.png");

	map.inflateObstacles();

	map.saveMap("inflatedMap.png");

	// A* algorithm - to find the path

	return 0;
}


