#-------------------------------------------------
#
# Project created by QtCreator 2020-12-24T13:25:50
#
#-------------------------------------------------

QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CdtTools
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
    ui/dialog/ykdialog.cpp \
    ui/tabpage.cpp \
    network/tcpclient.cpp \
    common/threadpool.cpp \
    common/workerthread.cpp \
    protocol/cdtinteracte.cpp \
    protocol/cdtframe.cpp \
    protocol/checkhelper.cpp \
    protocol/cdtprotocol.cpp \
    protocol/protocolbase.cpp \
    protocol/cdtcycle.cpp \
    ui/clientpage.cpp \
    ui/serverpage.cpp \
    ui/cdtsettingdlg.cpp \
    common/util.cpp \
    ui/tables/ditablemodel.cpp \
    ui/tables/didata.cpp \
    ui/cdtworkwidget.cpp \
    ui/tables/delegates/comboboxdelegate.cpp \
    ui/tables/aitablemodel.cpp \
    ui/tables/aidata.cpp \
    ui/tables/delegates/digitlimitedelegate.cpp \
    ui/ptcfg.cpp \
    protocol/frame.cpp \
    ui/floatbuttongroup.cpp \
    protocol/cdtexut.cpp \
    protocol/cdtexnr.cpp

HEADERS += \
        mainwindow.h \
    network/networkbase.h \
    enums.h \
    network/tcpserver.h \
    ui/dialog/ykdialog.h \
    ui/tabpage.h \
    network/tcpclient.h \
    common/threadpool.h \
    common/workerthread.h \
    protocol/cdtinteracte.h \
    protocol/cdtframe.h \
    protocol/checkhelper.h \
    protocol/cdtprotocol.h \
    protocol/protocolbase.h \
    protocol/cdtcycle.h \
    ui/clientpage.h \
    ui/serverpage.h \
    ui/cdtsettingdlg.h \
    common/util.h \
    ui/tables/ditablemodel.h \
    ui/tables/didata.h \
    ui/cdtworkwidget.h \
    ui/tables/delegates/comboboxdelegate.h \
    ui/tables/aitablemodel.h \
    ui/tables/aidata.h \
    ui/tables/delegates/digitlimitedelegate.h \
    ui/ptcfg.h \
    protocol/frame.h \
    ui/floatbuttongroup.h \
    protocol/cdtexut.h \
    protocol/cdtexnr.h

FORMS += \
        mainwindow.ui \
    ui/tabpage.ui \
    ui/cdtwidget.ui \
    ui/cdtsettingdlg.ui \
    ui/cdtworkwidget.ui

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}
