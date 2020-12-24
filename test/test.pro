QT += core testlib gui widgets network

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app
SOURCES += \
    tst_networktest.cpp \
    ../CdtTools/network/networkbase.cpp \
    ../CdtTools/network/tcpserver.cpp


HEADERS += \
    ../CdtTools/network/networkbase.h \
    ../CdtTools/network/tcpserver.h
