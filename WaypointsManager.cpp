/*
 * WayPointManager.cpp
 */

#include "WaypointsManager.h"
#include "ConfigurationManager.h"


#include <iostream>

using namespace std;

void WayPointsManager::createWaypoints(string route, Location* &arr)
{

	const int dirNum=8;
	static int dirX[dirNum]={-1, -1, 0, 1, 1, 1, 0, -1};
	static int dirY[dirNum]={0, 1, 1, 1, 0, -1, -1, -1};

	ConfigurationMGR *pntConfiguration;
	pntConfiguration = pntConfiguration->getInstance();

	// in case the route is not empty
	if (route.length() > 0)
			{
				int counter = 0;
				int lastDirection = (int)(route.at(0)-'0');
				int direction;
				int nNumOfWayPoints = 0;
				arr = new Location[50];
				Location* tempArr;
				char c;
				int x = 0;
				int y = 0;

				// running over all the route and create waypoints
				for (unsigned int i = 0; i < route.length(); i++)
				{
					c = route.at(i);
					direction = c-'0';

					// if the pint is the continue of the way, don't create a waypoint
					if(counter == 0 || (lastDirection == direction && counter < 5))
					{
						counter ++;
					}
					else
					{
						// create a new waypoint
						arr[nNumOfWayPoints].Xpos = x;
						arr[nNumOfWayPoints].Ypos = y;
						lastDirection = direction;
						counter = 0;
						nNumOfWayPoints++;

					}

					x += dirY[direction];
					y += dirX[direction];
				}
			}
			else
			{
				cout << "No route found";
				cout << endl;
			}


}
