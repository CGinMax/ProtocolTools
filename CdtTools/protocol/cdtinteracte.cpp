#include "cdtinteracte.h"

CDTInteracte::CDTInteracte(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

void CDTInteracte::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    // true合,false开
    bool status = ctrlCode == m_settingData->m_ptCfg->m_ykClose;
    int ykAddr = firstInfoData.dataArray[2];
    ykAddr |= firstInfoData.dataArray[3] << 8;

    if (ykAddr > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    // 遥控执行
    showMessageBuffer(eMsgType::eMsgRecv, "接收到遥控帧，正在处理...", frame.toAllByteArray());
    if (funCode == m_settingData->m_ptCfg->m_ykReqCode) {
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
    }
    else if (funCode == m_settingData->m_ptCfg->m_ykAckCode) {
        ykExecute(ctrlCode, static_cast<uint8_t>(ykAddr));
        qDebug("send execute");
        // emit execute?
    }
    else if (funCode == m_settingData->m_ptCfg->m_ykExeCode) {
        bool success = firstInfoData.dataArray[1] == m_settingData->m_ptCfg->m_ykUnlock;
        if (success){
            auto di = m_settingData->m_ptCfg->findDiById(ykAddr);
            QString msg;
            if (!di) {
                di->setValue(status);
                msg = QStringLiteral("变位成功");
            }
            else {
                msg = QStringLiteral("点错误");
            }
            emit ykExecuteFinish(msg);
        }
        else {
            // emit failed msg;
            showMessage(eMsgRecv, QStringLiteral("遥控解闭锁应答失败"));
        }
        m_isRunYK = false;

    }

}

void CDTInteracte::ykSelect(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, ctrlCode, 0xFF, ptId);
    send(frame);
    showMessageBuffer(eMsgType::eMsgSend, "send", frame.toAllByteArray());
}

void CDTInteracte::ykSelectBack(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykAckCode, ctrlCode, 0xFF, ptId);
    send(frame);
}

void CDTInteracte::ykExecute(uint8_t ctrlCode, uint8_t ptId)
{
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykReqType, m_settingData->m_ptCfg->m_ykReqCode, ctrlCode, 0xFF, ptId);
    send(frame);
}

void CDTInteracte::ykExecuteBack(uint8_t ctrlCode, uint8_t ptId, bool success)
{
    // AA解锁，55闭锁
    uint8_t valid = success ? m_settingData->m_ptCfg->m_ykUnlock : m_settingData->m_ptCfg->m_ykLock;
    CDTFrame frame = interactYKFrame(m_settingData->m_ptCfg->m_ykAckType, m_settingData->m_ptCfg->m_ykExeCode, ctrlCode, valid, ptId);
    send(frame);
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

void CDTInteracte::startYK(int ptId, bool offon)
{
    if (ptId > m_settingData->m_ptCfg->m_globalDiList->size())
        return ;

    uint8_t code = offon ? m_settingData->m_ptCfg->m_ykClose : m_settingData->m_ptCfg->m_ykOpen;

    ykSelect(code, static_cast<uint8_t>(ptId));
    m_isRunYK = true;
}


