#include "cdtcycle.h"
#include <QThread>

CDTCycle::CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData)
    : CDTProtocol (network, settingData)
{

}

CDTCycle::~CDTCycle()
{

}
