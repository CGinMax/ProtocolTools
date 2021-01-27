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

void UtWFStrategy::uploadTiming()
{

}

void UtWFStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    bool success = ctrlCode != 0xFF;
    // true合,false开
    bool status = ctrlCode == m_cdt->getPtCfg()->m_ykClose;
    int ykAddr = firstInfoData.dataArray[1];

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size())
        return ;

    if (funCode == m_cdt->getPtCfg()->m_ykReqCode) {
        // TODO
    }
}
