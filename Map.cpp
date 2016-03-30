/*
 * Map.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

Map::Map(double mapResolution, double robotSize) {
	this->mapResolution = mapResolution;
	this->robotSize = robotSize;

}

void Map::loadMap(const char* mapFile) {

	lodepng::decode(pixels, width, height, mapFile);
	map.resize(height);
	for (int i = 0; i < height; i++) {
		map[i].resize(width);
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	printMap();
}

void Map::inflateObstacles() {
	int robotSizeInPixels = robotSize / mapResolution;
	int inflationRadius = 0.3 * robotSizeInPixels;

	// TODO: inflate obstacles
	cout<< inflationRadius << " " << robotSizeInPixels << endl;

	for(int i = 0; i < height; i++){
			for(int j = 0; j< width; j++) {
				newMap[i][j] = map[i][j];
			}
		}
bool isGood = false;
	for(int i = inflationRadius; i < height + inflationRadius*2; i++){
		for(int j = inflationRadius; j< width + inflationRadius*2; j++) {

		}
	}
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * width + j) * 4;
	int r = pixels[c];
	int g = pixels[c + 1];
	int b = pixels[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printMap() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << (map[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::saveMap(const char* newMapFile) {
	//Encode the image
	  unsigned error = lodepng::encode(newMapFile, pixels, width, height);

	  //if there's an error, display it
	  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


Map::~Map() {
	// TODO Auto-generated destructor stub
}

