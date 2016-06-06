


/*
 * Map.h
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
//#include "Particle.h"


using namespace std;
class Map {


public:
//	void saveMapWithParticles(vector<Particle>& array);
	void MakeGridFromImage(int **&GridMap, int *nGridWidth, int *nGridHight);
	void saveWithRobot(double x, double y, const char* filename);


private:
	int CheckCell(int nRow, int nCol, int nCellsToCheck);
	bool CheckPlaceIsValid(int nRow,int nCol);
	void NewBlow(int yPos, int xPos, int nCount);
	void lodeImage(const char* filename);
	void paintPixel(int i, int j);

	int GetPositionAsMatrix(int nRow, int nCol);
	void SetPositionAsMatrix(int nRow, int nCol, int nValue);

public :
	int nMapWidth;
	int nMapHeight;
	int **GridOfTheMap;
};

#endif
