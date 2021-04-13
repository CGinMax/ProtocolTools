#protocol pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    $$PWD/checkhelper.cpp \
    $$PWD/cdtframe.cpp \
    $$PWD/protocolbase.cpp \
    $$PWD/standard/cdtprotocol.cpp \
    $$PWD/interacte/cdtinteracte.cpp \
    $$PWD/ut/cdtexut.cpp \
    $$PWD/nr/cdtexnr.cpp \
    $$PWD/strategybase.cpp \
    $$PWD/standard/cdtwfstrategy.cpp \
    $$PWD/standard/cdtmintorstrategy.cpp \
    $$PWD/interacte/interwfstrategy.cpp \
    $$PWD/interacte/intermintorstrategy.cpp \
    $$PWD/ut/utwfstrategy.cpp \
    $$PWD/ut/utmintorstrategy.cpp \
    $$PWD/nr/nrwfstrategy.cpp \
    $$PWD/nr/nrmintorstrategy.cpp \
    $$PWD/cycle/cdtstandard.cpp \
    $$PWD/cycle/standardmintorstrategy.cpp \
    $$PWD/cycle/standardwfstrategy.cpp \
    $$PWD/nrudp/nrudpframe.cpp \
    $$PWD/nrudp/nrudpprotocol.cpp \
    $$PWD/nrudp/nrudpmintorstrategy.cpp \
    $$PWD/nrudp/nrudpwfstrategy.cpp

HEADERS += \
    $$PWD/checkhelper.h \
    $$PWD/cdtframe.h \
    $$PWD/standard/cdtprotocol.h \
    $$PWD/protocolbase.h \
    $$PWD/interacte/cdtinteracte.h \
    $$PWD/ut/cdtexut.h \
    $$PWD/nr/cdtexnr.h \
    $$PWD/strategybase.h \
    $$PWD/standard/cdtwfstrategy.h \
    $$PWD/standard/cdtmintorstrategy.h \
    $$PWD/interacte/interwfstrategy.h \
    $$PWD/interacte/intermintorstrategy.h \
    $$PWD/ut/utwfstrategy.h \
    $$PWD/ut/utmintorstrategy.h \
    $$PWD/nr/nrwfstrategy.h \
    $$PWD/nr/nrmintorstrategy.h \
    $$PWD/cycle/cdtstandard.h \
    $$PWD/cycle/standardmintorstrategy.h \
    $$PWD/cycle/standardwfstrategy.h \
    $$PWD/nrudp/nrudpframe.h \
    $$PWD/nrudp/nrudpprotocol.h \
    $$PWD/nrudp/nrudpmintorstrategy.h \
    $$PWD/nrudp/nrudpwfstrategy.h
