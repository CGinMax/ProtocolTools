#include "utwfstrategy.h"
#include "cdtexut.h"

UtWFStrategy::UtWFStrategy(CDTExUt *cdt, QObject *parent)
    : CDTWFStrategy (cdt, parent)
    , m_cdt(cdt)
{

}

UtWFStrategy::~UtWFStrategy()
{

}

void UtWFStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    // true合,false开
    bool status = ctrlCode == m_cdt->getPtCfg()->m_ykClose;
    int ykAddr = firstInfoData.dataArray[1];

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size())
        return ;

    if (funCode == m_cdt->getPtCfg()->m_ykReqCode) {
        emit m_cdt->sendYKMsg(QStringLiteral("接收到请求五防解锁，点%1遥控%2操作").arg(ykAddr).arg(status ? QStringLiteral("分->合") : QStringLiteral("合->分")));
        m_cdt->setRunYK(true);
        emit m_cdt->notifyYK(ykAddr);
    }
}

void UtWFStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(ptId)
    Q_UNUSED(offon)
}
