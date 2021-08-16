#ifndef UTWFSTRATEGY_H
#define UTWFSTRATEGY_H

#include "../standard/cdtwfstrategy.h"

class CDTExUt;
class UtWFStrategy : public CDTWFStrategy
{
    Q_OBJECT
public:
    explicit UtWFStrategy(CDTExUt* cdt, QObject *parent = nullptr);
    ~UtWFStrategy() override;

    void ykResponse(CDTFrame &frame) override;

signals:

public slots:
    void sendYK(int ptId, bool offon) override;
private:
    CDTExUt* m_cdt;

};

#endif // UTWFSTRATEGY_H
