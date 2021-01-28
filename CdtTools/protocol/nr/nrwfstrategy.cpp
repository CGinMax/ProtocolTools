#include "nrwfstrategy.h"
#include "cdtexnr.h"

NrWFStrategy::NrWFStrategy(CDTExNr *cdt, QObject *parent)
    : CDTWFStrategy (cdt, parent)
    , m_cdt(cdt)
{

}

NrWFStrategy::~NrWFStrategy()
{

}

void NrWFStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame);
}

void NrWFStrategy::sendYK(int ptId, bool offon)
{
    if (ptId > m_cdt->getPtCfg()->m_globalDiList->last()->io()) {
        return ;
    }

    if (!m_cdt->isRunYK()) {
        m_cdt->ykAllLock(0xFFFF);
        m_cdt->setRunYK(true);
        return ;
    }

    m_cdt->ykExecute(ptId);

}
