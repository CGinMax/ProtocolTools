#protocol pri

QT       += core concurrent

CONFIG += c++11
SOURCES += \
    protocol/checkhelper.cpp \
    protocol/cdtframe.cpp \
    protocol/protocolbase.cpp \
    protocol/standard/cdtprotocol.cpp \
    protocol/interacte/cdtinteracte.cpp \
    protocol/ut/cdtexut.cpp \
    protocol/nr/cdtexnr.cpp \
    protocol/strategybase.cpp \
    protocol/standard/cdtwfstrategy.cpp \
    protocol/standard/cdtmintorstrategy.cpp \
    protocol/interacte/interwfstrategy.cpp \
    protocol/interacte/intermintorstrategy.cpp \
    protocol/ut/utwfstrategy.cpp \
    protocol/ut/utmintorstrategy.cpp \
    protocol/nr/nrwfstrategy.cpp \
    protocol/nr/nrmintorstrategy.cpp \
    protocol/cycle/cdtstandard.cpp \
    protocol/cycle/standardmintorstrategy.cpp \
    protocol/cycle/standardwfstrategy.cpp \
    protocol/nrudp/nrudpframe.cpp \
    protocol/nrudp/nrudpprotocol.cpp \
    protocol/nrudp/nrudpmintorstrategy.cpp \
    protocol/nrudp/nrudpwfstrategy.cpp

HEADERS += \
    protocol/checkhelper.h \
    protocol/cdtframe.h \
    protocol/standard/cdtprotocol.h \
    protocol/protocolbase.h \
    protocol/interacte/cdtinteracte.h \
    protocol/ut/cdtexut.h \
    protocol/nr/cdtexnr.h \
    protocol/strategybase.h \
    protocol/standard/cdtwfstrategy.h \
    protocol/standard/cdtmintorstrategy.h \
    protocol/interacte/interwfstrategy.h \
    protocol/interacte/intermintorstrategy.h \
    protocol/ut/utwfstrategy.h \
    protocol/ut/utmintorstrategy.h \
    protocol/nr/nrwfstrategy.h \
    protocol/nr/nrmintorstrategy.h \
    protocol/cycle/cdtstandard.h \
    protocol/cycle/standardmintorstrategy.h \
    protocol/cycle/standardwfstrategy.h \
    protocol/nrudp/nrudpframe.h \
    protocol/nrudp/nrudpprotocol.h \
    protocol/nrudp/nrudpmintorstrategy.h \
    protocol/nrudp/nrudpwfstrategy.h
