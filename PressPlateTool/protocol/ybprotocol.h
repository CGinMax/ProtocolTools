#ifndef YBPROTOCOL_H
#define YBPROTOCOL_H

#include "iprotocol.h"
#include <deque>
#include "ybframe.h"
class YBProtocol : public IProtocol
{
public:
    YBProtocol();
    ~YBProtocol() override;

    void appendDatas(uint8_t* buff, int size);

    void appendDatas(const std::list<uint8_t>& dataList);

    void parseRecvData();

    eYBParseResult parseToFrame();

    std::deque<YBFrame> getRecvFrameQueue();

//    void processFrame(const YBFrame& frame);// 外部处理

    YBFrame nakErrorFrame(uint8_t funCode, uint8_t errorCode, uint16_t dstAddr);

    YBFrame settingStatus(uint8_t status, uint16_t dstAddr);

    YBFrame queryStatus(uint16_t dstAddr);

    YBFrame queryVersion(eYBFrameType type, uint16_t dstAddr);

    YBFrame settingAddr(eYBFrameType type, uint8_t addr);

    // 暂时不用
    YBFrame upgradeProgram(const std::vector<uint8_t>& contentData);

    YBFrame forceSettingAddr(uint16_t addr);

    YBFrame queryAddr(eYBFrameType type, uint16_t dstAddr);


private:
    std::deque<YBFrame> recvFrameQueue;
    std::deque<YBFrame> sendFrameQueue;
    std::list<uint8_t> recvDataList;
};

#endif // YBPROTOCOL_H
