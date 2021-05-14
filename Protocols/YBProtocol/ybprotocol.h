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

    void parseToFrame();

    bool isRecvFrameEmpty();
    YBFrame popRecvFrame();

    std::deque<YBProtocolException> popAllException();

//    void processFrame(const YBFrame& frame);// 外部处理

    YBFrame nakErrorFrame(uint8_t funCode, uint8_t errorCode, uint16_t dstAddr);

    YBFrame settingStatus(uint8_t status, uint16_t dstAddr);

    YBFrame queryStatus(uint16_t dstAddr);

    YBFrame queryVersion(eYBFrameType type, uint16_t dstAddr);

    YBFrame settingAddress(eYBFrameType type, uint8_t addr);

    YBFrame setSensorNum(uint16_t dstAddr, uint8_t num);

    // 暂时不用
    YBFrame upgradeProgram(const std::vector<uint8_t>& contentData);

    YBFrame forceSettingAddr(uint16_t addr);

    YBFrame queryAddress(eYBFrameType type, uint16_t dstAddr);


private:
    std::deque<YBFrame> m_recvFrameQueue;
    std::deque<YBProtocolException> m_recvExceptionQueue;
    std::list<uint8_t> m_recvDataList;
};

#endif // YBPROTOCOL_H
