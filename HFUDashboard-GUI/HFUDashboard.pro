QT += qml quick

#QT += network positioning location # maps

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
# libtag
LIBS +=  `pkg-config --cflags --libs taglib` -lz
INCLUDEPATH  += /usr/include/taglib

CONFIG += c++11

unix{ LIBS += -ludev}

SOURCES += main.cpp \
    connector/connector.cpp \
    connector/inputthread.cpp \
    connector/smooththread.cpp \
    connector/timethread.cpp \
    connector/taglibmanager.cpp

RESOURCES += qml.qrc \
    dev.qrc

QT_DEBUG_PLUGINS=1

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    hfuenums.h \
    main.h \
    connector/connector.h \
    connector/inputthread.h \
    connector/smooththread.h \
    connector/timethread.h \
    connector/taglibmanager.h

#test pi
target.path = /home/pi/
INSTALLS += target
