/*
 * LocalizationManager.cpp
 */

# include "LocalizationManager.h"
using namespace std;


LocalizationManager*  LocalizationManager::localObject = 0;

LocalizationManager* LocalizationManager::getInstance()
{
	if (!localObject){

		localObject = new LocalizationManager();
	}
	return localObject;
}

void LocalizationManager::SetGrid(int** setGridMap,int setGridWidth,int setGridHight)

{
	GridMap = setGridMap;
	nGridWidth = setGridWidth;
	nGridHight = setGridHight;
}

void LocalizationManager::initParticles()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		double x = (rand() % nGridWidth);
		double y = (rand() % nGridHight);
		double yaw = rand() % (int)(2*M_PI);
		while (GridMap[(int)y][(int)x] == 1)
		{

			x = (rand() % nGridWidth);
			y = (rand() % nGridHight);

		}
		Particle* p =new Particle(x, y,yaw,1,GridMap,nGridWidth,nGridHight);
		arr_particles[i] = p;
	}
}


void LocalizationManager::UpdateBel(double DeltaX, double DeltaY, double Yaw, Robot* robot)
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		//cout << arr_particles[i]->getX() << " ---- " << arr_particles[i]->getY() << endl;
		arr_particles[i]->UpdateParticle(DeltaX,DeltaY,Yaw,robot);
		//cout << arr_particles[i]->getBelief() << endl;
	}
}

Location LocalizationManager::GetHigeBel()
{
	Location rLocation;
	double nMax=-999;

	for (int i = 0; i < PARTICLE_NUM; i++)
		{
			if(arr_particles[i]->getBelief() > nMax)
			{
				nMax = arr_particles[i]->getBelief();
				rLocation.Xpos = arr_particles[i]->getX();
				rLocation.Ypos = arr_particles[i]->getY();
				rLocation.Yaw = arr_particles[i]->getYaw();
			}
		}

		return (rLocation);
	}

