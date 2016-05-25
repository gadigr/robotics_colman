/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_
#include "robot.h"
class ConfigurationManager {
public:
	ConfigurationManager();
	virtual ~ConfigurationManager();

};

void ReadConfigurationFile(Robot* rob);
#endif /* CONFIGURATIONMANAGER_H_ */
