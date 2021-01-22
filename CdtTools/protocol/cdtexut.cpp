#include "cdtexut.h"

CDTExUt::CDTExUt(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExUt::~CDTExUt()
{

}

void CDTExUt::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    bool success = ctrlCode != 0xFF;
    // true合,false开
    bool status = ctrlCode == m_settingData->m_ptCfg->m_ykClose;
    int ykAddr = firstInfoData.dataArray[1];

    if (ykAddr > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    if (funCode == m_settingData->m_ptCfg->m_ykAckCode) {
        // 遥控应答
        if (success) {
            emit sendYKMsg(QStringLiteral("接收到请求应答，允许点%1遥控变位操作").arg(ykAddr));
            auto di = m_settingData->m_ptCfg->findDiById(ykAddr);
            QString msg;
            if (di) {
                di->setValue(status);
                msg = QStringLiteral("变位成功");
            }
            else {
                msg = QStringLiteral("变位失败，遥信点Id=%1错误").arg(ykAddr);
            }
            emit sendYKMsg(msg);
        }
        else {
            emit sendYKMsg(QStringLiteral("接收到请求应答，禁止点%1遥控变位操作").arg(ykAddr));
        }
        m_isRunYK = false;
    }
    else if (funCode == m_settingData->m_ptCfg->m_ykReqCode) {
        // TODO
    }

}

void CDTExUt::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    auto frame = interactYKFrame(eCDTFrameControlType::ExternType, m_settingData->m_ptCfg->m_ykReqType, 0xE9, ctrlCode, ptId);
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
