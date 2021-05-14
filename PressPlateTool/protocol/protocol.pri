#protocol.pri

QT += core serialport network

CONFIG += c++11

HEADERS += \
    $$PWD/ybprotocolchannel.h \
    $$PWD/protocolchannelbase.h

SOURCES += \
    $$PWD/ybprotocolchannel.cpp \
    $$PWD/protocolchannelbase.cpp

