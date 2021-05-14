#protocol.pri

QT += core serialport network

CONFIG += c++11

HEADERS += \
    $$PWD/iprotocol.h \
    $$PWD/ybprotocolchannel.h \
    $$PWD/protocolchannelbase.h

SOURCES += \
    $$PWD/iprotocol.cpp \
    $$PWD/ybprotocolchannel.cpp \
    $$PWD/protocolchannelbase.cpp

