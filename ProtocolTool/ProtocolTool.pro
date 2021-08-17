#-------------------------------------------------
#
# Project created by QtCreator 2020-12-24T13:25:50
#
#-------------------------------------------------

QT       += core gui network concurrent serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProtocolTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


include(common/common.pri)
#include(network/network.pri)
include(protocol/protocol.pri)
include(ui/ui.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp \


HEADERS += \
        mainwindow.h \


FORMS += \
        mainwindow.ui


INCLUDEPATH += $$PWD/../spdlog/include
DEPENDPATH += $$PWD/../spdlog/include

INCLUDEPATH += $$PWD/../Communication/
DEPENDPATH += $$PWD/../Communication/
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
    LIBS += -L$$PWD/../bin/debug -lspdlog
    LIBS += -L$$PWD/../bin/debug -lCommunication
}
else {
    DESTDIR = $$PWD/../bin/release
    LIBS += -L$$PWD/../bin/release -lspdlog
    LIBS += -L$$PWD/../bin/release -lCommunication
}

QMAKE_RPATHDIR += ./
QMAKE_RPATHDIR += ./lib
QMAKE_RPATHDIR += $${DESTDIR}
QMAKE_RPATHDIR += ./../lib
QMAKE_RPATHDIR += $${DESTDIR}/../lib

TRANSLATIONS += $$PWD/ProtocolTools_en.ts
TRANSLATIONS += $$PWD/ProtocolTools_zh.ts

RESOURCES += \
    resources.qrc

