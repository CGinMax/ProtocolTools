# ui.pri

QT += gui core widgets

CONFIG += c++11

HEADERS += \
    $$PWD/expand/expandwidgetitem.h \
    $$PWD/expand/expandwidgetitem_p.h \
    $$PWD/expand/expandtile.h \
    $$PWD/expand/expandwidget.h \
    $$PWD/expand/tileicon.h \
    $$PWD/expand/gatheroperwidget.h

SOURCES += \
    $$PWD/expand/expandwidgetitem.cpp \
    $$PWD/expand/expandtile.cpp \
    $$PWD/expand/expandwidget.cpp \
    $$PWD/expand/tileicon.cpp \
    $$PWD/expand/gatheroperwidget.cpp

FORMS += \
    $$PWD/expand/expandwidget.ui \
    $$PWD/expand/expandtile.ui \
    $$PWD/expand/gatheroperwidget.ui
