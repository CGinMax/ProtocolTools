#communication lib
QT -= gui
QT += core network serialport

TARGET = Communication
TEMPLATE = lib

CONFIG += c++11
SOURCES += \
    $$PWD/communicationbase.cpp \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpclient.cpp \
    $$PWD/udpsocket.cpp \
    $$PWD/serialport.cpp \
    $$PWD/portparam.cpp

HEADERS += \
    $$PWD/communicationbase.h \
    $$PWD/tcpserver.h \
    $$PWD/tcpclient.h \
    $$PWD/udpsocket.h \
    $$PWD/serialport.h \
    $$PWD/portparam.h

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug/lib
}
else {
    DESTDIR = $$PWD/../bin/release/lib
}
