#-------------------------------------------------
#
# Project created by QtCreator 2021-04-28T09:04:46
#
#-------------------------------------------------

QT       += core gui serialport widgets

TARGET = PressPlateTool
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

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

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
else{
    DESTDIR = $$PWD/../bin/release
    LIBS += -L$$PWD/../bin/release -lspdlog
    LIBS += -L$$PWD/../bin/release -lCommunication
}

QMAKE_RPATHDIR += ./
QMAKE_RPATHDIR += ./lib
QMAKE_RPATHDIR += $${DESTDIR}
QMAKE_RPATHDIR += ./../lib
QMAKE_RPATHDIR += $${DESTDIR}/../lib

TRANSLATIONS += $$PWD/PressPlateTool_en.ts
TRANSLATIONS += $$PWD/PressPlateTool_zh.ts

include(ui/ui.pri)
include(protocol/protocol.pri)
include(common/common.pri)

RESOURCES += \
    resources/resources.qrc
