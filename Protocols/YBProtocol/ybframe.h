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
#include "ybframeenums.h"

class PROTOCOLSSHARED_EXPORT YBFrame
{
public:
    static uint16_t checkCRC16(std::vector<uint8_t> buff, int offset);
    YBFrame();
    ~YBFrame();
    YBFrame(const YBFrame& other);
    YBFrame& operator=(const YBFrame& other);
    static YBFrame parseBytesToFrame(std::list<uint8_t>& datas);
    static uint16_t calcCrc(const YBFrame& frame);
    std::string parseToString();

    std::vector<uint8_t> packetFrameToPureData();
    std::vector<uint8_t> packetFrameToSeparator(unsigned char separator);

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
