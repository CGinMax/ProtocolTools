#ifndef STRATEGYBASE_H
#define STRATEGYBASE_H

#include <QObject>

class CDTFrame;

class StrategyBase : public QObject
{
    Q_OBJECT
public:
    virtual ~StrategyBase();

    virtual void uploadTiming() = 0;

    virtual void ykResponse(CDTFrame& frame) = 0;

signals:

public slots:
};

#endif // STRATEGYBASE_H
