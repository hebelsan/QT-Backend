#ifndef MOUNT_H_
#define MOUNT_H_
#include <string>
class Mount
{
private:
	std::string* mnt_pnt;
	
	public:
	Mount();
	void startScan(std::string &mountpoint, std::string &deviceID, std::string &deviceNode, bool &attached);
	std::string convertToString(const char *str);
	void getMountpoint(const std::string deviceNode, std::string &mountpoint);
	virtual ~Mount();
	static void *checkMount(void*);
	void setCntrlConnector(std::string*);
	void setMountPoint(std::string);
};

#endif /* MOUNT_H_ */
