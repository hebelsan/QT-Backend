#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H
#include <QtCore>

class InputThread : public QThread {
    Q_OBJECT
public:
    InputThread();
    void run();
};

#endif // INPUTTHREAD_H
