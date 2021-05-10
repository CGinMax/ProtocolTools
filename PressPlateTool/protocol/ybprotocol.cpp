#include "ybprotocol.h"
#include "content/contentfactory.h"

YBProtocol::YBProtocol()
{

}

YBProtocol::~YBProtocol()
{

}

void YBProtocol::appendDatas(uint8_t *buff, int size)
{
//    for (int i = 0; i < size; i++) {
//        recvDataList.push_back(*buff);
//        buff++;
//    }
    std::copy(buff, buff + size, std::back_inserter(recvDataList));
}

void YBProtocol::appendDatas(const std::list<uint8_t> &dataList)
{
    std::copy(dataList.begin(), dataList.end(), std::back_inserter(recvDataList));
}

void YBProtocol::parseRecvData()
{
    while (!recvDataList.empty()) {
        if (parseToFrame() != eYBParseResult::NoError) {
            break;
        }
    }
}

eYBParseResult YBProtocol::parseToFrame()
{
    std::pair<YBFrame, eYBParseResult> result = YBFrame::parseBytesToFrame(recvDataList);
    if (result.second == eYBParseResult::NoError) {
        recvFrameQueue.emplace_back(result.first);
        // TODO(shijm): show recv
    } else {

    }
    return result.second;
}

bool YBProtocol::recvFrameEmpty()
{
    return recvFrameQueue.empty();
}

YBFrame YBProtocol::popRecvFrame()
{
    auto frame = recvFrameQueue.front();
    recvFrameQueue.pop_front();
    return frame;
}

YBFrame YBProtocol::nakErrorFrame(uint8_t funCode, uint8_t errorCode, uint16_t dstAddr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBSensor;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::NAKCode;
    frame.dataLen = 0x02;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode, {funCode, errorCode}));

    return frame;
}

YBFrame YBProtocol::settingStatus(uint8_t status, uint16_t dstAddr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBSensor;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::SetStatusCode;
    frame.dataLen = 0x01;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode, {status}));

    return frame;
}

YBFrame YBProtocol::queryStatus(uint16_t dstAddr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBSensor;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::QueryStatusCode;
    frame.dataLen = 0x00;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode));


    return frame;
}

YBFrame YBProtocol::queryVersion(eYBFrameType type, uint16_t dstAddr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = type;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::QueryVersionCode;
    frame.dataLen = 0x00;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode));


    return frame;
}

YBFrame YBProtocol::settingAddress(eYBFrameType type, uint8_t addr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = type;
    frame.dstAddr = 0x007F;
    frame.funCode = eYBFunCode::SetAddressCode;
    frame.dataLen = 0x01;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode, {addr}));

    return frame;
}

YBFrame YBProtocol::setSensorNum(uint16_t dstAddr, uint8_t num)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBGather;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::SetSensorNumCode;
    frame.dataLen = 0x01;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode, {num}));

    return frame;
}

// TODO(shijm): 更改数据格式
YBFrame YBProtocol::upgradeProgram(const std::vector<uint8_t> &contentData)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBGather;
    frame.funCode = eYBFunCode::SetStatusCode;
    frame.dataLen = contentData.size();
    frame.data.clear();
    frame.data.resize(contentData.size());
    std::copy(contentData.begin(), contentData.end(), frame.data.begin());


    return frame;
}

YBFrame YBProtocol::forceSettingAddr(uint16_t addr)
{
    std::vector<uint8_t> datas;
    datas.push_back(addr & 0xFF);
    datas.push_back((addr >> 8) & 0xFF);
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = eYBFrameType::YBSensor;
    frame.funCode = eYBFunCode::ForceSettingAddrCode;
    frame.dataLen = 0x02;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode, datas));

    return frame;
}

YBFrame YBProtocol::queryAddress(eYBFrameType type, uint16_t dstAddr)
{
    YBFrame frame;
    frame.srcType = eYBFrameType::PCSoftware;
    frame.dstType = type;
    frame.dstAddr = dstAddr;
    frame.funCode = eYBFunCode::QueryAddrCode;
    frame.dataLen = 0x00;
    frame.dataContent.reset(ContentFactory::createContent(frame.funCode));


    return frame;
}
