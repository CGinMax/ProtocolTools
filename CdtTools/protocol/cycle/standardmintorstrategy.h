#ifndef STANDARDMINTORSTRATEGY_H
#define STANDARDMINTORSTRATEGY_H

#include "../standard/cdtmintorstrategy.h"

class CDTStandard;
class StandardMintorStrategy : public CDTMintorStrategy
{
    Q_OBJECT
public:
    explicit StandardMintorStrategy(CDTStandard* cdt, QObject *parent = nullptr);
    ~StandardMintorStrategy() override;

    void ykResponse(CDTFrame& frame) override;

    int findPositive(uint32_t num);
signals:

public slots:
    void sendYK(int ptId, bool offon) override;
private:
    CDTStandard* m_cdt;
};

#endif // CYCLEMINTORSTRATEGY_H
