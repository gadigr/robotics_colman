/*
 * Map.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>
#include <math.h>

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

	// Init newMap
	newMap.resize(height + inflationRadius*2);
		for (int i = 0; i < height + inflationRadius*2; i++) {
			newMap[i].resize(width + inflationRadius*2);
		}

	// Inflate every dark pixel
	for(int i = 0; i < height; i++){
		for(int j = 0; j< width; j++) {
			if(map[i][j]) {
				for(int y=-inflationRadius; y<inflationRadius; y++)
				{
				    int half_row_width=sqrt(inflationRadius*inflationRadius-y*y);
				    for(int x=-half_row_width; x< half_row_width; x++)
				    	newMap[i+inflationRadius+y][j+inflationRadius+x] = true;
				}
			}
		}
	}


	// Paint inflated pixels in map
	for (int m = 0; m < height; m++) {
			for (int n = 0; n < width; n++) {
				if(newMap[m + inflationRadius][n + inflationRadius])
					paintPixel(m,n);
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

void Map::paintPixel(int i, int j){
	int c = (i * width + j) * 4;
	pixels[c] = 0;
	pixels[c + 1] = 0;
	pixels[c + 2] = 0;
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

