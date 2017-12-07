/*
 * Mount.h
 *
 *  Created on: 02.04.2015
 *      Author: paul
 */

#ifndef MOUNT_H_
#define MOUNT_H_
#include <string>
class Mount
{
public:
	Mount();
	void startScan(std::string &mountpoint, std::string &deviceID, std::string &deviceNode, bool &attached);
	std::string convertToString(const char *str);
	void getMountpoint(const std::string deviceNode, std::string &mountpoint);
	virtual ~Mount();
};

#endif /* MOUNT_H_ */
