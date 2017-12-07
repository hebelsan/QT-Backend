#include "mediathread.h"
#include "Mount.h"
#include "../connector/connector.h"
#include <QDebug>


MediaThread::MediaThread() {}

void MediaThread::run() {
    qInfo() << "check usb...";
    Connector *creader = Connector::getInstance();

    while(true)
        {
            bool attached = false;
            std::string mountpoint = "";
            std::string device_id = "";
            std::string device_node = "";
            Mount m;
            m.startScan(mountpoint,device_id,device_node,attached);
            if(attached)
            {
                qInfo() << "attached " << QString::fromStdString(mountpoint);
                emit creader->usbPluggedInSignalReceived();
                // SongDatabase db("/home/paul/track.db");
                // db.synchDatabase(mountpoint,device_id);
            }
            else
            {
                qInfo() << "detached";
                emit creader->usbPluggedOutSignalReceived();
            }
            usleep(100);
        }
}
