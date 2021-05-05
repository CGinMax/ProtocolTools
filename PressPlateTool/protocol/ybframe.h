#ifndef YBFRAME_H
#define YBFRAME_H

#include <cstdint>
#include <utility>
#include <array>
#include <list>
#include <iterator>
#include <vector>

#include "content/icontent.h"

enum eYBFrameType
{
    YBCollector = 0x20,
    YBSensor    = 0x21,
};

enum eYBNAKCode
{
    NAKVaildCode = 0x01,
    NAKNumErrorCode = 0x02,
    NAKCrcErrorCode = 0x03,
};

enum eYBFunCode
{
    SettingStatusCode       = 0x02,
    QueryStatusCode         = 0x03,
    QueryVersionCode        = 0x04,
    SettingAddrCode         = 0x05,
    ReportStatusCode        = 0x06,
    UpgradeCode             = 0x84,
    ForceSettingAddrCode    = 0x90,
    QueryAddrCode           = 0x91,
};

enum eYBParseResult {
    NoError,            // Complete Frame
    HeaderError,        // Header Error
    NotComplete,        // not complete
    DataLengthError,    // Protocol Length != Actual Data Length
    CrcError,           // CRC Error
};

class YBFrame
{
public:
    static uint16_t checkCRC16(std::vector<uint8_t> buff, int offset);
    YBFrame();
    ~YBFrame();
    YBFrame(const YBFrame& other);
    YBFrame& operator=(const YBFrame& other);
    static std::pair<YBFrame, eYBParseResult> parseBytesToFrame(std::list<uint8_t>& datas);
    static uint16_t calcCrc(const YBFrame& frame);
    // 报文数据
    static const std::array<uint8_t, 6> header;
    uint8_t srcType;
    uint8_t dstType;
    uint16_t srcAddr;
    uint16_t dstAddr;
    uint8_t funCode;
    uint16_t dataLen;
    std::vector<uint8_t> data;
    uint16_t crcCode;

    static const uint8_t frameMinLen = 17; // 17

    std::string parseToString();

private:
    bool isSend;
    IContent* dataContent;
};

#endif // YBFRAME_H
