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
        try {
            YBFrame result = YBFrame::parseBytesToFrame(m_recvDataList);
            m_recvFrameQueue.push_back(result);

        } catch (const YBProtocolException& e) {
            m_recvExceptionQueue.emplace_back(e);
        }

    }
}

bool YBProtocol::isRecvFrameEmpty()
{
    return m_recvFrameQueue.empty();
}

YBFrame YBProtocol::popRecvFrame()
{
    auto frame = m_recvFrameQueue.front();
    m_recvFrameQueue.pop_front();
    return frame;
}

std::deque<YBProtocolException> YBProtocol::popAllException()
{
    std::deque<YBProtocolException> results;
    m_recvExceptionQueue.swap(results);
    return results;
}
