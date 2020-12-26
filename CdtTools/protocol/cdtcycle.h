#ifndef CDTCYCLE_H
#define CDTCYCLE_H

#include <QQueue>
#include "cdtframe.h"
#include "network/networkbase.h"

class CDTCycle
{
public:
    CDTCycle();
    // 解析接收数据接口
    void parseRecvData();
    // 解析数据，封装成帧
    eCDTParseResult parseToFrame();

    void processFrame();

    // 遥控
    void ykCommand(uint8_t ctrlCode, uint8_t objNo);

    // 命令帧
    void createCmdFrame(uint8_t type, uint8_t funCode, uint8_t ctrlCode, uint8_t objNo);


    // 遥信
    void yxResponse(QList<InfoFieldEntity> &infoFieldList);

    // 遥测
    void ycResponse(QList<InfoFieldEntity> &infoFieldList);

    // 电度
    void accResponse(QList<InfoFieldEntity> &infoFieldList);

    // 循环上送遥信
    void cycleSendYX();

    // 循环上送遥测
    void cycleSendYC();

    // 循环上送电度量
    void cycleSendAcc();

    void ykExecuted(int ptId);

    void yKCancel(uint8_t objNo);

    void yKNotAllow(int ptId);

    void yKAllNotAllow();

    // 非全部点遥控帧，则要传入点号
    CDTFrame createCycleYKFrame(bool isAllPoint, int ptId = -1);

protected:
    double bcdToValue(int bcdValue);

    uint32_t valueToBCD(double value);


    QByteArray m_recvBuffer;
    QQueue<CDTFrame> m_frameQueue;

    bool isRunYK;
};

#endif // CDTCYCLE_H
