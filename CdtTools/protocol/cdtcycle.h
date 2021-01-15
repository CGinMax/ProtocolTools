#ifndef CDTCYCLE_H
#define CDTCYCLE_H

#include "cdtprotocol.h"

class CDTCycle : public CDTProtocol
{
    Q_OBJECT
public:
    CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTCycle() override;

};

#endif // CDTCYCLE_H
