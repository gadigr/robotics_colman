///*
// * Map.cpp
// *
// *  Created on: Mar 22, 2016
// *      Author: colman
// */
//
//#include "Map.h"
//#include "lodepng.h"
//#include <iostream>
//#include <math.h>
//
//Map::Map(double mapResolution, double robotSize) {
//	this->mapResolution = mapResolution;
//	this->robotSize = robotSize;
//
//}
//
//void Map::loadMap(const char* mapFile) {
//
//	lodepng::decode(pixels, width, height, mapFile);
//	map.resize(height);
//	for (int i = 0; i < height; i++) {
//		map[i].resize(width);
//	}
//
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			map[i][j] = checkIfCellIsOccupied(i, j);
//		}
//	}
//
//	printMap();
//}
//
//void Map::inflateObstacles() {
//	int robotSizeInPixels = robotSize / mapResolution;
//	int inflationRadius = 0.3 * robotSizeInPixels;
//
//	// Init newMap
//	newMap.resize(height + inflationRadius*2);
//		for (int i = 0; i < height + inflationRadius*2; i++) {
//			newMap[i].resize(width + inflationRadius*2);
//		}
//
//	// Inflate every dark pixel
//	for(int i = 0; i < height; i++){
//		for(int j = 0; j< width; j++) {
//			if(map[i][j]) {
//				for(int y=-inflationRadius; y<inflationRadius; y++)
//				{
//				    int half_row_width=sqrt(inflationRadius*inflationRadius-y*y);
//				    for(int x=-half_row_width; x< half_row_width; x++)
//				    	newMap[i+inflationRadius+y][j+inflationRadius+x] = true;
//				}
//			}
//		}
//	}
//
//
//	// Paint inflated pixels in map
//	for (int m = 0; m < height; m++) {
//			for (int n = 0; n < width; n++) {
//				if(newMap[m + inflationRadius][n + inflationRadius])
//					paintPixel(m,n);
//			}
//		}
//}
//
//bool Map::checkIfCellIsOccupied(int i, int j) {
//	int c = (i * width + j) * 4;
//	int r = pixels[c];
//	int g = pixels[c + 1];
//	int b = pixels[c + 2];
//
//	if (r == 0 && g == 0 && b == 0)
//		return true;
//	return false;
//}
//
//void Map::printMap() const {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			cout << (map[i][j] ? "*" : " ");
//		}
//		cout << endl;
//	}
//}
//
//void Map::paintPixel(int i, int j){
//	int c = (i * width + j) * 4;
//	pixels[c] = 0;
//	pixels[c + 1] = 0;
//	pixels[c + 2] = 0;
//}
//
//void Map::saveMap(const char* newMapFile) {
//	//Encode the image
//	  unsigned error = lodepng::encode(newMapFile, pixels, width, height);
//
//	  //if there's an error, display it
//	  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
//}
//
//unsigned int Map::getHeight() {
//	return this->height;
//}
//
//unsigned int Map::getWidth() {
//	return this->width;
//}
//
//Map::~Map() {
//	// TODO Auto-generated destructor stub
//}
//

/*
 * Map.cpp
 */


#include "Map.h"
#include "ConfigurationManager.h"
#include "lodepng.h"
#include <iostream>
#include <fstream>


using namespace std;

std::vector<unsigned char> imageArray; //the raw pixels
unsigned int nWidth, nHeight;


