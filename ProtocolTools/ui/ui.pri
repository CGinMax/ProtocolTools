#ui pri
QT       += core concurrent

CONFIG += c++11
SOURCES += \
    ui/dialog/ykdialog.cpp \
    ui/tabpage.cpp \
    ui/clientpage.cpp \
    ui/serverpage.cpp \
    ui/cdtsettingdlg.cpp \
    ui/tables/ditablemodel.cpp \
    ui/cdtworkwidget.cpp \
    ui/tables/delegates/comboboxdelegate.cpp \
    ui/tables/aitablemodel.cpp \
    ui/tables/delegates/digitlimitedelegate.cpp \
    ui/tabs/maintabwidget.cpp \
    ui/tabs/fakeclosebutton.cpp \
    ui/tabs/realclosebutton.cpp \
    ui/tabs/maintabbar.cpp \
    ui/trees/channeltreewidget.cpp \
    ui/udppage.cpp \
    ui/tables/diheaderview.cpp \
    ui/dialog/nameddialog.cpp \
    ui/controller/savecontroller.cpp \
    ui/controller/maintabcontroller.cpp

HEADERS += \
    ui/dialog/ykdialog.h \
    ui/tabpage.h \
    ui/clientpage.h \
    ui/serverpage.h \
    ui/cdtsettingdlg.h \
    ui/tables/ditablemodel.h \
    ui/cdtworkwidget.h \
    ui/tables/delegates/comboboxdelegate.h \
    ui/tables/aitablemodel.h \
    ui/tables/delegates/digitlimitedelegate.h \
    ui/tabs/maintabwidget.h \
    ui/tabs/fakeclosebutton.h \
    ui/tabs/realclosebutton.h \
    ui/tabs/maintabbar.h \
    ui/trees/channeltreewidget.h \
    ui/udppage.h \
    ui/tables/diheaderview.h \
    ui/dialog/nameddialog.h \
    ui/controller/savecontroller.h \
    ui/controller/maintabcontroller.h
