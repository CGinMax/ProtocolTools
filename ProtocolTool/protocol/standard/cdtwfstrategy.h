#ifndef CDTWFSTRATEGY_H
#define CDTWFSTRATEGY_H

#include "../strategybase.h"
class CDTProtocol;

class CDTWFStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit CDTWFStrategy(CDTProtocol* cdt, QObject *parent = nullptr);
    ~CDTWFStrategy() override;

    void uploadTiming() override;
    void ykResponse(CDTFrame& frame) override;
    void ykResponse(QByteArray& infoData) override;

signals:

public slots:
    void onLockOrUnlock(bool locked) override;
    void sendYK(int ptId, bool offon) override;
private:
    CDTProtocol* m_cdt;
};

#endif // CDTWFSTRATEGY_H
