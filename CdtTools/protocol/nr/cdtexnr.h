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

    void ykAllLock(int ptNo);

    void ykExecute(int ptNo);

    void ykAllUnlock(int ptNo);


    CDTFrame YKFrame(uint8_t funcode, int ptNo);
signals:

public slots:
};

#endif // CDTEXNR_H
