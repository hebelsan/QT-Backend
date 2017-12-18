#include "Mount.hpp"
#include "Controller.hpp"
#include "libudev.h"
#include <unistd.h>
#include <mntent.h>
#include <iostream>
using namespace std;

Mount::Mount() {}

Mount::~Mount()	{}

void Mount::getMountpoint(const string deviceNode, string &mountpoint) {
	struct mntent *ent;
	FILE *aFile;

	aFile = setmntent("/proc/mounts", "r");
	if (aFile == NULL) {
		perror("setmntent");
		exit(1);
	}
	while (NULL != (ent = getmntent(aFile))) {
		if (ent->mnt_fsname == deviceNode) {
			mountpoint = ent->mnt_dir;
		}
	}
	endmntent(aFile);
}

string Mount::convertToString(const char *str) {
	if (str) {
		return str;
	}
	return "";
}

void Mount::setCntrlConnector(std::string* connector)
{
	mnt_pnt = connector;
}

void Mount::setMountPoint(std::string point)
{
	mnt_pnt = new string(point);
}

void Mount::startScan(std::string &mountpoint, std::string &deviceID, std::string &deviceNode, bool &attached)
{
	struct udev *udev;
	struct udev_device *dev;

	struct udev_monitor *mon;
	int fd;

	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		return;
	}
	/* Set up a monitor to monitor hidraw devices */
	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "block", "partition");
	udev_monitor_enable_receiving(mon);
	/* Get the file descriptor (fd) for the monitor.
	 This fd will get passed to select() */
	fd = udev_monitor_get_fd(mon);
	while (1) {
		/* Set up the call to select(). In this case, select() will
		 only operate on a single file descriptor, the one
		 associated with our udev_monitor. Note that the timeval
		 object is set to 0, which will cause select() to not
		 block. */
		fd_set fds;
		struct timeval tv;
		int ret;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(fd + 1, &fds, NULL, NULL, &tv);

		/* Check if our file descriptor has received data. */
		if (ret > 0 && FD_ISSET(fd, &fds)) {

			/* Make the call to receive the device.
			 select() ensured that this will not block. */
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				string action = convertToString(udev_device_get_action(dev));
				deviceNode = convertToString(
						udev_device_get_devnode(dev));
				string id = convertToString(
						udev_device_get_property_value(dev, "ID_INPUT"));
				dev = udev_device_get_parent_with_subsystem_devtype(dev, "usb",
						"usb_device");
				if (!dev) {
					printf("Unable to find parent usb device.");
					exit(1);
				}
				//string serial = udev_device_get_sysattr_value(dev, "serial");
				string manufacturer = convertToString(
						udev_device_get_sysattr_value(dev, "manufacturer"));
				string idVendor = convertToString(
						udev_device_get_sysattr_value(dev, "idVendor"));
				string idProduct = convertToString(
						udev_device_get_sysattr_value(dev, "idProduct"));
				string serial = convertToString(
						udev_device_get_sysattr_value(dev, "serial"));
				if (action == "add") {
					deviceID = idProduct + " " + idVendor;
					attached = true;
					while(mountpoint == "")
					{
						getMountpoint(deviceNode, mountpoint);
						usleep(250 * 1000);
					}
					return;
				} else if (action == "remove") {
					attached = false;
					deviceID= idProduct + " " + idVendor;
					return;
				}

				udev_device_unref(dev);

			} else {
				printf("No Device from receive_device(). An error occured.\n");
			}
		}
		usleep(250 * 1000);
	}

	udev_unref(udev);
}

void* Mount::checkMount(void* mObject){
	while(true)
	{
		bool attached = false;
		string mountpoint = "";
		string device_id = "";
		string device_node = "";
		((Mount *)mObject)->startScan(mountpoint,device_id,device_node,attached);
		if(attached)
		{
			cout << "attached mountpoint:" << mountpoint << " device id:" << device_id << endl;
			// Set Value to notify Controller
			((Mount *)mObject)->setMountPoint(mountpoint);
		}
		else
		{
			((Mount *)mObject)->setMountPoint("");
			cout << "detached" << endl;
		}
	}
}
