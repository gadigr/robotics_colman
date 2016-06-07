/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "ConfigurationManager.h"
#include "robot.h"
#include "Globals.h"
#include "Particle.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "Driver.h"
#include "LocalizationManager.h"
#include <sstream>

int main() {
//	Robot* robot = new Robot("10.10.245.63", 6665);
	Robot* robot = new Robot("localhost", 6665);

	// init variables
	int** GridMap;
	int nGridWidth, nGridHeight;
	Location* locations;
	Map map;
	ConfigurationMGR *pntConfiguration;
	pntConfiguration = pntConfiguration->getInstance();
	PathPlanner path;
	WayPointsManager waypoint;
	Localization* localization;
	string fin;
	stringstream strs;
	string temp_str;
	char const* pchar;

	// Reads the parameters file + make the grid
	map.MakeGridFromImage(GridMap,&nGridWidth, &nGridHeight);

	// Run A* algo
	string route = path.AStarPathFind(pntConfiguration->StartLocation.Ypos,pntConfiguration->StartLocation.Xpos,
			pntConfiguration->Goal.Ypos,pntConfiguration->Goal.Xpos,GridMap, nGridHeight, nGridWidth);

	// Print the path
	path.PrintPath(GridMap,pntConfiguration->StartLocation.Ypos,pntConfiguration->StartLocation.Xpos, nGridHeight, nGridWidth,route);

	// Creates the way points along the way
	int nNumofWayPoints = waypoint.createWaypoints(route, locations);

	// Creates the driver to move the robot
	cout << endl << "***Start moving***" << endl;

	robot->gridResolution = pntConfiguration->GridResolutionCM;
	robot->gridHeight = nGridHeight;
	robot->gridWidth = nGridWidth;
	robot->read();
	Driver* driver = new Driver(robot);

    // Create the first particles
    localization = new Localization(&map);
//    localization->initParticles(MAX_PARTICLES_COUNT);

    Particle* p = new Particle(robot->getXPosition(), robot->getYPosition(), robot->getYawPosition(), 0.51);

    for (int i = 0; i<MAX_PARTICLES_COUNT; i++) {
    	localization->particles.push_back(p->CreateChild(5, 1, &map));
    }

//    map.saveMapWithParticles(localization);

	// Move to all points
	for (int i = 0; i < nNumofWayPoints; i++) {

		fin = ".png";
		strs.str(std::string());
		strs << i;
		temp_str = strs.str();
		pchar = temp_str.c_str();
		fin = pchar + fin;

		// save map with robot position
		map.saveWithRobot(robot->getXPosition(), robot->getYPosition(),
				fin.c_str());

		driver->moveToNextWaypoint((locations + i)->Xpos,
								   (locations + i)->Ypos,
								   localization);

		Particle* best = localization->BestParticle();
		cout << "Best particle: x - " << best->GetX() << "  y - " << best->GetY() << endl
			 << "Curr position: x - " << robot->getXPosition() << " y - " << robot->getYPosition() << endl << endl;
	}


	map.saveWithRobot(robot->getXPosition(), robot->getYPosition(),
			"fin.png");

	return 0;
}


