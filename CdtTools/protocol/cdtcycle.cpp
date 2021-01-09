#include "cdtcycle.h"
#include <QThread>

CDTCycle::CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData)
    : CDTProtocol (network, settingData)
{

}

CDTCycle::~CDTCycle()
{

}

void CDTCycle::run()
{
    if (!m_network->isActived()) {
        QThread::msleep(2000);// 2s
    }

    if (!initConnection()) {
        return;
    }
    // 处理命令
    processCommand();

    auto bytes = m_network->readAll();
    if (!bytes.isEmpty()) {
        m_recvBuffer.append(bytes);
        //处理数据
        parseRecvData();
    }
    // 处理帧
    processFrame();

    if (m_settingData->m_stationType == eStationType::WF && !isRunYK) {
        ykAllNotAllow();
    }

}

void CDTCycle::processFrame()
{
    while (!m_frameQueue.isEmpty()) {
        CDTFrame frame = m_frameQueue.dequeue();

        //QByteArray ba = frame.toAllByteArray();

        switch (frame.frameControl.type)
        {
        // 0x61，遥测
        case eCDTFrameType::RmtMeasurement:
            //ShowMsgArray(eMsgType::eMsgRecv, "接收到遥测帧，正在处理...", ba, ba.size());
            yxResponse(frame.infoFields);
            break;

        // 0xF4,遥信
        case eCDTFrameType::RmtInformation:
            //ShowMsgArray(eMsgType::eMsgRecv, "接收到遥信帧，正在处理...", ba, ba.size());
            if (m_settingData->m_stationType == eStationType::WF) {
                // 五防接收到变位遥信
                if (isRunYK) {
                    changedYXResponse(frame.infoFields);
                } else {
                    yxResponse(frame.infoFields);

                }
            } else if (m_settingData->m_stationType == eStationType::Minitor) {
                // 监控接收虚遥信

            }
            break;

        case eCDTFrameType::RmtControlTypeCycle:
            ykResponse(frame);
            break;

        default :
            break;
        }
    }

}

void CDTCycle::changedYXResponse(QList<InfoFieldEntity> &infoFieldList)
{
    for (int idx = 0; idx < infoFieldList.count(); idx++) {
        //TODO: 获取当前遥信，进行比较
    }
}

void CDTCycle::ykResponse(CDTFrame &frame)
{
    // 解析报文，找解锁
    int allowIndex = -1;
    for (int idx = 0; idx < frame.infoFields.count(); idx++) {
        // 组合成一个四字节整数
        uint32_t combineNum = 0;
        for (int i = 0; i < 4; i++) {
            uint32_t convNum = frame.infoFields.at(idx).dataArray[i];
            combineNum |= convNum << i * 8;
        }
        // 提取里面是否有1的bit，有且只有一个
        auto positiveIdx = findPositive(combineNum);
        if (positiveIdx > -1) {
            allowIndex = idx * 32 + positiveIdx;
            break;
        }
    }

    // 闭锁或全闭锁
    if (allowIndex == -1) {
        return;
    }
    //TODO: 解锁：对应地址的di进行变位

}
// 全0返回-1，否则返回对应为1的位置
int CDTCycle::findPositive(uint32_t num)
{
    if (num > 0) {
        for (int i = 0; i < 32; i++) {
            if ((num >> i) & 0x01) {
                return i;
            }
        }
    }
    return -1;
}

void CDTCycle::ykNotAllow(int ptId)
{
    CDTFrame frame = createCycleYKFrame(false, ptId);
//    m_sendList.append(frame);
}

void CDTCycle::ykAllNotAllow()
{
    CDTFrame frame = createCycleYKFrame(true);
//    m_sendList.append(frame);

    //ShowMsgArray(eMsgType::eMsgSend, QString("发送遥控全闭锁命令"), frameBytes, frameBytes.size());
}

CDTFrame CDTCycle::createCycleYKFrame(bool isAllPoint, int ptId)
{
    CDTFrame cmdFrame;

    uint8_t infoFieldCount = 0;
    if (isAllPoint) {
        int doCount = 0;
        // TODO:获取Di数量
        //    for (const auto& dev : RtuObj->ListDev) {
        //        doCount += dev->ListDo.size();
        //    }
        infoFieldCount = qRound(static_cast<double>(doCount) / 32.0);
    }
    else {
        infoFieldCount = qRound(static_cast<double>(ptId) / 32.0);
    }

    // 0xF0-0xFF, 16
    uint8_t funCode = infoFieldCount < 16 ? 0xF0 : 0x80;
    // 设置控制字值
    cmdFrame.frameControl.fillData(eCDTFrameControlType::StandardType, 0xF1, infoFieldCount, 0, 0);
    // 填充空数据
    for (uint8_t i = 0; i < infoFieldCount; i++) {
        uint8_t datas[4] = {0, 0, 0, 0};

        InfoFieldEntity entity(funCode, datas);
        funCode++;
        cmdFrame.infoFields.append(entity);
    }
    return  cmdFrame;
}
