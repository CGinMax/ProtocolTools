#network pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    network/networkbase.cpp \
    network/tcpserver.cpp \
    network/tcpclient.cpp \
    network/udpsocket.cpp

HEADERS += \
    network/networkbase.h \
    network/tcpserver.h \
    network/tcpclient.h \
    network/udpsocket.h
