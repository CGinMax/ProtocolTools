#ifndef CDTEXUT_H
#define CDTEXUT_H

#include "../standard/cdtprotocol.h"

class CDTExUt : public CDTProtocol
{
    Q_OBJECT
public:
    explicit CDTExUt(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTExUt() override;

    void init() override;

    void ykSelect(uint8_t ctrlCode, uint8_t ptId);

signals:

public slots:
    void startYK(int ptId, bool offon) override;

};

#endif // CDTEXUT_H
