#ifndef INTERMINTORSTRATEGY_H
#define INTERMINTORSTRATEGY_H

#include "../standard/cdtmintorstrategy.h"

class CDTInteracte;

class InterMintorStrategy : public CDTMintorStrategy
{
    Q_OBJECT
public:
    explicit InterMintorStrategy(CDTInteracte* cdt, QObject *parent = nullptr);
    ~InterMintorStrategy() override;

    void ykResponse(CDTFrame &frame) override;


signals:

public slots:
    void sendYK(int ptId, bool offon) override;

private:
    CDTInteracte* m_cdt;
};

#endif // INTERMINTORSTRATEGY_H
