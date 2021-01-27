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

void NrWFStrategy::uploadTiming()
{

}

void NrWFStrategy::ykResponse(CDTFrame &frame)
{

}
