# ui.pri

QT += gui core widgets

CONFIG += c++11

HEADERS += \
    $$PWD/expandwidgetitem.h \
    $$PWD/expandwidgetitem_p.h \
    $$PWD/expandtile.h \
    $$PWD/expandwidget.h \
    $$PWD/tileicon.h

SOURCES += \
    $$PWD/expandwidgetitem.cpp \
    $$PWD/expandtile.cpp \
    $$PWD/expandwidget.cpp \
    $$PWD/tileicon.cpp

FORMS += \
    $$PWD/expandwidget.ui \
    $$PWD/expandtile.ui
