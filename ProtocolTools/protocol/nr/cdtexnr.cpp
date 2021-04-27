#include "cdtexnr.h"
#include "nrwfstrategy.h"
#include "nrmintorstrategy.h"

CDTExNr::CDTExNr(const QSharedPointer<CommunicationBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExNr::~CDTExNr()
{

}

void CDTExNr::initStrategy()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new NrWFStrategy(this, this);
    } else {
        m_strategy = new NrMintorStrategy(this, this);
    }
    connect(this, &ProtocolBase::lockOrUnlock, m_strategy, &StrategyBase::onLockOrUnlock);
    connect(this, &ProtocolBase::sendYk, m_strategy, &StrategyBase::sendYK);
}

void CDTExNr::ykAllLock(int ptNo)
{
    CDTFrame frame = YKFrame(0x00, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送全部闭锁遥控"), frame.toAllByteArray());
    for (int i = 0; i < 3; i++) {
        send(frame);
    }
    emit sendYKMsg(QStringLiteral("发送遥控全闭锁指令"));
}

void CDTExNr::ykExecute(int ptNo)
{
    auto funcode = static_cast<uint8_t>(ptNo / 32);
    CDTFrame frame = YKFrame(funcode, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送单步遥控"), frame.toAllByteArray());
    for (int i = 0; i < 3; i++) {
        send(frame);
    }
    emit sendYKMsg(QStringLiteral("发送点%1单步遥控指令").arg(ptNo));

}

void CDTExNr::ykAllUnlock(int ptNo)
{
    CDTFrame frame = YKFrame(0x00, ptNo);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送全部解锁遥控"), frame.toAllByteArray());
    for (int i = 0; i < 3; i++) {
        send(frame);
    }
    emit sendYKMsg(QStringLiteral("发送遥控全解锁指令"));
}

CDTFrame CDTExNr::YKFrame(uint8_t funcode, int ptNo)
{
    auto ptLow = static_cast<uint8_t>(ptNo);
    auto ptHigh = static_cast<uint8_t>(ptNo >> 8);

    InfoFieldEntity entity;
    entity.fillData(funcode, ptLow, ptHigh, 0xFF, 0xFF);
    CDTFrame frame;
    frame.infoFields.append(entity);
    frame.frameControl.fillData(0xF1, m_settingData->m_ptCfg->m_ykReqType, frame.infoFields.count(), 0x00, 0x00);
    return frame;
}

