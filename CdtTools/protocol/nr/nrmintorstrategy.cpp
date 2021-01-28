#include "nrmintorstrategy.h"
#include "cdtexnr.h"

NrMintorStrategy::NrMintorStrategy(CDTExNr *cdt, QObject *parent)
    : CDTMintorStrategy (cdt, parent)
    , m_cdt(cdt)
{

}

NrMintorStrategy::~NrMintorStrategy()
{

}

void NrMintorStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    int ykAddr = firstInfoData.dataArray[1];
    ykAddr = (ykAddr << 8) | firstInfoData.dataArray[0];

    if (ykAddr == 0xFFFF) {
        emit m_cdt->sendYKMsg(QStringLiteral("接收到遥控全闭锁指令，进入遥控状态"));
        return;
    }

    if (ykAddr == 0xFFFE) {
        emit m_cdt->sendYKMsg(QStringLiteral("接收到遥控全解锁指令，退出遥控状态"));
        m_cdt->setRunYK(false);
        return ;
    }

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size()) {
        emit m_cdt->sendYKMsg(QStringLiteral("接收遥控请求错误，遥信点Id=%1不存在").arg(ykAddr));
        return ;
    }

    if (!m_cdt->isRunYK()) {
        m_cdt->setRunYK(true);
        emit m_cdt->notifyYK(ykAddr);
        emit m_cdt->sendYKMsg(QStringLiteral("接收到遥控单点闭锁指令"));
    }
}
