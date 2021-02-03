#ifndef NRUDPMINTORSTRATEGY_H
#define NRUDPMINTORSTRATEGY_H

#include "../strategybase.h"

class NrUdpProtocol;

class NrUdpMintorStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit NrUdpMintorStrategy(NrUdpProtocol *nrudp);

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;
    void ykResponse(QByteArray &infoData) override;
signals:

public slots:    
    void onLockOrUnlock(bool locked) override;
    void sendYK(int ptId, bool offon) override;

private:
    NrUdpProtocol* m_nrudp;
    int m_oldPtId;
};

#endif // NRUDPMINTORSTRATEGY_H
