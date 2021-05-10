#common pri

QT += gui core widgets concurrent

CONFIG += c++11

HEADERS += \
    $$PWD/threadpool.h \
    $$PWD/workerthread.h \
    $$PWD/ybsensordata.h \
    $$PWD/gatherdata.h

SOURCES += \
    $$PWD/threadpool.cpp \
    $$PWD/workerthread.cpp \
    $$PWD/ybsensordata.cpp \
    $$PWD/gatherdata.cpp
