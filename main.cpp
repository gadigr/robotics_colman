/*
 * Main.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <algorithm>    // std::min
#include <math.h>

using namespace PlayerCc;
using namespace std;

bool myfn(int i, int j) { return i<j; }

const int SENSORS_ANGLES[] = {90, 25, 0, -25, -90};
#define PI 3.14159265

int main() {
	PlayerClient pc("localhost", 6665);

	Position2dProxy pp(&pc);
	SonarProxy sp(&pc);

	//pp.SetSpeed(0.5, 0);
	pp.SetOdometry(-6.009, 2.481, dtor(-194.220));

	while (true) {
		pc.Read();
		cout << "X: " << pp.GetXPos() << ", Y: " << pp.GetYPos()
				<< ", Yaw: " << pp.GetYaw() << endl;

//		cout << sp << endl;

		for (int i=0; i<=4 ;i++) {
			if(sp[i] < 0.8)
			{
				cout << "Distance from obstacle: " << sp[i] << endl;
				double yPos = cos(SENSORS_ANGLES[i]*PI/180) * sp[i] + pp.GetYPos();

				double xPos = sin(SENSORS_ANGLES[i]*PI/180) * sp[i] + pp.GetXPos();
				cout << "Obstacle Y: " << yPos << endl;
				cout << "Obstacle X: " << xPos << endl;

				break;
			}
		}

		if (sp[2] < 0.5 || sp[1] < 0.5 || sp[3] < 0.5){
//			cout << "object found in: " << std::min_element(arr, arr+2, myfn) - arr << endl;
			double right = sp[0] + sp[5] + sp[1];
			double left = sp[3] + sp[7] + sp[4];
			if(right > left) {
				cout << "turn right" << endl;
//				pp.SetSpeed(0, -0.5);
			}
			else {
				cout << "turn left" << endl;
//				pp.SetSpeed(0, 0.5);
			}
		}

//		else
//			pp.SetSpeed(0.5, 0);

	}

}

/*int main() {
	PlayerClient pc("localhost", 6665);
	Position2dProxy pp(&pc);

	pc.Read();
	double startX = pp.GetXPos();
	double targetX = startX + 1;
	double currX = startX;

	pp.SetSpeed(0.5, 0);
	while (currX < targetX) {
		pc.Read();
		currX = pp.GetXPos();
		cout << "X: " << pp.GetXPos() << ", Y: " << pp.GetYPos() << ", Yaw: " << pp.GetYaw() << endl;
	}

	return 0;
}*/

