#ifndef YBFRAME_H
#define YBFRAME_H

#include <cstdint>
#include <utility>
#include <array>
#include <map>
#include <list>
#include <iterator>
#include <vector>
#include <memory>

#include "content/icontent.h"

enum eYBFrameType
{
    PCSoftware  = 0x02,
    YBGather    = 0x20,
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
    std::string parseToString();

    std::vector<uint8_t> packetFrame();

    // 报文数据
    static const std::array<uint8_t, 4> HEADER_DATA;
    uint8_t m_srcType;
    uint8_t m_dstType;
    uint16_t m_srcAddr;
    uint16_t m_dstAddr;
    uint8_t m_funCode;
    uint16_t m_dataLen;
    std::vector<uint8_t> m_data;
    uint16_t m_crcCode;

    static const uint8_t FRAME_MIN_LEN = 15; // 15

    static const std::map<int, std::string> FRAME_TYPE_MAP;

    bool m_isSend;
    std::shared_ptr<IContent> m_dataContent;
};

#endif // YBFRAME_H
