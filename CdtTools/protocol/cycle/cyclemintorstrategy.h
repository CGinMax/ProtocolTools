#ifndef CYCLEMINTORSTRATEGY_H
#define CYCLEMINTORSTRATEGY_H

#include "../strategybase.h"

class CDTCycle;
class CycleMintorStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit CycleMintorStrategy(CDTCycle* cdt, QObject *parent = nullptr);
    ~CycleMintorStrategy() override;

    void uploadTiming() override;

    void ykResponse(CDTFrame& frame) override;

    int findPositive(uint32_t num);
signals:

public slots:
private:
    CDTCycle* m_cdt;
};

#endif // CYCLEMINTORSTRATEGY_H
