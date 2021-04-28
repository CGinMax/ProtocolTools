# ui.pri

QT += gui core widgets

CONFIG += c++11

HEADERS += \
    $$PWD/expandwidgetitem.h \
    $$PWD/expandwidgetitem_p.h \
    $$PWD/expandtile.h

SOURCES += \
    $$PWD/expandwidgetitem.cpp \
    $$PWD/expandtile.cpp
