QT += core testlib gui widgets network concurrent

CONFIG += qt testcase warn_on depend_includepath
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app

include(../ProtocolTool/common/common.pri)
#include(../ProtocolTool/network/network.pri)
#include(../ProtocolTool/protocol/protocol.pri)
#include(../ProtocolTool/ui/ui.pri)
include(../PressPlateTool/protocol/protocol.pri)

SOURCES += \
    tst_networktest.cpp \


HEADERS += \


INCLUDEPATH += $$PWD/../Protocols/
DEPENDPATH += $$PWD/../Protocols/

INCLUDEPATH += $$PWD/../Communication/
DEPENDPATH += $$PWD/../Communication/


CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin/debug
}
else {
    DESTDIR = $$PWD/../bin/release
}
LIBS += -L$${DESTDIR} -lProtocols
LIBS += -L$${DESTDIR} -lCommunication
