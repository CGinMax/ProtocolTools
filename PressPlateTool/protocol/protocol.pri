#protocol.pri

QT += core serialport network

CONFIG += c++11

HEADERS += \
    $$PWD/content/contentfactory.h \
    $$PWD/content/contentqueryaddr.h \
    $$PWD/content/contentquerystatus.h \
    $$PWD/content/contentqueryversion.h \
    $$PWD/content/contentreportstatus.h \
    $$PWD/content/contentsettingaddr.h \
    $$PWD/content/contentsettingstatus.h \
    $$PWD/content/icontent.h \
    $$PWD/ybframe.h

SOURCES += \
    $$PWD/content/contentfactory.cpp \
    $$PWD/content/contentqueryaddr.cpp \
    $$PWD/content/contentquerystatus.cpp \
    $$PWD/content/contentqueryversion.cpp \
    $$PWD/content/contentreportstatus.cpp \
    $$PWD/content/contentsettingaddr.cpp \
    $$PWD/content/contentsettingstatus.cpp \
    $$PWD/content/icontent.cpp \
    $$PWD/ybframe.cpp
