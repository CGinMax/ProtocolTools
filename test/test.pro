QT += core testlib gui widgets network concurrent

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app
SOURCES += \
    tst_networktest.cpp \
    ../CdtTools/network/networkbase.cpp \
    ../CdtTools/network/tcpserver.cpp\
    ../CdtTools/common/threadpool.cpp \
    ../CdtTools/common/workerthread.cpp \
    ../CdtTools/protocol/cdtframe.cpp \
    ../CdtTools/protocol/cdtinteracte.cpp \
    ../CdtTools/protocol/cdtprotocol.cpp \
    ../CdtTools/protocol/checkhelper.cpp \
    ../CdtTools/protocol/protocolbase.cpp \
    ../CdtTools/common/util.cpp \
    ../CdtTools/ui/tables/delegates/comboboxdelegate.cpp \
    ../CdtTools/ui/tables/didata.cpp \
    ../CdtTools/ui/tables/ditablemodel.cpp \
    ../CdtTools/ui/cdtworkwidget.cpp \
    ../CdtTools/ui/tables/aitablemodel.cpp \
    ../CdtTools/ui/tables/aidata.cpp \
    ../CdtTools/ui/tables/delegates/digitlimitedelegate.cpp


HEADERS += \
    ../CdtTools/network/networkbase.h \
    ../CdtTools/network/tcpserver.h\
    ../CdtTools/common/threadpool.h \
    ../CdtTools/common/workerthread.h \
    ../CdtTools/protocol/cdtframe.h \
    ../CdtTools/protocol/cdtinteracte.h \
    ../CdtTools/protocol/cdtprotocol.h \
    ../CdtTools/protocol/checkhelper.h \
    ../CdtTools/protocol/protocolbase.h \
    ../CdtTools/common/util.h \
    ../CdtTools/ui/tables/delegates/comboboxdelegate.h \
    ../CdtTools/ui/tables/didata.h \
    ../CdtTools/ui/tables/ditablemodel.h \
    ../CdtTools/ui/cdtworkwidget.h \
    ../CdtTools/ui/tables/aitablemodel.h \
    ../CdtTools/ui/tables/aidata.h \
    ../CdtTools/ui/tables/delegates/digitlimitedelegate.h


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}

FORMS += \
    ../CdtTools/ui/cdtworkwidget.ui
