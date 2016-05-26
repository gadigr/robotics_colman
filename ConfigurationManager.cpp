/*
 * ConfigurationManager.cpp
 *
 *  Created on: May 26, 2016
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

ConfigurationMGR*  ConfigurationMGR::configMgr = 0;
ConfigurationMGR* ConfigurationMGR::getInstance()
{
	if (!configMgr){

		configMgr = new ConfigurationMGR();
	}
	return configMgr;
}

ConfigurationMGR::ConfigurationMGR()
{
	ReadParametersFile();
}

void ConfigurationMGR::ReadParametersFile()
{
	string FileContent, FileVariable;
	ifstream infile;
	size_t Pos;


	infile.open("parameters.txt");
	if (infile.is_open()) {
		while (!infile.eof())
		{
			getline(infile, FileContent);
			Pos = FileContent.find(": ");
			FileVariable = FileContent.substr(0, Pos);

			if (!FileVariable.compare("map"))
			{
				mapLocation = FileContent.substr(Pos + 2, FileContent.length() - 6);
				cout << mapLocation << endl;
			}
			else if (!FileVariable.compare("startLocation"))
			{
				FileContent = FileContent.substr(Pos + 2, FileContent.length());

				Pos = FileContent.find(" ");
				StartLocation.Xpos = atoi(FileContent.substr(0, Pos).c_str());
				FileContent = FileContent.substr(Pos + 1, FileContent.length());

				Pos = FileContent.find(" ");
				StartLocation.Ypos = atoi(FileContent.substr(0, Pos).c_str());
				FileContent = FileContent.substr(Pos + 1, FileContent.length());

				StartLocation.Yaw = atoi(FileContent.substr(0, Pos - 1).c_str());
			}
			else if (!FileVariable.compare("goal"))
			{
				FileContent = FileContent.substr(Pos + 2, FileContent.length());

				Pos = FileContent.find(" ");
				Goal.Xpos = atoi(FileContent.substr(0, Pos).c_str());
				FileContent = FileContent.substr(Pos + 1, FileContent.length());

				Goal.Ypos = atoi(FileContent.substr(0, Pos).c_str());
			}
			else if (!FileVariable.compare("robotSize"))
			{
				FileContent = FileContent.substr(Pos + 2, FileContent.length());
				Pos = FileContent.find(" ");

				RobotSize = atof(FileContent.substr(0, Pos).c_str());
			}
			else if (!FileVariable.compare("MapResolutionCM"))
			{
				MapResolutionCM = atof(FileContent.substr(Pos + 2, FileContent.length() - 1).c_str());
			}
			else if (!FileVariable.compare("GridResolutionCM"))
			{
				GridResolutionCM = atof(FileContent.substr(Pos + 2, FileContent.length() - 1).c_str());
			}
		}
		infile.close();
	}
	else
	{
		MapResolutionCM = 2.5;
		GridResolutionCM = 10;
		RobotSize = 30;
		StartLocation.Xpos = 362;
		StartLocation.Ypos = 305;
		StartLocation.Yaw = 20;
		Goal.Xpos = 169;
		Goal.Ypos = 138;
		mapLocation = "~/Desktop/roboticLabMap.png";
	}


}
