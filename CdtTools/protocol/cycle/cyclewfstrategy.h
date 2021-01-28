#ifndef CYCLEWFSTRATEGY_H
#define CYCLEWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"
#include <QTimer>
class CDTCycle;

class CycleWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit CycleWFStrategy(CDTCycle* cdt, QObject *parent = nullptr);
    ~CycleWFStrategy() override;
    void uploadTiming() override;

    void ykResponse(CDTFrame& frame) override;
signals:

public slots:
    // add 闭锁
    void sendYK(int ptId, bool offon) override;
    void onListenTimeout();

private:
    CDTCycle* m_cdt;
    int m_listenPtId;
    bool m_oldStatus;
    QTimer m_timer;
};

#endif // CYCLEWFSTRATEGY_H
