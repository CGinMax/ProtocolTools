#ifndef NRUDPWFSTRATEGY_H
#define NRUDPWFSTRATEGY_H

#include "../strategybase.h"
class NrUdpProtocol;

class NrUdpWFStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit NrUdpWFStrategy(NrUdpProtocol* nrudp);

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;
    void ykResponse(QByteArray &infoData) override;
signals:

public slots:
    void onLockOrUnlock(bool locked) override;
    void sendYK(int ptId, bool offon) override;

private:
    NrUdpProtocol* m_nrudp;
};

#endif // NRUDPWFSTRATEGY_H
