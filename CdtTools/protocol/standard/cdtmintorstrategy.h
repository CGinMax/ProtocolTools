#ifndef CDTMINTORSTRATEGY_H
#define CDTMINTORSTRATEGY_H

#include "../strategybase.h"

class CDTProtocol;

class CDTMintorStrategy : public StrategyBase
{
    Q_OBJECT
public:
    explicit CDTMintorStrategy(CDTProtocol* cdt, QObject *parent = nullptr);
    ~CDTMintorStrategy() override;

    void uploadTiming() override;

    void ykResponse(CDTFrame& frame) override;

    int findPositive(uint32_t num);
private:
    CDTProtocol* m_cdt;
};

#endif // CDTMINTORSTRATEGY_H
