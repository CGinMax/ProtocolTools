#network pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    $$PWD/networkbase.cpp \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpclient.cpp \
    $$PWD/udpsocket.cpp

HEADERS += \
    $$PWD/networkbase.h \
    $$PWD/tcpserver.h \
    $$PWD/tcpclient.h \
    $$PWD/udpsocket.h
