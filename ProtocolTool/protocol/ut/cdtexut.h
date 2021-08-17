#ifndef CDTEXUT_H
#define CDTEXUT_H

#include "../standard/cdtprotocol.h"

class CDTExUt : public CDTProtocol
{
    Q_OBJECT
public:
    explicit CDTExUt(const QSharedPointer<CommunicationBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTExUt() override;

    void initStrategy() override;

    void ykSelect(uint8_t ctrlCode, uint8_t ptId);
    void ykSelectBack(uint8_t ctrlCode, uint8_t ptId);
signals:

public slots:
    void onReverseYx(int ptId, bool allow) override;
};

#endif // CDTEXUT_H