//Decode from disk to raw pixels with a single function call
void Map::lodeImage(const char* filename)
{
	//decode
	unsigned error = lodepng::decode(imageArray, nWidth, nHeight, filename);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

int Map::GetPositionAsMatrix(int nRow, int nCol)
{
	return (imageArray[nRow * nWidth * 4 + nCol * 4]);
}
void Map::SetPositionAsMatrix(int nRow, int nCol, int nValue)
{
	imageArray[nRow * nWidth * 4 + nCol * 4] = nValue;
	imageArray[nRow * nWidth * 4 + nCol * 4 + 1] = nValue;
	imageArray[nRow * nWidth * 4 + nCol * 4 + 2] = nValue;
	imageArray[nRow * nWidth * 4 + nCol * 4 + 3] = 255;
}

void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

bool Map::CheckPlaceIsValid(int nRow,int nCol)
{
	if (nCol * 4 < 0 || nRow < 0 || nCol * 4 > nWidth * 4 - 8 || nRow > nHeight - 2)
		return false;

	return(true);
}


void Map::NewBlow(int yPos, int xPos, int nCount)
{
	int LeftCornerX = xPos - nCount;
	int LeftCornery = yPos - nCount;
	int RightCornerX = xPos + nCount;
	int RightCornery = yPos + nCount;

	for (int nRow = LeftCornery; nRow < RightCornery; nRow++)
	{
		for (int nCol = LeftCornerX; nCol < RightCornerX; nCol++)
		{
			if (CheckPlaceIsValid(nRow, nCol) && GetPositionAsMatrix(nRow, nCol) == BLANK)
			{
				SetPositionAsMatrix(nRow, nCol, NEW_FULL);
			}

		}
	}
}

int Map::CheckCell(int nRow, int nCol, int nCellsToCheck)
{
	int nNumOfBlack = 0;
	int nNumOfNewBlacks = 0;
	nRow *= nCellsToCheck;
	nCol *= nCellsToCheck;
	int Result;

	// Running over the png vector and counts how many black and new black there is for this gridpixel
	for (int nRowOfset = 0; nRowOfset < nCellsToCheck; nRowOfset += 1)
	{
		for (int nColOfset = 0; nColOfset < nCellsToCheck; nColOfset += 1)
		{
			if (CheckPlaceIsValid(nRow + nRowOfset, nCol + nColOfset))
			{
				Result = GetPositionAsMatrix(nRow + nRowOfset, nCol + nColOfset);

				if (Result == FULL)
				{
					nNumOfBlack++;
				}
				else if (Result == NEW_FULL)
				{
					nNumOfNewBlacks++;
				}
			}

		}
	}

	if ((nNumOfBlack > 0) || (nNumOfNewBlacks > 2))
		return 1;
	else
		return 0;

}

void Map::MakeGridFromImage(int **&GridMap, int *nGridWidth, int *nGridHight)
{
	ConfigurationMGR *pntConfiguration;
	int CellsToBlow;

	// Call Configurationmanager to get the parameters values
	pntConfiguration = pntConfiguration->getInstance();

	// Crate the array of pixels from the png file
	lodeImage(pntConfiguration->mapLocation.c_str());

	// Callculate how many pixel needs to be blow depending on the size of the robot
	CellsToBlow = (pntConfiguration->RobotSize / 2) / (pntConfiguration->MapResolutionCM) + 4;

	// Running over all the png map and blow it
	for (unsigned int nRow = 0; nRow < nHeight; nRow += 1)
	{
		for (unsigned int nCol = 0; nCol < nWidth; nCol += 1)
		{
			if (GetPositionAsMatrix(nRow, nCol) == FULL)
			{
				NewBlow(nRow, nCol, CellsToBlow);
			}
		}
	}


	int PixelInGrid;

	// TODO: Remove this. its just for testing
	const char* newfile = "hospital_section2.png";
	saveImage(newfile, imageArray, nWidth, nHeight);
	//

	int nMapHight, nMapWidth;

	// Callculate how many cells in the first array is one cell in the final grid
	PixelInGrid = pntConfiguration->GridResolutionCM / pntConfiguration->MapResolutionCM;

	ofstream myFile;
	myFile.open("map.txt");

	// Finds the size of the grid
	nMapHight = nHeight / PixelInGrid;
	nMapWidth = nWidth / PixelInGrid;

	// Change the value of the start and the goal positions on the grid
	pntConfiguration->StartLocation.Xpos /= PixelInGrid;
	pntConfiguration->StartLocation.Ypos /= PixelInGrid;
	pntConfiguration->Goal.Xpos /= PixelInGrid;
	pntConfiguration->Goal.Ypos /= PixelInGrid;

	// TODO: Remove this. its just for testing
	cout << pntConfiguration->Goal.Xpos << "    " << pntConfiguration->Goal.Ypos << endl;
	cout << pntConfiguration->StartLocation.Xpos << "    " << pntConfiguration->StartLocation.Ypos << endl;
	//

	// creating the matrixGrid
	GridMap = new int*[nMapHight];
	for (int i = 0; i < nMapHight; i++)
		GridMap[i] = new int[nMapWidth];

	// Running over the grid and puts values using the first array
	for (int nRow = 0; nRow < nMapHight; nRow++)
	{
		for (int nCol = 0; nCol < nMapWidth; nCol++)
		{
			GridMap[nRow][nCol] = CheckCell(nRow,nCol,PixelInGrid);

			// TODO: Remove this. its just for testing
			if((nRow == pntConfiguration->StartLocation.Ypos && nCol == pntConfiguration->StartLocation.Xpos) ||
					(nRow == pntConfiguration->Goal.Ypos && nCol == pntConfiguration->Goal.Xpos))
			{
				myFile << '2';
			}
			else
			{
				myFile << GridMap[nRow][nCol];
			}
			//
		}

		myFile << '\n';

		GridOfTheMap = GridMap;
}
myFile.close();

*nGridWidth = nMapWidth;
*nGridHight = nMapHight;

}



