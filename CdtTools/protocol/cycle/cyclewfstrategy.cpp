#include "cyclewfstrategy.h"
#include "cdtcycle.h"

CycleWFStrategy::CycleWFStrategy(CDTCycle *cdt, QObject *parent)
    : m_cdt(cdt)
{
    setParent(parent);
}

CycleWFStrategy::~CycleWFStrategy()
{

}

void CycleWFStrategy::uploadTiming()
{
    if (!m_cdt->isRunYK()) {
        m_cdt->uploadUnlock();
    }
}

void CycleWFStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame)
}
