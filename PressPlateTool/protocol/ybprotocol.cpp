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
    std::copy(buff, buff + size, std::back_inserter(m_recvDataList));
}

void YBProtocol::appendDatas(const std::list<uint8_t> &dataList)
{
    std::copy(dataList.begin(), dataList.end(), std::back_inserter(m_recvDataList));
}

void YBProtocol::parseRecvData()
{
    while (!m_recvDataList.empty()) {
        if (parseToFrame() != eYBParseResult::NoError) {
            break;
        }
    }
}

eYBParseResult YBProtocol::parseToFrame()
{
    std::pair<YBFrame, eYBParseResult> result = YBFrame::parseBytesToFrame(m_recvDataList);
    if (result.second == eYBParseResult::NoError) {
        m_recvFrameQueue.emplace_back(result.first);
        // TODO(shijm): show recv
    } else if (result.second == eYBParseResult::CrcError) {
        // TODO(shijm): 显示错误报文
    }
    return result.second;
}

bool YBProtocol::recvFrameEmpty()
{
    return m_recvFrameQueue.empty();
}

YBFrame YBProtocol::popRecvFrame()
{
    auto frame = m_recvFrameQueue.front();
    m_recvFrameQueue.pop_front();
    return frame;
}

YBFrame YBProtocol::nakErrorFrame(uint8_t funCode, uint8_t errorCode, uint16_t dstAddr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBSensor;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::NAKCode;
    frame.m_dataLen = 0x02;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, {funCode, errorCode}));

    return frame;
}

YBFrame YBProtocol::settingStatus(uint8_t status, uint16_t dstAddr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBSensor;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::SetStatusCode;
    frame.m_dataLen = 0x01;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, {status}));

    return frame;
}

YBFrame YBProtocol::queryStatus(uint16_t dstAddr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBSensor;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::QueryStatusCode;
    frame.m_dataLen = 0x00;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode));


    return frame;
}

YBFrame YBProtocol::queryVersion(eYBFrameType type, uint16_t dstAddr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = type;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::QueryVersionCode;
    frame.m_dataLen = 0x00;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode));


    return frame;
}

YBFrame YBProtocol::settingAddress(eYBFrameType type, uint8_t addr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = type;
    frame.m_dstAddr = 0x007F;
    frame.m_funCode = eYBFunCode::SetAddressCode;
    frame.m_dataLen = 0x01;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, {addr}));

    return frame;
}

YBFrame YBProtocol::setSensorNum(uint16_t dstAddr, uint8_t num)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBGather;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::SetSensorNumCode;
    frame.m_dataLen = 0x01;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, {num}));

    return frame;
}

// TODO(shijm): 更改数据格式
YBFrame YBProtocol::upgradeProgram(const std::vector<uint8_t> &contentData)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBGather;
    frame.m_funCode = eYBFunCode::SetStatusCode;
    frame.m_dataLen = contentData.size();
    frame.m_data.clear();
    frame.m_data.resize(contentData.size());
    std::copy(contentData.begin(), contentData.end(), frame.m_data.begin());


    return frame;
}

YBFrame YBProtocol::forceSettingAddr(uint16_t addr)
{
    std::vector<uint8_t> datas;
    datas.push_back(addr & 0xFF);
    datas.push_back((addr >> 8) & 0xFF);
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = eYBFrameType::YBSensor;
    frame.m_funCode = eYBFunCode::ForceSettingAddrCode;
    frame.m_dataLen = 0x02;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode, datas));

    return frame;
}

YBFrame YBProtocol::queryAddress(eYBFrameType type, uint16_t dstAddr)
{
    YBFrame frame;
    frame.m_srcType = eYBFrameType::PCSoftware;
    frame.m_dstType = type;
    frame.m_dstAddr = dstAddr;
    frame.m_funCode = eYBFunCode::QueryAddrCode;
    frame.m_dataLen = 0x00;
    frame.m_dataContent.reset(ContentFactory::createContent(frame.m_funCode));


    return frame;
}
