#include "ybframe.h"
#include <algorithm>
#include <iterator>
#include "utilhelper.h"
#include "content/contentfactory.h"

std::map<int, std::string> YBFrame::frameTypeMap{{0x02, u8"一匙通PC软件"}, {0x20, u8"压版采集器"}, {0x21, u8"压版传感器"}};

const std::array<uint8_t, 4> YBFrame::header = {0xEB, 0x90, 0xEB, 0x90};

YBFrame::YBFrame()
    : srcType(0)
    , dstType(0)
    , srcAddr(0)
    , dstAddr(0)
    , funCode(0)
    , dataLen(0)
    , crcCode(0)
    , isSend(true)
    , dataContent(nullptr)
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
    data.clear();
    srcType = other.srcType;
    dstType = other.dstType;
    srcAddr = other.srcAddr;
    dstAddr = other.dstAddr;
    funCode = other.funCode;
    dataLen = other.dataLen;
    std::copy(other.data.begin(), other.data.end(), std::back_inserter(data));
    crcCode = other.crcCode;
    isSend = other.isSend;
    dataContent = other.dataContent;
    return *this;
}

std::pair<YBFrame, eYBParseResult> YBFrame::parseBytesToFrame(std::list<uint8_t> &datas)
{
    YBFrame frame;
    // header
    auto iter = std::search(datas.begin(), datas.end(), header.begin(), header.end());
    if (iter == datas.end()) {
        return std::make_pair(YBFrame(), eYBParseResult::HeaderError);
    }

    std::advance(iter, header.size());

    if (iter == datas.end()
            || static_cast<int>(std::distance(iter, datas.end())) < static_cast<int>(frameMinLen - header.size())) {
        return std::make_pair(YBFrame(), eYBParseResult::NotComplete);
    }

    // src type
    frame.srcType = *iter++;
    // dst type
    frame.dstType = *iter++;
    // dst ddr
    uint16_t low = *iter++;
    uint16_t hight = *iter++;
    frame.srcAddr = static_cast<uint16_t>(hight << 8) | low;
    // src addr
    low = *iter++;
    hight = *iter++;
    frame.dstAddr = static_cast<uint16_t>(hight << 8) | low;
    frame.funCode = *iter++;
    low = *iter++;
    hight = *iter++;
    frame.dataLen = static_cast<uint16_t>(hight << 8) | low;

    if (frame.dataLen > std::distance(iter, datas.end())) {
        return std::make_pair(frame, eYBParseResult::DataLengthError);
    }
    if (frame.dataLen + 2 > std::distance(iter, datas.end())) {
        return std::make_pair(frame, eYBParseResult::NotComplete);
    }

    frame.data.resize(frame.dataLen, 0);
    std::copy_n(iter, frame.dataLen, frame.data.begin());
    std::advance(iter, frame.dataLen);

    // calc crc
    uint16_t currentCrc = calcCrc(frame);

    low = *iter++;
    hight = *iter++;
    frame.crcCode = static_cast<uint16_t>(hight << 8) | low;

    if (currentCrc != frame.crcCode) {
        // crc错误删除错误报文
        datas.erase(datas.begin(), iter);
        return std::make_pair(frame, eYBParseResult::CrcError);
    }

    frame.isSend = false;
    if (frame.dataContent == nullptr) {
        frame.dataContent.reset(ContentFactory::createContent(frame.funCode, frame.data));
    }
    // 完整时删除完整报文数据
    datas.erase(datas.begin(), iter);
    return std::make_pair(frame, eYBParseResult::NoError);
}

uint16_t YBFrame::calcCrc(const YBFrame &frame)
{
    std::vector<uint8_t> crcvec(frameMinLen - header.size() - 2 + frame.data.size(), 0);
    crcvec[0] = frame.srcType;
    crcvec[1] = frame.dstType;
    crcvec[2] = static_cast<uint8_t>(frame.srcAddr);
    crcvec[3] = static_cast<uint8_t>(frame.srcAddr >> 8);
    crcvec[4] = static_cast<uint8_t>(frame.dstAddr);
    crcvec[5] = static_cast<uint8_t>(frame.dstAddr >> 8);
    crcvec[6] = frame.funCode;
    crcvec[7] = static_cast<uint8_t>(frame.dataLen);
    crcvec[8] = static_cast<uint8_t>(frame.dataLen >> 8);
    std::copy(frame.data.begin(), frame.data.end(), crcvec.begin() + 9);

    return checkCRC16(crcvec, 0);

}

std::string YBFrame::parseToString()
{
    std::list<std::string> strList;

    strList.emplace_back(u8"源类型:");
    strList.emplace_back(frameTypeMap.at(srcType));
    strList.emplace_back(u8"(" + UtilHelper::num2HexString(srcType) + u8")");
    strList.emplace_back(u8", 目的类型:");
    strList.emplace_back(frameTypeMap.at(dstType));
    strList.emplace_back(u8"(" + UtilHelper::num2HexString(dstType) + u8")");

    strList.emplace_back(u8", 源地址:");
    strList.emplace_back(std::to_string(srcAddr));

    strList.emplace_back(u8", 目的地址:");
    strList.emplace_back(std::to_string(dstAddr));

    strList.emplace_back(u8", 功能码:");
    strList.emplace_back(std::to_string(funCode));
    strList.emplace_back(u8"(" + UtilHelper::num2HexString(funCode) + u8")");

    strList.emplace_back(u8", 数据正文长度:");
    strList.emplace_back(std::to_string(dataLen));

    if (dataContent == nullptr) {
        dataContent.reset(ContentFactory::createContent(funCode, data));
    }
    std::string contentStr = dataContent->toString(isSend);
    if (!contentStr.empty()) {
        strList.push_back(contentStr);
    }

    strList.emplace_back(u8", crc16校验码:");
    strList.emplace_back(std::to_string(crcCode));
    strList.emplace_back(u8"(" + UtilHelper::num2HexString(crcCode | 0xFF) + " " + UtilHelper::num2HexString((crcCode >> 8) | 0xFF) + u8")");

    std::string result;
    for (auto& str : strList) {
        result += str;
    }
    return result;
}

std::vector<uint8_t> YBFrame::packetFrame()
{
    if (dataLen > 0 && dataContent != nullptr) {
        data = dataContent->toByteVector();
    }
    crcCode = calcCrc(*this);

    uint pos = 0;
    std::vector<uint8_t> packetDatas(frameMinLen + data.size(), 0);
    std::copy(header.begin(), header.end(), packetDatas.begin());
    pos += header.size();

    packetDatas[pos++] = srcType;
    packetDatas[pos++] = dstType;
    packetDatas[pos++] = srcAddr & 0xFF;
    packetDatas[pos++] = (srcAddr >> 8) & 0xFF;
    packetDatas[pos++] = dstAddr & 0xFF;
    packetDatas[pos++] = (dstAddr >> 8) & 0xFF;
    packetDatas[pos++] = funCode;
    packetDatas[pos++] = dataLen & 0xFF;
    packetDatas[pos++] = (dataLen >> 8) & 0xFF;
    std::copy(data.begin(), data.end(), packetDatas.begin() + pos);
    pos += data.size();
    packetDatas[pos++] = crcCode & 0xFF;
    packetDatas[pos++] = (crcCode >> 8) & 0xFF;
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
