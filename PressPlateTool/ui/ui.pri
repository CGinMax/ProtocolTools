# ui.pri

QT += gui core widgets

CONFIG += c++11

HEADERS += \
    $$PWD/expand/expandwidgetitem.h \
    $$PWD/expand/expandwidgetitem_p.h \
    $$PWD/expand/expandtile.h \
    $$PWD/expand/expandwidget.h \
    $$PWD/expand/tileicon.h \
    $$PWD/expand/gatheroperwidget.h \
    $$PWD/tables/ybtablemodel.h \
    $$PWD/tables/listdelegate.h \
    $$PWD/tables/listviewitem.h \
    $$PWD/gatherdetailpage.h \
    $$PWD/tables/ybtableview.h \
    $$PWD/tables/listheader.h \
    $$PWD/buttons/fabcircularmenu.h \
    $$PWD/editableeventfilter.h \
    $$PWD/expand/gathercontroller.h \
    $$PWD/dialogs/serialportdialog.h \
    $$PWD/buttons/rippleoverlay.h \
    $$PWD/buttons/rippleanimation.h \
    $$PWD/page/tablepage.h \
    $$PWD/buttons/circlebutton.h \
    $$PWD/buttons/fabbutton.h

SOURCES += \
    $$PWD/expand/expandwidgetitem.cpp \
    $$PWD/expand/expandtile.cpp \
    $$PWD/expand/expandwidget.cpp \
    $$PWD/expand/tileicon.cpp \
    $$PWD/expand/gatheroperwidget.cpp \
    $$PWD/tables/ybtablemodel.cpp \
    $$PWD/tables/listdelegate.cpp \
    $$PWD/tables/listviewitem.cpp \
    $$PWD/gatherdetailpage.cpp \
    $$PWD/tables/ybtableview.cpp \
    $$PWD/tables/listheader.cpp \
    $$PWD/buttons/fabcircularmenu.cpp \
    $$PWD/editableeventfilter.cpp \
    $$PWD/expand/gathercontroller.cpp \
    $$PWD/dialogs/serialportdialog.cpp \
    $$PWD/buttons/rippleoverlay.cpp \
    $$PWD/buttons/rippleanimation.cpp \
    $$PWD/page/tablepage.cpp \
    $$PWD/buttons/circlebutton.cpp \
    $$PWD/buttons/fabbutton.cpp

FORMS += \
    $$PWD/expand/expandwidget.ui \
    $$PWD/expand/expandtile.ui \
    $$PWD/expand/gatheroperwidget.ui \
    $$PWD/tables/listviewitem.ui \
    $$PWD/gatherdetailpage.ui \
    $$PWD/tables/listheader.ui \
    $$PWD/dialogs/serialportdialog.ui \
    $$PWD/page/tablepage.ui
