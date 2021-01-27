#ifndef NRWFSTRATEGY_H
#define NRWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"

class CDTExNr;
class NrWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit NrWFStrategy(CDTExNr* cdt, QObject *parent = nullptr);
    ~NrWFStrategy() override;

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;
signals:

public slots:

private:
    CDTExNr* m_cdt;

};

#endif // NRWFSTRATEGY_H
