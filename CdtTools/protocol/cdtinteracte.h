#ifndef CDTINTERACTE_H
#define CDTINTERACTE_H

#include "cdtprotocol.h"

class CDTInteracte : public CDTProtocol
{
    Q_OBJECT
public:
    CDTInteracte(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
};

#endif // CDTINTERACTE_H
