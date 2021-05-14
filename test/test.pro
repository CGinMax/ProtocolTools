QT += core testlib gui widgets network concurrent

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app

include(../ProtocolTools/common/common.pri)
#include(../ProtocolTools/network/network.pri)
#include(../ProtocolTools/protocol/protocol.pri)
#include(../ProtocolTools/ui/ui.pri)
include(../PressPlateTool/protocol/protocol.pri)

SOURCES += \
    tst_networktest.cpp \


HEADERS += \


INCLUDEPATH += $$PWD/../Protocols/
DEPENDPATH += $$PWD/../Protocols/


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}
LIBS += -L$${DESTDIR} -lProtocols

