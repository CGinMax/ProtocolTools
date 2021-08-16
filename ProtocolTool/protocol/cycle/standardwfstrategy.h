#ifndef STANDARDWFSTRATEGY_H
#define STANDARDWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"
#include <QTimer>
class CDTStandard;

class StandardWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit StandardWFStrategy(CDTStandard* cdt, QObject *parent = nullptr);
    ~StandardWFStrategy() override;
    void uploadTiming() override;

    void ykResponse(CDTFrame& frame) override;
signals:

public slots:
    // add 闭锁
    void sendYK(int ptId, bool offon) override;
    void onListenTimeout();

private:
    CDTStandard* m_cdt;
    int m_listenPtId;
    bool m_oldStatus;
    QTimer m_timer;
};

#endif // CYCLEWFSTRATEGY_H
