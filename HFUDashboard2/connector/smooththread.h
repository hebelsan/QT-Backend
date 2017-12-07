#ifndef SMOOTHTHREAD_H
#define SMOOTHTHREAD_H
#include <QtCore>

class SmoothThread : public QThread {
    Q_OBJECT
public:
    SmoothThread();
    void run();
};

#endif // SMOOTHTHREAD_H
