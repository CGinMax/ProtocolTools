#ifndef CYCLEWFSTRATEGY_H
#define CYCLEWFSTRATEGY_H

#include "../strategybase.h"
#include <QTimer>
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
    void sendYK(int ptId, bool offon) override;
    void onListenTimeout();

private:
    CDTCycle* m_cdt;
    int m_listenPtId;
    bool m_oldStatus;
    QTimer m_timer;
};

#endif // CYCLEWFSTRATEGY_H
