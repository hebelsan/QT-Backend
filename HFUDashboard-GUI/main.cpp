#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QDebug>
#include <QQmlComponent>
#include <QDateTime>
#include <QFont>
#include <QFontDatabase>

#include <unistd.h>

#include "hfuenums.h"
#include "connector/connector.h"
#include "connector/taglibmanager.h"
#include "colorimageprovider.h"
#include "main.h"

QMLSlot::QMLSlot(QObject *parent) : QObject(parent)
{
    counter = 0;
    logFile.setFileName("/home/pi/log/qml_receive.log");
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "could not open log";
}

void QMLSlot::speedSlot(const int speed){
    counter++;
    if (logFile.isOpen()){
        QTextStream out(&logFile);
        out << QDateTime::currentMSecsSinceEpoch() << ";" << counter << ";" << speed << "\n";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("HS Furtwangen");
    QCoreApplication::setOrganizationDomain("hs-furtwangen.de");
    QCoreApplication::setApplicationName("HFU Dashboard");

    //QSettings settings;

    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont("fonts/UbuntuMono-R.ttf");
    QFont newFont("Ubuntu Mono", 11, QFont::Normal, false);
    app.setFont(newFont);

    qmlRegisterUncreatableType<CruseControl>("hfu.enums.CruseControl", 1, 0, "CruseControl", "You cannot create an instance of the Enums.");
    qmlRegisterUncreatableType<Indicators>("hfu.enums.IndicatorLight", 1, 0, "IndicatorLight", "You cannot create an instance of the Enums.");
    qmlRegisterUncreatableType<Gears>("hfu.enums.Gear", 1, 0, "Gear", "You cannot create an instance of the Enums.");

    QQmlApplicationEngine engine;

    Connector *creader = Connector::getInstance();
    engine.rootContext()->setContextProperty("connector", creader);
    engine.addImageProvider(QLatin1String("cover"), ColorImageProvider::getInstance());
    engine.load(QUrl(QLatin1String("qrc:/HFUDashboardBase.qml")));


    /*logging for delay test
    QObject *rootObject = engine.rootObjects().first();
    QObject *item = rootObject->findChild<QObject*>("canEventSink");

    QMLSlot slot;
    QObject::connect(item, SIGNAL(speedSignal(int)),
                     &slot, SLOT(speedSlot(int)));
    */
    return app.exec();
}
