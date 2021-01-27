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

    }
}

void CDTWFStrategy::ykResponse(CDTFrame &frame)
{

}
