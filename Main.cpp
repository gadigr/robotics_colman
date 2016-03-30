/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"

int main() {
	double mapResolution = 0.025;
	double robotSize = 0.3;

	Map map(mapResolution, robotSize);
	map.loadMap("roboticLabMap.png");

	map.inflateObstacles();

	map.saveMap("test.png");

	return 0;
}


