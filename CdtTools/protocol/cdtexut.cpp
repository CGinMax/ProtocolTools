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

    if (funCode == m_settingData->m_ptCfg->m_ykAckType) {
        // 遥控应答
        if (success) {
            auto di = m_settingData->m_ptCfg->findDiById(ykAddr);
            QString msg;
            if (di) {
                di->setValue(status);
                msg = QStringLiteral("变位成功");
            }
            else {
                msg = QStringLiteral("点号不存在");
            }
            emit ykExecuteFinish(msg);
        }
        else {
            // emit failed msg;
            showMessage(eMsgRecv, QStringLiteral("遥控解闭锁应答失败"));
        }
        m_isRunYK = false;
    }
    else if (funCode == m_settingData->m_ptCfg->m_ykReqType) {

    }

}

void CDTExUt::processFrame()
{
    while (!m_frameQueue.isEmpty()) {
        CDTFrame frame = m_frameQueue.dequeue();

        switch (frame.frameControl.type)
        {
        // 0x61，遥测
        case eCDTFrameType::RmtMeasurement:
            showMessageBuffer(eMsgType::eMsgRecv, "接收到遥测帧，正在处理...", frame.toAllByteArray());
            yxResponse(frame.infoFields);
            break;

            // 0xF4,遥信
        case eCDTFrameType::RmtInformation:
            if (m_settingData->m_stationType == eStationType::WF) {
                showMessageBuffer(eMsgType::eMsgRecv, "接收到遥信帧，正在处理...", frame.toAllByteArray());
                yxResponse(frame.infoFields);
            } else if (m_settingData->m_stationType == eStationType::Minitor) {
                // 监控接收虚遥信

            }
            break;

        case 0xD9:
            ykResponse(frame);
            break;

        default :
            break;
        }
    }

}

void CDTExUt::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    auto frame = interactYKFrame(eCDTFrameControlType::StandardType, m_settingData->m_ptCfg->m_ykReqType, 0xE9, ctrlCode, ptId);
    showMessageBuffer(eMsgType::eMsgSend, QStringLiteral("发送遥控命令"), frame.toAllByteArray());
    send(frame);
}

void CDTExUt::startYK(int ptId, bool offon)
{
    if (ptId > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    eControlLockCode code = offon ? eControlLockCode::CloseValidLock : eControlLockCode::OpenValidLock;

    ykSelect(code, static_cast<uint8_t>(ptId));
    m_isRunYK = true;
}
