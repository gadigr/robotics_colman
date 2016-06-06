
/*
 * Map.cpp
 */


#include "Map.h"
#include "ConfigurationManager.h"
#include "lodepng.h"
#include <math.h>
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


void Map::saveWithRobot(double x, double y, const char* filename){

	int xInMap = x*4;
	int yInMap = -y*4;


	std::vector<unsigned char> newImg;
	unsigned error = lodepng::decode(newImg, nWidth, nHeight, "roboticLabMap.png");

		//if there's an error, display it
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;


	double inflationRadius = 5;
	int position;
	for(int m=-inflationRadius; m<inflationRadius; m++) {
		 int half_row_width=sqrt(inflationRadius*inflationRadius-m*m);
		 for(int n=-half_row_width; n< half_row_width; n++){
			 position = ((yInMap+inflationRadius+m) * (nWidth) + (xInMap+inflationRadius+n)) * 4;
			 newImg[position] = 	255;
			 newImg[position + 1] = 0;
			 newImg[position + 2] = 0;
		 }
//			 imageArray[yInMap+inflationRadius+m][xInMap+inflationRadius+n] = true;
	 }
//	position = (yInMap * nWidth + xInMap) * 4;

	 error = lodepng::encode(filename, newImg, nWidth, nHeight);

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
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



