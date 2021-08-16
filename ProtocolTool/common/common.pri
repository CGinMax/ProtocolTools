#common pri

QT       += core concurrent network serialport

CONFIG += c++11
SOURCES += \
    $$PWD/threadpool.cpp \
    $$PWD/workerthread.cpp \
    $$PWD/util.cpp \
    $$PWD/ptcfg.cpp \
    $$PWD/aidata.cpp \
    $$PWD/didata.cpp

HEADERS += \
    $$PWD/enums.h \
    $$PWD/threadpool.h \
    $$PWD/workerthread.h \
    $$PWD/util.h \
    $$PWD/ptcfg.h \
    $$PWD/aidata.h \
    $$PWD/didata.h

INCLUDEPATH += $$PWD/../../Communication/
DEPENDPATH += $$PWD/../../Communication/
CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../../bin/debug -lCommunication
}
else {
    LIBS += -L$$PWD/../../bin/release -lCommunication
}
