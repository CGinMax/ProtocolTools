#ifndef YBFRAMEENUMS_H
#define YBFRAMEENUMS_H

#include "../protocols_global.h"

enum PROTOCOLSSHARED_EXPORT eYBFrameType
{
    PCSoftware  = 0x02,
    YBGather    = 0x20,
    YBSensor    = 0x21,
};

enum PROTOCOLSSHARED_EXPORT eYBNAKCode
{
    NAKVaildCode = 0x01,
    NAKNumErrorCode = 0x02,
    NAKCrcErrorCode = 0x03,
};

enum PROTOCOLSSHARED_EXPORT eYBFunCode
{
    NAKCode                 = 0x01,
    SetStatusCode           = 0x02,
    QueryStatusCode         = 0x03,
    QueryVersionCode        = 0x04,
    SetAddressCode          = 0x05,
    ReportStatusCode        = 0x06,
    SetSensorNumCode        = 0x0A,
    UpgradeCode             = 0x84,
    ForceSettingAddrCode    = 0x90,
    QueryAddrCode           = 0x91,
};

enum PROTOCOLSSHARED_EXPORT eYBParseResult {
    NoError,            // Complete Frame
    HeaderError,        // Header Error
    NotComplete,        // not complete
    CrcError,           // CRC Error
};

#endif // YBFRAMEENUMS_H
