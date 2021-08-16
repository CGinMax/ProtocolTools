#communication lib

QT += core network serialport

TARGET = Communication
TEMPLATE = lib

CONFIG += c++11

DEFINES += COMMUNICATION_LIBRARY

SOURCES += \
    $$PWD/communicationbase.cpp \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpclient.cpp \
    $$PWD/udpsocket.cpp \
    $$PWD/serialport.cpp \
    $$PWD/portparam.cpp \
    qmlserialporthelper.cpp

HEADERS += \
    $$PWD/communicationbase.h \
    $$PWD/tcpserver.h \
    $$PWD/tcpclient.h \
    $$PWD/udpsocket.h \
    $$PWD/serialport.h \
    $$PWD/portparam.h \
    $$PWD/communication_global.h \
    qmlserialporthelper.h

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}

QMAKE_RPATHDIR += ./
QMAKE_RPATHDIR += ./lib
QMAKE_RPATHDIR += $${DESTDIR}
QMAKE_RPATHDIR += ./../lib
QMAKE_RPATHDIR += $${DESTDIR}/../lib
