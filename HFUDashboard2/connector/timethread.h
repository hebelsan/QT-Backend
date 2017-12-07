#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QtCore>

class TimeThread : public QThread {
     Q_OBJECT
public:
    TimeThread();
    void run();
};

#endif // TIMETHREAD_H
