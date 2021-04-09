#-------------------------------------------------
#
# Project created by QtCreator 2020-12-24T13:25:50
#
#-------------------------------------------------

QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProtocolTools
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
        mainwindow.cpp \
    network/networkbase.cpp \
    network/tcpserver.cpp \
    network/tcpclient.cpp \
    common/threadpool.cpp \
    common/workerthread.cpp \
    common/util.cpp \
    common/ptcfg.cpp \
    protocol/checkhelper.cpp \
    protocol/cdtframe.cpp \
    protocol/protocolbase.cpp \
    protocol/standard/cdtprotocol.cpp \
    protocol/interacte/cdtinteracte.cpp \
    protocol/ut/cdtexut.cpp \
    protocol/nr/cdtexnr.cpp \
    ui/dialog/ykdialog.cpp \
    ui/tabpage.cpp \
    ui/clientpage.cpp \
    ui/serverpage.cpp \
    ui/cdtsettingdlg.cpp \
    ui/tables/ditablemodel.cpp \
    ui/tables/didata.cpp \
    ui/cdtworkwidget.cpp \
    ui/tables/delegates/comboboxdelegate.cpp \
    ui/tables/aitablemodel.cpp \
    ui/tables/aidata.cpp \
    ui/tables/delegates/digitlimitedelegate.cpp \
    protocol/strategybase.cpp \
    protocol/standard/cdtwfstrategy.cpp \
    protocol/standard/cdtmintorstrategy.cpp \
    protocol/interacte/interwfstrategy.cpp \
    protocol/interacte/intermintorstrategy.cpp \
    protocol/ut/utwfstrategy.cpp \
    protocol/ut/utmintorstrategy.cpp \
    protocol/nr/nrwfstrategy.cpp \
    protocol/nr/nrmintorstrategy.cpp \
    protocol/cycle/cdtstandard.cpp \
    protocol/cycle/standardmintorstrategy.cpp \
    protocol/cycle/standardwfstrategy.cpp \
    ui/tabs/maintabwidget.cpp \
    ui/tabs/fakeclosebutton.cpp \
    ui/tabs/realclosebutton.cpp \
    protocol/nrudp/nrudpframe.cpp \
    protocol/nrudp/nrudpprotocol.cpp \
    protocol/nrudp/nrudpmintorstrategy.cpp \
    protocol/nrudp/nrudpwfstrategy.cpp \
    ui/tabs/maintabbar.cpp \
    network/udpsocket.cpp \
    ui/udppage.cpp \
    ui/tables/diheaderview.cpp \
    ui/dialog/nameddialog.cpp \
    common/savecontroller.cpp

HEADERS += \
        mainwindow.h \
    enums.h \
    network/networkbase.h \
    network/tcpserver.h \
    network/tcpclient.h \
    common/threadpool.h \
    common/workerthread.h \
    common/util.h \
    common/ptcfg.h \
    protocol/checkhelper.h \
    protocol/cdtframe.h \
    protocol/standard/cdtprotocol.h \
    protocol/protocolbase.h \
    protocol/interacte/cdtinteracte.h \
    protocol/ut/cdtexut.h \
    protocol/nr/cdtexnr.h \
    ui/dialog/ykdialog.h \
    ui/tabpage.h \
    ui/clientpage.h \
    ui/serverpage.h \
    ui/cdtsettingdlg.h \
    ui/tables/ditablemodel.h \
    ui/tables/didata.h \
    ui/cdtworkwidget.h \
    ui/tables/delegates/comboboxdelegate.h \
    ui/tables/aitablemodel.h \
    ui/tables/aidata.h \
    ui/tables/delegates/digitlimitedelegate.h \
    protocol/strategybase.h \
    protocol/standard/cdtwfstrategy.h \
    protocol/standard/cdtmintorstrategy.h \
    protocol/interacte/interwfstrategy.h \
    protocol/interacte/intermintorstrategy.h \
    protocol/ut/utwfstrategy.h \
    protocol/ut/utmintorstrategy.h \
    protocol/nr/nrwfstrategy.h \
    protocol/nr/nrmintorstrategy.h \
    protocol/cycle/cdtstandard.h \
    protocol/cycle/standardmintorstrategy.h \
    protocol/cycle/standardwfstrategy.h \
    ui/tabs/maintabwidget.h \
    ui/tabs/fakeclosebutton.h \
    ui/tabs/realclosebutton.h \
    protocol/nrudp/nrudpframe.h \
    protocol/nrudp/nrudpprotocol.h \
    protocol/nrudp/nrudpmintorstrategy.h \
    protocol/nrudp/nrudpwfstrategy.h \
    ui/tabs/maintabbar.h \
    network/udpsocket.h \
    ui/udppage.h \
    ui/tables/diheaderview.h \
    ui/dialog/nameddialog.h \
    common/savecontroller.h

FORMS += \
        mainwindow.ui \
    ui/tabpage.ui \
    ui/cdtsettingdlg.ui \
    ui/cdtworkwidget.ui

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}


QMAKE_RPATHDIR += ./
QMAKE_RPATHDIR += $${DESTDIR}
QMAKE_RPATHDIR += ./../lib
QMAKE_RPATHDIR += $${DESTDIR}/../lib

TRANSLATIONS += $$PWD/ProtocolTools_en.ts
TRANSLATIONS += $$PWD/ProtocolTools_zh.ts

RESOURCES += \
    resources.qrc

