QT += core testlib gui widgets network concurrent

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app
SOURCES += \
    tst_networktest.cpp \
    ../CdtTools/network/networkbase.cpp \
    ../CdtTools/network/tcpserver.cpp\
    ../CdtTools/common/threadpool.cpp \
    ../CdtTools/common/workerthread.cpp


HEADERS += \
    ../CdtTools/network/networkbase.h \
    ../CdtTools/network/tcpserver.h\
    ../CdtTools/common/threadpool.h \
    ../CdtTools/common/workerthread.h


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}
