#include "cdtexnr.h"

CDTExNr::CDTExNr(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExNr::~CDTExNr()
{

}

void CDTExNr::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    int ykAddr = firstInfoData.dataArray[1];
    ykAddr = (ykAddr << 8) | firstInfoData.dataArray[0];

    if (ykAddr == 0xFFFF) {
        emit sendYKMsg(QStringLiteral("接收到遥控全闭锁指令，进入遥控状态"));
        return;
    }

    if (ykAddr == 0xFFFE) {
        emit sendYKMsg(QStringLiteral("接收到遥控全解锁指令，退出遥控状态"));
        m_isRunYK = false;
        return ;
    }

    if (ykAddr > m_settingData->m_ptCfg->m_globalDiList->size()) {
        emit sendYKMsg(QStringLiteral("接收遥控请求错误，遥信点Id=%1不存在").arg(ykAddr));
        return ;
    }

    if (!m_isRunYK) {
        m_isRunYK = true;
        emit notifyYK(ykAddr);
        emit sendYKMsg(QStringLiteral("接收到遥控单点闭锁指令"));
    }
}
