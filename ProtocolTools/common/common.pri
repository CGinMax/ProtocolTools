#common pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    $$PWD/threadpool.cpp \
    $$PWD/workerthread.cpp \
    $$PWD/util.cpp \
    $$PWD/ptcfg.cpp \
    $$PWD/aidata.cpp \
    $$PWD/didata.cpp \
    $$PWD/portparam.cpp

HEADERS += \
    $$PWD/enums.h \
    $$PWD/threadpool.h \
    $$PWD/workerthread.h \
    $$PWD/util.h \
    $$PWD/ptcfg.h \
    $$PWD/aidata.h \
    $$PWD/didata.h \
    $$PWD/portparam.h
