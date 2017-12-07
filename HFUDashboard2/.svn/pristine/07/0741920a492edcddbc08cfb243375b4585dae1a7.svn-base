#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDebug>
#include <QFile>

class QMLSlot : public QObject
{
    Q_OBJECT

public:
    QMLSlot(QObject *parent = nullptr);

private:
    int counter;
    QFile logFile; //("/home/huebners/log/qml_receive.log");
public slots:
    void speedSlot(const int speed);
};

#endif // MAIN_H
