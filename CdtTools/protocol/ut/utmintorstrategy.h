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

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;
signals:

public slots:

private:
    CDTExUt* m_cdt;

};

#endif // UTMINTORSTRATEGY_H
