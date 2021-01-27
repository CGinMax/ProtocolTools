#include "cdtexut.h"
#include "utwfstrategy.h"
#include "utmintorstrategy.h"

CDTExUt::CDTExUt(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExUt::~CDTExUt()
{

}

void CDTExUt::init()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new UtWFStrategy(this, this);
    } else {
        m_strategy = new UtMintorStrategy(this, this);
    }
}

void CDTExUt::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    auto frame = YKFrame(eCDTFrameControlType::ExternType, m_settingData->m_ptCfg->m_ykReqType, 0xE9, ctrlCode, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控命令"), frame.toAllByteArray());
    send(frame);
    emit sendYKMsg(QStringLiteral("发送点%1的请求解锁指令").arg(ptId));
}

void CDTExUt::startYK(int ptId, bool offon)
{
    if (ptId > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    eControlLockCode code = offon ? eControlLockCode::CloseValidLock : eControlLockCode::OpenValidLock;

    ykSelect(code, static_cast<uint8_t>(ptId));
    m_isRunYK = true;
}
