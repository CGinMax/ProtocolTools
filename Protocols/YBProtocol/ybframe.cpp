#include "ybframe.h"
#include <algorithm>
#include <iterator>
#include "../convert.h"
#include "content/contentfactory.h"
#include "ybprotocolexception.h"

const std::map<int, std::string> YBFrame::FRAME_TYPE_MAP{{0x02, u8"一匙通PC软件"}, {0x20, u8"压版采集器"}, {0x21, u8"压版传感器"}};

const std::array<uint8_t, 4> YBFrame::HEADER_DATA = {0xEB, 0x90, 0xEB, 0x90};

YBFrame::YBFrame()
    : m_srcType(0)
    , m_dstType(0)
    , m_srcAddr(0)
    , m_dstAddr(0)
    , m_funCode(0)
    , m_dataLen(0)
    , m_crcCode(0)
    , m_isSend(true)
    , m_dataContent(nullptr)
{

}

YBFrame::~YBFrame()
{
}

YBFrame::YBFrame(const YBFrame &other)
{
    *this = other;
}

YBFrame &YBFrame::operator=(const YBFrame &other)
{
    m_data.clear();
    m_srcType = other.m_srcType;
    m_dstType = other.m_dstType;
    m_srcAddr = other.m_srcAddr;
    m_dstAddr = other.m_dstAddr;
    m_funCode = other.m_funCode;
    m_dataLen = other.m_dataLen;
    std::copy(other.m_data.begin(), other.m_data.end(), std::back_inserter(m_data));
    m_crcCode = other.m_crcCode;
    m_isSend = other.m_isSend;
    m_dataContent = other.m_dataContent;
    return *this;
}

YBFrame YBFrame::parseBytesToFrame(std::list<uint8_t> &datas)
{
    YBFrame frame;
    // header
    auto iter = std::search(datas.begin(), datas.end(), HEADER_DATA.begin(), HEADER_DATA.end());
    if (iter == datas.end()) {
        throw YBProtocolException(eYBParseResult::HeaderError, "not found header");
    }

    std::advance(iter, HEADER_DATA.size());

    if (iter == datas.end()
            || static_cast<int>(std::distance(iter, datas.end())) < static_cast<int>(FRAME_MIN_LEN - HEADER_DATA.size())) {
        throw YBProtocolException(eYBParseResult::NotComplete, "Parse not complete! Just " + std::to_string(std::distance(iter, datas.end())) + " bytes after header!");
    }

    // src type
    frame.m_srcType = *iter++;
    // dst type
    frame.m_dstType = *iter++;
    // dst ddr
    uint16_t low = *iter++;
    uint16_t hight = *iter++;
    frame.m_srcAddr = static_cast<uint16_t>(hight << 8) | low;
    // src addr
    low = *iter++;
    hight = *iter++;
    frame.m_dstAddr = static_cast<uint16_t>(hight << 8) | low;
    frame.m_funCode = *iter++;
    low = *iter++;
    hight = *iter++;
    frame.m_dataLen = static_cast<uint16_t>(hight << 8) | low;

    if (frame.m_dataLen + 2 > std::distance(iter, datas.end())) {
        throw YBProtocolException(eYBParseResult::NotComplete, "Parse not complete! Just " + std::to_string(std::distance(iter, datas.end())) + " bytes after dataLen!");
    }

    frame.m_data.resize(frame.m_dataLen, 0);
    std::copy_n(iter, frame.m_dataLen, frame.m_data.begin());
    std::advance(iter, frame.m_dataLen);

    // calc crc
    uint16_t currentCrc = calcCrc(frame);

    low = *iter++;
    hight = *iter++;
    frame.m_crcCode = static_cast<uint16_t>(hight << 8) | low;

    if (currentCrc != frame.m_crcCode) {
        // crc错误删除错误报文
        datas.erase(datas.begin(), iter);
        throw YBProtocolException(eYBParseResult::CrcError, "Crc Error:receive crc=" + Convert::num2HexString(frame.m_crcCode) + ", parsed crc=" + Convert::num2HexString(currentCrc));
    }

    frame.m_isSend = false;
    if (frame.m_dataContent == nullptr) {
        frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, frame.m_data));
    }
    // 完整时删除完整报文数据
    datas.erase(datas.begin(), iter);
    return frame;
}

uint16_t YBFrame::calcCrc(const YBFrame &frame)
{
    std::vector<uint8_t> crcvec(FRAME_MIN_LEN - HEADER_DATA.size() - 2 + frame.m_data.size(), 0);
    crcvec[0] = frame.m_srcType;
    crcvec[1] = frame.m_dstType;
    crcvec[2] = static_cast<uint8_t>(frame.m_srcAddr);
    crcvec[3] = static_cast<uint8_t>(frame.m_srcAddr >> 8);
    crcvec[4] = static_cast<uint8_t>(frame.m_dstAddr);
    crcvec[5] = static_cast<uint8_t>(frame.m_dstAddr >> 8);
    crcvec[6] = frame.m_funCode;
    crcvec[7] = static_cast<uint8_t>(frame.m_dataLen);
    crcvec[8] = static_cast<uint8_t>(frame.m_dataLen >> 8);
    std::copy(frame.m_data.begin(), frame.m_data.end(), crcvec.begin() + (FRAME_MIN_LEN - HEADER_DATA.size() - 2));

    return checkCRC16(crcvec, 0);

}

