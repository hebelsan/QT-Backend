#include "smooththread.h"
#include "connector.h"
#include "timethread.h"

SmoothThread::SmoothThread() {}


void SmoothThread::run() {
    Connector *creader = Connector::getInstance();

    TimeThread t;
    t.start();

    while(1){
        usleep(50000);
        float rpm = creader->getRpm();
        float newRpm = creader->getNewRpm();
        rpm = (rpm*7+newRpm*1)/8;
        emit creader->rpmFrameReceived(rpm);
    }
}
