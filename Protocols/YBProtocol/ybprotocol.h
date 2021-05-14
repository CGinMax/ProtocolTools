#ifndef YBPROTOCOL_H
#define YBPROTOCOL_H

#include "../iprotocols.h"
#include <deque>
#include "ybframe.h"

class YBProtocolException;

class PROTOCOLSSHARED_EXPORT YBProtocol : public IProtocols
{
public:
    YBProtocol();
    ~YBProtocol() override;

    void appendDatas(uint8_t* buff, int size);

    void appendDatas(const std::list<uint8_t>& dataList);

    void parseRecvData();

    bool isRecvFrameEmpty();
    YBFrame popRecvFrame();

    std::deque<YBProtocolException> popAllException();

//    void processFrame(const YBFrame& frame);// 外部处理


private:
    std::deque<YBFrame> m_recvFrameQueue;
    std::deque<YBProtocolException> m_recvExceptionQueue;
    std::list<uint8_t> m_recvDataList;
};

#endif // YBPROTOCOL_H
