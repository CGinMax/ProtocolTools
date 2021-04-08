#include "cdtmintorstrategy.h"
#include "cdtprotocol.h"

CDTMintorStrategy::CDTMintorStrategy(CDTProtocol *cdt, QObject *parent)
    : m_cdt(cdt)
{
    setParent(parent);
}

CDTMintorStrategy::~CDTMintorStrategy()
{

}

void CDTMintorStrategy::uploadTiming()
{
    if (!m_cdt->isRunYK()) {
        m_cdt->uploadDi();
        m_cdt->uploadAi();
    }
}

void CDTMintorStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];

    bool status = ctrlCode == m_cdt->getPtCfg()->m_ykClose;
    int ykAddr = firstInfoData.dataArray[2];

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size()) {
        qInfo("未找到对应点号");
        return ;
    }

    if (funCode == m_cdt->getPtCfg()->m_ykReqCode) {
        m_cdt->setRunYK(true);
        m_cdt->ykSelectBack(ctrlCode, ykAddr);
    } else if (funCode == m_cdt->getPtCfg()->m_ykExeCode) {
        emit m_cdt->notifyYK(ykAddr);
        emit m_cdt->sendYKMsg(QStringLiteral("接收到点%1遥控%2执行请求").arg(ykAddr).arg(status ? QStringLiteral("分->合") : QStringLiteral("合->分")));
    }
}

void CDTMintorStrategy::ykResponse(QByteArray &infoData)
{
    Q_UNUSED(infoData)
}

void CDTMintorStrategy::onLockOrUnlock(bool locked)
{
    Q_UNUSED(locked)
}

void CDTMintorStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(ptId);
    Q_UNUSED(offon);
}
