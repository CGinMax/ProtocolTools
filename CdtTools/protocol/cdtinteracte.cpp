#include "cdtinteracte.h"

CDTInteracte::CDTInteracte(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

void CDTInteracte::ykResponse(CDTFrame &frame)
{
    if (frame.frameControl.type != 0xA8) {
        return ;
    }
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    // true开,false关
    bool status = ctrlCode == eControlLockCode::CloseValidLock;
    int ykAddr = firstInfoData.dataArray[2];
    ykAddr |= firstInfoData.dataArray[3] << 8;

    if (ykAddr > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    // 遥控执行
    showMessageBuffer(eMsgType::eMsgRecv, "接收到遥控帧，正在处理...", frame.toAllByteArray());
    switch (funCode) {
    case eCDTFunCode::RmtControlSelectCode:
    {
        if (!m_isRunYK) {// 接收到遥控选择
            // 直接返回校核
            ykSelectBack(ctrlCode, static_cast<uint8_t>(ykAddr));
            // 进入遥控执行状态
            m_isRunYK = true;
        }
        else {// 接收到遥控执行
            // 退出遥控执行状态
            m_isRunYK = false;
        }
        break;
    }
        // 监控发执行
    case eCDTFunCode::RmtControlBackCode:
    {
        ykExecute(ctrlCode, static_cast<uint8_t>(ykAddr));
        qDebug("send execute");
        // emit execute?
        break;
    }
        // 监控接收解闭锁应答
    case eCDTFunCode::RmtControlExecuteCode:
    {
        bool success = firstInfoData.dataArray[1] == 0xAA;
        if (success){
            (*m_settingData->m_ptCfg->m_globalDiList)[ykAddr - 1].setValue(status);
            emit ykExecuteFinish();
        }
        else {
            // emit failed msg;
            showMessage(eMsgRecv, QStringLiteral("遥控解闭锁应答失败"));
        }
        m_isRunYK = false;

        break;
    }

    default:
        break;
    }
}

void CDTInteracte::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(eCDTFunCode::RmtControlSelectCode, ctrlCode, 0xFF, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, "send", frame.toAllByteArray());
}

void CDTInteracte::ykSelectBack(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(eCDTFunCode::RmtControlBackCode, ctrlCode, 0xFF, ptId);
    send(frame);
}

void CDTInteracte::ykExecute(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(eCDTFunCode::RmtControlSelectCode, ctrlCode, 0xFF, ptId);
    send(frame);
}

void CDTInteracte::ykExecuteBack(uint8_t ctrlCode, uint8_t ptId, bool success)
{
    // AA解锁，55闭锁
    uint8_t valid = success ? 0xAA : 0x55;
    CDTFrame frame = interactYKFrame(eCDTFunCode::RmtControlExecuteCode, ctrlCode, valid, ptId);
    send(frame);
}

CDTFrame CDTInteracte::interactYKFrame(uint8_t funCode, uint8_t operCode, uint8_t vaild, int ptId)
{
    CDTFrame frame;

    InfoFieldEntity entity;
    entity.fillData(funCode, operCode, vaild, static_cast<uint8_t>(ptId & 0xFF), static_cast<uint8_t>(ptId >> 8 & 0xFF));
    frame.infoFields.append(entity);

    frame.frameControl.fillData(eCDTFrameControlType::StandardType, 0xA8, frame.infoFields.count(), 0, 0);
    return frame;
}

void CDTInteracte::startYK(int ptId, bool offon)
{
    if (ptId > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    eControlLockCode code = offon ? eControlLockCode::CloseValidLock : eControlLockCode::OpenValidLock;

    ykSelect(code, static_cast<uint8_t>(ptId));
    m_isRunYK = true;
}

void CDTInteracte::processFrame()
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

        case 0xA8:
            ykResponse(frame);
            break;

        default :
            break;
        }
    }

}

