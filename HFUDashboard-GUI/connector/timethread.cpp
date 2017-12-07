#include "timethread.h"
#include "connector.h"
#include <QDateTime>
#include <QString>

TimeThread::TimeThread() {}

void TimeThread::run() {
    Connector *creader = Connector::getInstance();

    while(1){
        QString currentDate = QDateTime::currentDateTime().toString("dd.MM.yyyy");
        QString currentTime = QDateTime::currentDateTime().toString("HH:mm:ss");
        emit creader->dateFrameReceived(currentDate);
        emit creader->timeFrameReceived(currentTime);
        usleep(1000000);
    }
}
