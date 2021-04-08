#include "nrudpframe.h"
#include "../checkhelper.h"

uint8_t NrUdpFrame::header[7] = { 0x90, 0xEB, 0x90, 0xEB, 0x90, 0xEB, 0x00};

NrUdpFrame::NrUdpFrame()
    : length(0)
    , srcAddr(0)
    , dstAddr(0)
    , scheduling(0)
    , cmdCode(0)
    , crcCode(0)
{

}

NrUdpFrame::eNrParseResult NrUdpFrame::parseBytesToFrame(QByteArray &data, int &index, QString &errorMsg)
{
    // 1、解析头
    // 查找是否有帧头
    index = data.indexOf(reinterpret_cast<char *>(NrUdpFrame::header));
    if (index == -1)
    {
        // 未找到帧头
        if (data.size() >= 6)
        {
            errorMsg = QString("接受数据帧头部错误,未找到帧头, 接收到的数据帧长度为%1").arg(data.size());
            data.clear();
        }
        return eNrParseResult::HeaderError;
    }

    index += 6;

    if (data.size() - index < 2)
    {
        errorMsg = QString("报文长度不够, 接收到的数据帧长度为%2").arg(data.size());
        return eNrParseResult::PartOfFrame;
    }
    length = static_cast<uint16_t>(data.at(index++) & 0xFF);
    length |= static_cast<uint16_t>(data.at(index++) & 0xFF) << 8;

    // 实际接收长度不等于报文内置长度
    if (data.size() - index < length)
    {
        errorMsg = QString("报文长度错误, 报文长度为:%1, 接收到的数据帧长度为:%2").arg(length).arg(data.size());
        return eNrParseResult::PartOfFrame;
    }

    srcAddr    = static_cast<uint8_t>(data.at(index++));
    dstAddr    = static_cast<uint8_t>(data.at(index++));
    scheduling = static_cast<uint8_t>(data.at(index++));
    cmdCode    = static_cast<uint8_t>(data.at(index));
    index += 3;
    int validLength = data.at(index++) & 0xFF;
    validLength = validLength | (static_cast<uint16_t>(data.at(index++) & 0xFF) << 8);
    infoData = data.mid(index, validLength);
    index += validLength;

    setDataBuf();

    if (crcCode != static_cast<uint8_t>(data.at(index)))
    {
        errorMsg = QString("校验码错误, 接收到的校验码为:%1, 实际校验码为:%2").arg(data.at(index)).arg(crcCode);
        return eNrParseResult::CRCError;
    }
    index++;

    return eNrParseResult::CompleteFrame;
}

void NrUdpFrame::setDataBuf()
{
    allFrameBytes.clear();
    allFrameBytes.append(reinterpret_cast<char*>(NrUdpFrame::header), 6);
    allFrameBytes.append(static_cast<char>(length & 0x00FF));
    allFrameBytes.append(static_cast<char>((length >> 8) & 0x00FF));
    allFrameBytes.append(srcAddr);
    allFrameBytes.append(dstAddr);
    allFrameBytes.append(scheduling);
    allFrameBytes.append(cmdCode);
    allFrameBytes.append('\0');
    allFrameBytes.append('\0');
    allFrameBytes.append(infoData.length() & 0xFF);
    allFrameBytes.append((infoData.length() >> 8) & 0xFF);
    allFrameBytes.append(infoData);
    crcCode = CheckHelper::CheckSum8(reinterpret_cast<uchar*>(allFrameBytes.data()), 0, allFrameBytes.length());
    allFrameBytes.append(crcCode);
}
