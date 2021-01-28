#include "cdtwfstrategy.h"
#include "cdtprotocol.h"

CDTWFStrategy::CDTWFStrategy(CDTProtocol *cdt, QObject *parent)
    : m_cdt(cdt)
{
    setParent(parent);
}

CDTWFStrategy::~CDTWFStrategy()
{

}

void CDTWFStrategy::uploadTiming()
{
    if (!m_cdt->isRunYK()) {
        m_cdt->sendVirtualYX();
    }
}

void CDTWFStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    bool success = ctrlCode != 0xFF;


    int ykAddr = firstInfoData.dataArray[2];

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size()) {
        qInfo("未找到对应点号");
        return ;
    }

    if (!success) {
        // TODO 禁止操作处理
        return ;
    }

    if (funCode == m_cdt->getPtCfg()->m_ykAckCode) {
        m_cdt->yKExecute(m_cdt->getPtCfg()->m_ykUnlock, ykAddr);
    }
}

void CDTWFStrategy::sendYK(int ptId, bool offon)
{
    if (ptId > m_cdt->getPtCfg()->m_globalDiList->last()->io()) {
        return ;
    }
    uint8_t code = offon ? m_cdt->getPtCfg()->m_ykClose : m_cdt->getPtCfg()->m_ykOpen;
    m_cdt->setRunYK(true);
    m_cdt->ykSelect(code, ptId);
}
