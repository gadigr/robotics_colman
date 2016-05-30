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

int main() {
	Robot* robot = new Robot("localhost", 6665);


//	ReadConfigurationFile(robot);

//	Map map(robot->mapResolution, robot->robotWidth);
//	map.loadMap("roboticLabMap.png");
//
//	map.inflateObstacles();
//
//	map.saveMap("inflatedMap.png");

	// A* algorithm - to find the path

	int** GridMap;
	int nGridWidth, nGridHeight;
	Location* locations;
	Map map;

	// Reads the parameters file + make the grid
	map.MakeGridFromImage(GridMap,&nGridWidth, &nGridHeight);

	cout << "Grid Width: " << nGridWidth << endl;
	cout << "Grid Height: " << nGridHeight << endl;
	cout << "place [5][6] is " << GridMap[5][6] << endl;

//	Particle* arr_particles[PARTICLE_NUM];

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		int x = rand() % (int)(nGridHeight);
		int y = rand() % (int)(nGridHeight);
		int yaw = rand() % (int)(ANGLES_NUM);
		if(GridMap[x][y]==0)
		{
			GridMap[x][y] = 5;

//				arr_particles[i] = new Particle(x, y, yaw, 1);
		}
		else
		{
			i--;
		}
	}

	ConfigurationMGR *pntConfiguration;
	pntConfiguration = pntConfiguration->getInstance();

	PathPlanner path;
	string route = path.AStarPathFind(pntConfiguration->StartLocation.Ypos,pntConfiguration->StartLocation.Xpos,
			pntConfiguration->Goal.Ypos,pntConfiguration->Goal.Xpos,GridMap, nGridHeight, nGridWidth);

	path.PrintPath(GridMap,pntConfiguration->StartLocation.Ypos,pntConfiguration->StartLocation.Xpos, nGridHeight, nGridWidth,route);

	// Creates the way points along the way
	WayPointsManager waypoint;
	int nNumofWayPoints = waypoint.createWaypoints(route, locations);

	// Creates the driver to move the robot
	cout << endl << "***Start moving***" << endl;
	Driver* driver = new Driver(robot);

	// Move to all points
	for (int i = 0; i < nNumofWayPoints; i++) {
//		driver->moveToNextWaypoint(1, -1);
		driver->moveToNextWaypoint((locations + i)->Xpos,
								   (locations + i)->Ypos);
	}

	return 0;
}


