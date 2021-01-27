#include "cdtexnr.h"
#include "nrwfstrategy.h"
#include "nrmintorstrategy.h"

CDTExNr::CDTExNr(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData)
    : CDTProtocol (network, settingData)
{

}

CDTExNr::~CDTExNr()
{

}

void CDTExNr::init()
{
    if (m_settingData->m_stationType == eStationType::WF) {
        m_strategy = new NrWFStrategy(this, this);
    } else {
        m_strategy = new NrMintorStrategy(this, this);
    }
}

