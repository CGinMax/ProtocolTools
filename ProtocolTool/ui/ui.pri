#ui pri
QT       += core concurrent

CONFIG += c++11
SOURCES += \
    $$PWD/dialog/ykdialog.cpp \
    $$PWD/tabpage.cpp \
    $$PWD/clientpage.cpp \
    $$PWD/serverpage.cpp \
    $$PWD/cdtsettingdlg.cpp \
    $$PWD/tables/ditablemodel.cpp \
    $$PWD/cdtworkwidget.cpp \
    $$PWD/tables/delegates/comboboxdelegate.cpp \
    $$PWD/tables/aitablemodel.cpp \
    $$PWD/tables/delegates/digitlimitedelegate.cpp \
    $$PWD/tabs/maintabwidget.cpp \
    $$PWD/tabs/fakeclosebutton.cpp \
    $$PWD/tabs/realclosebutton.cpp \
    $$PWD/tabs/maintabbar.cpp \
    $$PWD/trees/channeltreewidget.cpp \
    $$PWD/udppage.cpp \
    $$PWD/tables/diheaderview.cpp \
    $$PWD/dialog/nameddialog.cpp \
    $$PWD/controller/savecontroller.cpp \
    $$PWD/controller/maintabcontroller.cpp \
    $$PWD/serialportpage.cpp \
    $$PWD/tables/aiheaderview.cpp \
    $$PWD/components/switchbutton.cpp \
    $$PWD/components/switchbutton_internal.cpp

HEADERS += \
    $$PWD/dialog/ykdialog.h \
    $$PWD/tabpage.h \
    $$PWD/clientpage.h \
    $$PWD/serverpage.h \
    $$PWD/cdtsettingdlg.h \
    $$PWD/tables/ditablemodel.h \
    $$PWD/cdtworkwidget.h \
    $$PWD/tables/delegates/comboboxdelegate.h \
    $$PWD/tables/aitablemodel.h \
    $$PWD/tables/delegates/digitlimitedelegate.h \
    $$PWD/tabs/maintabwidget.h \
    $$PWD/tabs/fakeclosebutton.h \
    $$PWD/tabs/realclosebutton.h \
    $$PWD/tabs/maintabbar.h \
    $$PWD/trees/channeltreewidget.h \
    $$PWD/udppage.h \
    $$PWD/tables/diheaderview.h \
    $$PWD/dialog/nameddialog.h \
    $$PWD/controller/savecontroller.h \
    $$PWD/controller/maintabcontroller.h \
    $$PWD/serialportpage.h \
    $$PWD/tables/aiheaderview.h \
    $$PWD/components/switchbutton.h \
    $$PWD/components/switchbutton_p.h \
    $$PWD/components/switchbutton_internal.h

FORMS += \
    $$PWD/tabpage.ui \
    $$PWD/cdtsettingdlg.ui \
    $$PWD/cdtworkwidget.ui
