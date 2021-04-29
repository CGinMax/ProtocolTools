#include "ybframe.h"
#include <algorithm>
#include <iterator>

const std::array<uint8_t, 6> YBFrame::header = {0xEB, 0x90, 0xEB, 0x90, 0xEB, 0x90};

YBFrame::YBFrame()
    : srcType(0)
    , dstType(0)
    , srcAddr(0)
    , dstAddr(0)
    , funCode(0)
    , dataLen(0)
    , crcCode(0)
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

    std::advance(iter, 6);

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
        return std::make_pair(frame, eYBParseResult::CrcError);
    }

    return std::make_pair(frame, eYBParseResult::NoError);
}

uint16_t YBFrame::calcCrc(const YBFrame &frame)
{
    std::vector<uint8_t> crcvec(frameMinLen - 8 + frame.data.size(), 0);
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
