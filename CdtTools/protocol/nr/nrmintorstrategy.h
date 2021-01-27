#ifndef NRMINTORSTRATEGY_H
#define NRMINTORSTRATEGY_H

#include "../standard/cdtmintorstrategy.h"

class CDTExNr;
class NrMintorStrategy : public CDTMintorStrategy
{
    Q_OBJECT
public:
    explicit NrMintorStrategy(CDTExNr* cdt, QObject *parent = nullptr);
    ~NrMintorStrategy() override;

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;
signals:

public slots:

private:
    CDTExNr* m_cdt;

};

#endif // NRMINTORSTRATEGY_H
