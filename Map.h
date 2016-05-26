///*
// * Map.h
// *
// *  Created on: Mar 22, 2016
// *      Author: colman
// */
//
//#ifndef MAP_H_
//#define MAP_H_
//
//#include <vector>
//using namespace std;
//
//class Map {
//private:
//	unsigned int width;
//	unsigned int height;
//	vector<vector<bool> > map;
//	vector<vector<bool> > newMap;
//	vector<unsigned char> pixels;
//	double mapResolution;
//	double robotSize;
//
//	bool checkIfCellIsOccupied(int i, int j);
//	void printMap() const;
//
//public:
//	Map(double mapResolution, double robotSize);
//	void loadMap(const char* mapFile);
//	void saveMap(const char* newMapFile);
//	void paintPixel(int i, int j);
//	void inflateObstacles();
//	virtual ~Map();
//	unsigned int getHeight();
//	unsigned int getWidth();
//};
//
//#endif /* MAP_H_ */



/*
 * Map.h
 */

#ifndef MAP_H_
#define MAP_H_

class Map {
public:
	void MakeGridFromImage(int **&GridMap, int *nGridWidth, int *nGridHight);

private:
	int CheckCell(int nRow, int nCol, int nCellsToCheck);
	bool CheckPlaceIsValid(int nRow,int nCol);
	void NewBlow(int yPos, int xPos, int nCount);
	void lodeImage(const char* filename);
	int GetPositionAsMatrix(int nRow, int nCol);
	void SetPositionAsMatrix(int nRow, int nCol, int nValue);
};

#endif
