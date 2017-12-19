#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QFile>

QT_BEGIN_NAMESPACE

class QCanBusFrame;
class QLabel;

QT_END_NAMESPACE

class Connector : public QObject
{
    Q_OBJECT
private:
    static bool instanceflag;
    static Connector *instance;
    static int rpm;
    static int rpm_new;
    static QString currentDate();
    static QString currentTime();
    static void *input(void *id);
    static void *testMount(void *id);
    static void *smooth_rpm(void *);
    static void *turnSignal(void *);
    static void *menu(void *);
    static void *time(void *);
    static void *rpm_test(void *id);
    explicit Connector(QObject *parent = nullptr);
public:
   void setRpm(float rpm);
   float getRpm();
   void setNewRpm(float newRpm);
   float getNewRpm();
   void turnSignalTest(std::string direction);
   void menuTest();
   static Connector* getInstance();

signals:
    void speedFrameReceived(float speed);
    void rpmFrameReceived(float rpm);
    void gearFrameReceived(int gear);
    void fuelFrameReceived(float fuel);
    void temperatureFrameReceived(float temperature);
    void turnSignalRightFrameReceived();
    void turnSignalLeftFrameReceived();
    void menuStateFrameReceived();
    void dateFrameReceived(QString date);
    void timeFrameReceived(QString time);
    void rangeFrameReceived(float range); //not implemented yet
    void warningFrameReceived();
    void dashboardMenuRightFrameReceived();
    void dashboardMenuLeftFrameReceived();
    void dashboardRollerUpFrameReceived();
    void dashboardRollerDownFrameReceived();

    // media
    void volumeUpFrameReceived();
    void volumeDownFrameReceived();
    void musicPlayButtonPressed();
    void audioWheelTurnedLeft();
    void audioWheelTurnedRight();
    void switchUsbMediaMode();
    void musicForwardButtonPressed();
    void musicBackwardButtonPressed();
    void musicWheelDirectionNormal();
    void newMusicTitleList(std::vector <QString> newMusicList);
};

#endif // CONNECTOR_H
