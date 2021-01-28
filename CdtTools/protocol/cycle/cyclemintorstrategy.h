#ifndef CYCLEMINTORSTRATEGY_H
#define CYCLEMINTORSTRATEGY_H

#include "../standard/cdtmintorstrategy.h"

class CDTCycle;
class CycleMintorStrategy : public CDTMintorStrategy
{
    Q_OBJECT
public:
    explicit CycleMintorStrategy(CDTCycle* cdt, QObject *parent = nullptr);
    ~CycleMintorStrategy() override;

    void ykResponse(CDTFrame& frame) override;

    int findPositive(uint32_t num);
signals:

public slots:
    void sendYK(int ptId, bool offon) override;
private:
    CDTCycle* m_cdt;
};

#endif // CYCLEMINTORSTRATEGY_H
