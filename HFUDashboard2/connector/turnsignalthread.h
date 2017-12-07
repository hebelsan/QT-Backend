#ifndef TURNSIGNALTHREAD_H
#define TURNSIGNALTHREAD_H

#include <QtCore>

class TurnSignalThread : public QThread{
     Q_OBJECT
public:
    TurnSignalThread();
    void run();
};

#endif // TURNSIGNALTHREAD_H
