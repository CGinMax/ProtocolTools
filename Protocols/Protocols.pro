#-------------------------------------------------
#
# Project created by QtCreator 2021-05-14T10:50:37
#
#-------------------------------------------------

QT -= gui
QT += core
TARGET = Protocols
TEMPLATE = lib

CONFIG += c++11
CONFIG += staticlib

DEFINES += PROTOCOLS_STATIC
#DEFINES += PROTOCOLS_LIBRARY

SOURCES += \
        iprotocols.cpp \
    convert.cpp

HEADERS += \
        iprotocols.h \
        protocols_global.h \ 
    convert.h

include(YBProtocol/YBProtocol.pri)
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