std::string YBFrame::parseToString()
{
    std::list<std::string> strList;

    strList.emplace_back(u8"源类型:");
    strList.emplace_back(FRAME_TYPE_MAP.at(m_srcType));
    strList.emplace_back(u8"(" + Convert::num2HexString(m_srcType) + u8")");
    strList.emplace_back(u8", 目的类型:");
    strList.emplace_back(FRAME_TYPE_MAP.at(m_dstType));
    strList.emplace_back(u8"(" + Convert::num2HexString(m_dstType) + u8")");

    strList.emplace_back(u8", 源地址:");
    strList.emplace_back(std::to_string(m_srcAddr));

    strList.emplace_back(u8", 目的地址:");
    strList.emplace_back(std::to_string(m_dstAddr));

    strList.emplace_back(u8", 功能码:");
    strList.emplace_back(std::to_string(m_funCode));
    strList.emplace_back(u8"(" + Convert::num2HexString(m_funCode) + u8")");

    strList.emplace_back(u8", 数据正文长度:");
    strList.emplace_back(std::to_string(m_dataLen));

    if (m_dataContent == nullptr) {
        m_dataContent.reset(ContentFactory::createContent(m_funCode, m_data));
    }
    std::string contentStr = m_dataContent->toString(m_isSend);
    if (!contentStr.empty()) {
        strList.push_back(contentStr);
    }

    strList.emplace_back(u8", crc16校验码:");
    strList.emplace_back(std::to_string(m_crcCode));
    strList.emplace_back(u8"(" + Convert::num2HexString(m_crcCode | 0xFF) + " " + Convert::num2HexString((m_crcCode >> 8) | 0xFF) + u8")");

    std::string result;
    for (auto& str : strList) {
        result += str;
    }
    return result;
}

std::vector<uint8_t> YBFrame::packetFrameToPureData()
{
    if (m_dataLen > 0 && m_dataContent != nullptr) {
        m_data = m_dataContent->toByteVector();
    }
    m_crcCode = calcCrc(*this);

    uint pos = 0;
    std::vector<uint8_t> packetDatas(FRAME_MIN_LEN + m_data.size(), 0);
    std::copy(HEADER_DATA.begin(), HEADER_DATA.end(), packetDatas.begin());
    pos += HEADER_DATA.size();

    packetDatas[pos++] = m_srcType;
    packetDatas[pos++] = m_dstType;
    packetDatas[pos++] = m_srcAddr & 0xFF;
    packetDatas[pos++] = (m_srcAddr >> 8) & 0xFF;
    packetDatas[pos++] = m_dstAddr & 0xFF;
    packetDatas[pos++] = (m_dstAddr >> 8) & 0xFF;
    packetDatas[pos++] = m_funCode;
    packetDatas[pos++] = m_dataLen & 0xFF;
    packetDatas[pos++] = (m_dataLen >> 8) & 0xFF;
    std::copy(m_data.begin(), m_data.end(), packetDatas.begin() + pos);
    pos += m_dataLen;
    packetDatas[pos++] = m_crcCode & 0xFF;
    packetDatas[pos++] = (m_crcCode >> 8) & 0xFF;
    return packetDatas;
}

std::vector<uint8_t> YBFrame::packetFrameToSeparator(unsigned char separator)
{
    if (m_dataLen > 0 && m_dataContent != nullptr) {
        m_data = m_dataContent->toByteVector();
    }
    m_crcCode = calcCrc(*this);
    auto separatorData = m_dataContent->toByteVector();

    uint pos = 0;
    std::vector<uint8_t> packetDatas(FRAME_MIN_LEN + m_data.size(), 0);
    std::copy(HEADER_DATA.begin(), HEADER_DATA.end(), packetDatas.begin());
    pos += HEADER_DATA.size();

    packetDatas[pos++] = m_srcType;
    packetDatas[pos++] = m_dstType;
    packetDatas[pos++] = m_srcAddr & 0xFF;
    packetDatas[pos++] = (m_srcAddr >> 8) & 0xFF;
    packetDatas[pos++] = m_dstAddr & 0xFF;
    packetDatas[pos++] = (m_dstAddr >> 8) & 0xFF;
    packetDatas[pos++] = m_funCode;
    packetDatas[pos++] = m_dataLen & 0xFF;
    packetDatas[pos++] = (m_dataLen >> 8) & 0xFF;
    std::copy(m_data.begin(), m_data.end(), packetDatas.begin() + pos);
    pos += m_data.size();
    packetDatas[pos++] = m_crcCode & 0xFF;
    packetDatas[pos++] = (m_crcCode >> 8) & 0xFF;
    return packetDatas;
}

uint16_t YBFrame::checkCRC16(std::vector<uint8_t> buff, int offset)
{
    uint16_t result = 0xffff;
    for (int i = offset; i < static_cast<int>(buff.size()); i++)
    {
        for (uint8_t b = 0x80; b != 0; b >>= 1)
        {
            if ((result & static_cast<uint16_t>(0x8000)) != 0)
            {
                result <<= 1;
                result ^= 0x1021;
            }
            else
            {
                result <<= 1;
            }
            if ((buff.at(i) & b) != 0)
            {
                result ^= 0x1021;
            }
        }
    }
    return result;
}
