#include "cdtinteracte.h"
#include "interwfstrategy.h"
#include "intermintorstrategy.h"

CDTInteracte::CDTInteracte(const QSharedPointer<CommunicationBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

void CDTInteracte::initStrategy()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new InterWFStrategy(this, this);
    } else {
        m_strategy = new InterMintorStrategy(this, this);
    }
    connect(this, &ProtocolBase::sendYk, m_strategy, &StrategyBase::sendYK);
}

void CDTInteracte::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, ctrlCode, 0xFF, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控选择指令").arg(ptId).arg(ctrlCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
}

void CDTInteracte::ykSelectBack(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykAckCode, ctrlCode, 0xFF, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控选择回传"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控选择回传指令").arg(ptId).arg(ctrlCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("分")));
}

void CDTInteracte::ykExecute(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, ctrlCode, 0xFF, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控执行"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2操作遥控执行指令").arg(ptId).arg(ctrlCode == eControlLockCode::CloseValidLock ? QStringLiteral("合"):QStringLiteral("合")));
}

void CDTInteracte::ykExecuteBack(uint8_t ctrlCode, uint8_t ptId, bool success)
{
    // AA解锁，55闭锁
    uint8_t valid = success ? m_settingData->m_ptCfg->m_ykUnlock : m_settingData->m_ptCfg->m_ykLock;
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykExeCode, ctrlCode, valid, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("遥控执行"), frame.toAllByteArray());
    emit sendYKMsg(QStringLiteral("发送点%1的%2遥控变位指令").arg(ptId).arg(success ? QStringLiteral("允许"):QStringLiteral("禁止")));
}

CDTFrame CDTInteracte::interactYKFrame(uint8_t frameType, uint8_t funCode, uint8_t operCode, uint8_t vaild, int ptId)
{
    CDTFrame frame;

    InfoFieldEntity entity;
    entity.fillData(funCode, operCode, vaild, static_cast<uint8_t>(ptId & 0xFF), static_cast<uint8_t>(ptId >> 8 & 0xFF));
    frame.infoFields.append(entity);

    frame.frameControl.fillData(m_settingData->m_ptCfg->m_controlType, frameType, frame.infoFields.count(), 0, 0);
    return frame;
}


