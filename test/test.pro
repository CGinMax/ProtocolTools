QT += core testlib gui widgets network concurrent

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app
SOURCES += \
    tst_networktest.cpp \
    ../CdtTools/common/threadpool.cpp \
    ../CdtTools/common/util.cpp \
    ../CdtTools/common/workerthread.cpp \
    ../CdtTools/network/networkbase.cpp \
    ../CdtTools/network/tcpclient.cpp \
    ../CdtTools/network/tcpserver.cpp \
    ../CdtTools/network/udpsocket.cpp \
    ../CdtTools/protocol/cycle/cdtstandard.cpp \
    ../CdtTools/protocol/cycle/standardmintorstrategy.cpp \
    ../CdtTools/protocol/cycle/standardwfstrategy.cpp \
    ../CdtTools/protocol/interacte/cdtinteracte.cpp \
    ../CdtTools/protocol/interacte/intermintorstrategy.cpp \
    ../CdtTools/protocol/interacte/interwfstrategy.cpp \
    ../CdtTools/protocol/nr/cdtexnr.cpp \
    ../CdtTools/protocol/nr/nrmintorstrategy.cpp \
    ../CdtTools/protocol/nr/nrwfstrategy.cpp \
    ../CdtTools/protocol/standard/cdtmintorstrategy.cpp \
    ../CdtTools/protocol/standard/cdtprotocol.cpp \
    ../CdtTools/protocol/standard/cdtwfstrategy.cpp \
    ../CdtTools/protocol/ut/cdtexut.cpp \
    ../CdtTools/protocol/ut/utmintorstrategy.cpp \
    ../CdtTools/protocol/ut/utwfstrategy.cpp \
    ../CdtTools/protocol/cdtframe.cpp \
    ../CdtTools/protocol/checkhelper.cpp \
    ../CdtTools/protocol/protocolbase.cpp \
    ../CdtTools/protocol/strategybase.cpp \
    ../CdtTools/protocol/nrudp/nrudpframe.cpp \
    ../CdtTools/protocol/nrudp/nrudpprotocol.cpp \
    ../CdtTools/protocol/nrudp/nrudpmintorstrategy.cpp \
    ../CdtTools/protocol/nrudp/nrudpwfstrategy.cpp \
    ../CdtTools/ui/dialog/ykdialog.cpp \
    ../CdtTools/ui/tables/delegates/comboboxdelegate.cpp \
    ../CdtTools/ui/tables/delegates/digitlimitedelegate.cpp \
    ../CdtTools/ui/tables/diheaderview.cpp \
    ../CdtTools/ui/tables/aidata.cpp \
    ../CdtTools/ui/tables/aitablemodel.cpp \
    ../CdtTools/ui/tables/didata.cpp \
    ../CdtTools/ui/tables/ditablemodel.cpp \
    ../CdtTools/ui/tabs/fakeclosebutton.cpp \
    ../CdtTools/ui/tabs/maintabbar.cpp \
    ../CdtTools/ui/tabs/maintabwidget.cpp \
    ../CdtTools/ui/tabs/realclosebutton.cpp \
    ../CdtTools/ui/cdtsettingdlg.cpp \
    ../CdtTools/ui/cdtworkwidget.cpp \
    ../CdtTools/ui/clientpage.cpp \
    ../CdtTools/ui/ptcfg.cpp \
    ../CdtTools/ui/serverpage.cpp \
    ../CdtTools/ui/tabpage.cpp\
    ../CdtTools/ui/udppage.cpp


HEADERS += \
    ../CdtTools/common/threadpool.h \
    ../CdtTools/common/util.h \
    ../CdtTools/common/workerthread.h \
    ../CdtTools/network/networkbase.h \
    ../CdtTools/network/tcpclient.h \
    ../CdtTools/network/tcpserver.h \
    ../CdtTools/network/udpsocket.h \
    ../CdtTools/protocol/cycle/cdtstandard.h \
    ../CdtTools/protocol/cycle/standardmintorstrategy.h \
    ../CdtTools/protocol/cycle/standardwfstrategy.h \
    ../CdtTools/protocol/interacte/cdtinteracte.h \
    ../CdtTools/protocol/interacte/intermintorstrategy.h \
    ../CdtTools/protocol/interacte/interwfstrategy.h \
    ../CdtTools/protocol/nr/cdtexnr.h \
    ../CdtTools/protocol/nr/nrmintorstrategy.h \
    ../CdtTools/protocol/nr/nrwfstrategy.h \
    ../CdtTools/protocol/standard/cdtmintorstrategy.h \
    ../CdtTools/protocol/standard/cdtprotocol.h \
    ../CdtTools/protocol/standard/cdtwfstrategy.h \
    ../CdtTools/protocol/ut/cdtexut.h \
    ../CdtTools/protocol/ut/utmintorstrategy.h \
    ../CdtTools/protocol/ut/utwfstrategy.h \
    ../CdtTools/protocol/cdtframe.h \
    ../CdtTools/protocol/checkhelper.h \
    ../CdtTools/protocol/protocolbase.h \
    ../CdtTools/protocol/strategybase.h \
    ../CdtTools/protocol/nrudp/nrudpframe.h \
    ../CdtTools/protocol/nrudp/nrudpprotocol.h \
    ../CdtTools/protocol/nrudp/nrudpmintorstrategy.h \
    ../CdtTools/protocol/nrudp/nrudpwfstrategy.h \
    ../CdtTools/ui/dialog/ykdialog.h \
    ../CdtTools/ui/tables/delegates/comboboxdelegate.h \
    ../CdtTools/ui/tables/delegates/digitlimitedelegate.h \
    ../CdtTools/ui/tables/aidata.h \
    ../CdtTools/ui/tables/aitablemodel.h \
    ../CdtTools/ui/tables/didata.h \
    ../CdtTools/ui/tables/ditablemodel.h \
    ../CdtTools/ui/tables/diheaderview.h \
    ../CdtTools/ui/tabs/fakeclosebutton.h \
    ../CdtTools/ui/tabs/maintabbar.h \
    ../CdtTools/ui/tabs/maintabwidget.h \
    ../CdtTools/ui/tabs/realclosebutton.h \
    ../CdtTools/ui/cdtsettingdlg.h \
    ../CdtTools/ui/cdtworkwidget.h \
    ../CdtTools/ui/clientpage.h \
    ../CdtTools/ui/ptcfg.h \
    ../CdtTools/ui/serverpage.h \
    ../CdtTools/ui/tabpage.h \
    ../CdtTools/ui/udppage.h \
    ../CdtTools/enums.h


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}

RESOURCES += \
    ../CdtTools/resources.qrc

FORMS += \
    ../CdtTools/ui/cdtsettingdlg.ui \
    ../CdtTools/ui/cdtworkwidget.ui \
    ../CdtTools/ui/tabpage.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/release/ -lqt-material-widgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/ -lqt-material-widgets
else:unix: LIBS += -L$$PWD/../bin/debug/ -lqt-material-widgets

INCLUDEPATH += $$PWD/../qt-material-widgets
DEPENDPATH += $$PWD/../qt-material-widgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../bin/release/libqt-material-widgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../bin/debug/libqt-material-widgets.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../bin/release/qt-material-widgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../bin/debug/qt-material-widgets.lib
else:unix: PRE_TARGETDEPS += $$PWD/../bin/debug/libqt-material-widgets.a
