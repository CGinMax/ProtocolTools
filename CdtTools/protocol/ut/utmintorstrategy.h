#ifndef UTMINTORSTRATEGY_H
#define UTMINTORSTRATEGY_H

#include "../standard/cdtmintorstrategy.h"

class CDTExUt;

class UtMintorStrategy : public CDTMintorStrategy
{
    Q_OBJECT
public:
    explicit UtMintorStrategy(CDTExUt* cdt, QObject *parent = nullptr);
    ~UtMintorStrategy() override;

    void ykResponse(CDTFrame &frame) override;
signals:

public slots:
    void sendYK(int ptId, bool offon) override;

private:
    CDTExUt* m_cdt;

};

#endif // UTMINTORSTRATEGY_H
