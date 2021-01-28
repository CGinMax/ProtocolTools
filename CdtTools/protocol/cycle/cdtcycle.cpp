#include "cdtcycle.h"
#include "cyclewfstrategy.h"
#include "cyclemintorstrategy.h"

CDTCycle::CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData)
    : CDTProtocol (network, settingData)
    , m_cycleTime(2000)// 2s
    , m_cycleTimer(0)
{

}

CDTCycle::~CDTCycle()
{

}

void CDTCycle::init()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new CycleWFStrategy(this, this);
    } else {
        m_strategy = new CycleMintorStrategy(this, this);
    }
}

void CDTCycle::ykUnlock(int ptId)
{
    CDTFrame frame = createCycleYKFrame(false, ptId);
    int offset = m_settingData->m_ptCfg->m_globalDiList->first()->io();
    int actualIdx = ptId - offset;
    int infoIdx = actualIdx / 8;
    int infoOffset = actualIdx % 8;
    uint8_t postiveNum = 1 << infoOffset;
    frame.infoFields[infoIdx / 4].dataArray[infoIdx % 4] |= postiveNum;

    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控单点解锁命令"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的遥控单点解锁指令").arg(ptId));
    send(frame);
}

void CDTCycle::yKLock(int ptId)
{
    CDTFrame frame = createCycleYKFrame(false, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控闭锁命令"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的遥控闭锁指令").arg(ptId));
    send(frame);
}

void CDTCycle::yKAllLock()
{
    CDTFrame frame = createCycleYKFrame(true);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控全闭锁命令"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送遥控全闭锁指令"));
    send(frame);
}

CDTFrame CDTCycle::createCycleYKFrame(bool isAllPoint, int ptId)
{
    CDTFrame cmdFrame;
    int offset = m_settingData->m_ptCfg->m_globalDiList->first()->io();

    uint8_t infoFieldCount = 0;
    if (isAllPoint) {
        int doCount = m_settingData->m_ptCfg->m_globalDiList->size();
        infoFieldCount = qRound(static_cast<double>(doCount) / 32.0);
    }
    else {
        infoFieldCount = qRound(static_cast<double>(ptId - offset) / 32.0);
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

void CDTCycle::onTimeout()
{
    m_cycleTimer += 100;
    CDTProtocol::onTimeout();
}
void CDTCycle::uploadLock()
{
    if (m_cycleTimer > m_cycleTime) {
        yKAllLock();
        m_cycleTimer = 0;
    }
}

