#ifndef NRWFSTRATEGY_H
#define NRWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"
#include <QTimer>

class CDTExNr;
class NrWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit NrWFStrategy(CDTExNr* cdt, QObject *parent = nullptr);
    ~NrWFStrategy() override;

    void ykResponse(CDTFrame &frame) override;
signals:

public slots:
    void onLockOrUnlock(bool locked) override;
    void sendYK(int ptId, bool offon) override;
    void onListenTimeout();
private:
    CDTExNr* m_cdt;
    QTimer m_timer;
    int m_listenPtId;
    bool m_oldStatus;
};

#endif // NRWFSTRATEGY_H
