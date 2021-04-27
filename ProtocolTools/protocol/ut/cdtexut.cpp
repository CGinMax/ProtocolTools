#include "cdtexut.h"
#include "utwfstrategy.h"
#include "utmintorstrategy.h"

CDTExUt::CDTExUt(const QSharedPointer<CommunicationBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExUt::~CDTExUt()
{

}

void CDTExUt::initStrategy()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new UtWFStrategy(this, this);
    } else {
        m_strategy = new UtMintorStrategy(this, this);
    }
    connect(this, &ProtocolBase::sendYk, m_strategy, &StrategyBase::sendYK);
}

void CDTExUt::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    auto frame = CDTFrame::createYKFrame(eCDTFrameControlType::ExternType, m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, ctrlCode, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控请求解锁命令"), frame.toAllByteArray());
    send(frame);
    emit sendYKMsg(QStringLiteral("发送点%1的请求解锁指令").arg(ptId));
}

void CDTExUt::ykSelectBack(uint8_t ctrlCode, uint8_t ptId)
{
    auto frame = CDTFrame::createYKFrame(eCDTFrameControlType::ExternType, m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykAckCode, ctrlCode, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控解锁应答命令"), frame.toAllByteArray());
    send(frame);
    emit sendYKMsg(QStringLiteral("发送点%1的解锁应答指令").arg(ptId));
}

void CDTExUt::onReverseYx(int ptId, bool allow)
{
    auto di = m_settingData->m_ptCfg->findDiById(ptId);
    auto changeMsg = di->value() ? QStringLiteral("合->分") : QStringLiteral("分->合");

    QString msg = allow ? QStringLiteral("允许点%1发生遥控%2操作") : QStringLiteral("禁止点%1发生遥控%2操作");
    eControlLockCode code = allow ? (di->value() ? eControlLockCode::OpenValidLock : eControlLockCode::CloseValidLock) : eControlLockCode::ControlError;

    ykSelectBack(code, ptId);
    emit sendYKMsg(msg.arg(ptId).arg(changeMsg));

    m_isRunYK = false;
}
