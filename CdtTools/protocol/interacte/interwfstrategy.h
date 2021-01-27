#ifndef INTERWFSTRATEGY_H
#define INTERWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"

class CDTInteracte;

class InterWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit InterWFStrategy(CDTInteracte* cdt, QObject *parent = nullptr);
    ~InterWFStrategy() override;

    void uploadTiming() override;
    void ykResponse(CDTFrame &frame) override;

signals:

public slots:

private:
    CDTInteracte* m_cdt;
};

#endif // INTERWFSTRATEGY_H
