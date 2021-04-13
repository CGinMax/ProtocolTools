#common pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    common/threadpool.cpp \
    common/workerthread.cpp \
    common/util.cpp \
    common/ptcfg.cpp \
    common/aidata.cpp \
    common/didata.cpp

HEADERS += \
    common/enums.h \
    common/threadpool.h \
    common/workerthread.h \
    common/util.h \
    common/ptcfg.h \
    common/aidata.h \
    common/didata.h
