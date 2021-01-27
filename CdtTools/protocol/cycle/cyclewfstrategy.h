#ifndef CYCLEWFSTRATEGY_H
#define CYCLEWFSTRATEGY_H

#include "../strategybase.h"

class CDTCycle;

class CycleWFStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit CycleWFStrategy(CDTCycle* cdt, QObject *parent = nullptr);
    ~CycleWFStrategy() override;
    void uploadTiming() override;

    void ykResponse(CDTFrame& frame) override;
signals:

public slots:

private:
    CDTCycle* m_cdt;
};

#endif // CYCLEWFSTRATEGY_H
