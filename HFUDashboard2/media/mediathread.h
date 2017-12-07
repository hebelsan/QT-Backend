#ifndef MEDIATHREAD_H
#define MEDIATHREAD_H

#include <QtCore>

class MediaThread : public QThread {
    Q_OBJECT
public:
    MediaThread();
    void run();
signals:
    void usbPluggedInSignalReceived();
    void usbPluggedOutSignalReceived();
};

#endif // MEDIATHREAD_H
