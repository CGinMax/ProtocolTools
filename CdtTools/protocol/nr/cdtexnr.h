#ifndef CDTEXNR_H
#define CDTEXNR_H

#include "../standard/cdtprotocol.h"

class CDTExNr : public CDTProtocol
{
    Q_OBJECT
public:
    explicit CDTExNr(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTExNr() override;

    void init() override;
signals:

public slots:
};

#endif // CDTEXNR_H
