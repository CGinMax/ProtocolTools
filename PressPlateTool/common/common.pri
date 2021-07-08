#common pri

QT += gui core widgets network serialport concurrent

CONFIG += c++11

HEADERS += \
    $$PWD/threadpool.h \
    $$PWD/workerthread.h

SOURCES += \
    $$PWD/threadpool.cpp \
    $$PWD/workerthread.cpp
