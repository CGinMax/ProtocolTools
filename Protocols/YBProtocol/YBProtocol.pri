# yb protocol
QT -= gui
CONFIG += c++11

HEADERS += \
    $$PWD/content/contentfactory.h \
    $$PWD/content/contentforcesetaddr.h \
    $$PWD/content/contentnakerror.h \
    $$PWD/content/contentqueryaddr.h \
    $$PWD/content/contentquerystatus.h \
    $$PWD/content/contentqueryversion.h \
    $$PWD/content/contentreportstatus.h \
    $$PWD/content/contentsetsensornum.h \
    $$PWD/content/contentsettingaddr.h \
    $$PWD/content/contentsettingstatus.h \
    $$PWD/content/icontent.h \
    $$PWD/ybframe.h \
    $$PWD/ybframeenums.h \
    $$PWD/ybprotocol.h \
    $$PWD/ybprotocolexception.h

SOURCES += \
    $$PWD/content/contentfactory.cpp \
    $$PWD/content/contentforcesetaddr.cpp \
    $$PWD/content/contentnakerror.cpp \
    $$PWD/content/contentqueryaddr.cpp \
    $$PWD/content/contentquerystatus.cpp \
    $$PWD/content/contentqueryversion.cpp \
    $$PWD/content/contentreportstatus.cpp \
    $$PWD/content/contentsetsensornum.cpp \
    $$PWD/content/contentsettingaddr.cpp \
    $$PWD/content/contentsettingstatus.cpp \
    $$PWD/content/icontent.cpp \
    $$PWD/ybframe.cpp \
    $$PWD/ybprotocol.cpp \
    $$PWD/ybprotocolexception.cpp


