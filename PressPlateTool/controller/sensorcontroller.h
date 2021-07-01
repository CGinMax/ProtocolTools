#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include "gathercontroller.h"

class SensorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GatherController* gatherController READ gatherController WRITE setGatherController)
public:
    explicit SensorController(QObject *parent = nullptr);

    Q_INVOKABLE void setGatherController(GatherController* controller);
    Q_INVOKABLE GatherController* gatherController();

    Q_INVOKABLE bool isConnected();

    Q_INVOKABLE void querySensorVersion(int addr, int timeout = 12000);
    Q_INVOKABLE void querySensorStatus(int addr, int timeout);
    Q_INVOKABLE void configureSensorAddress(int addr, int timeout = 12000);
    Q_INVOKABLE void configureSensorStatus(int addr, int status, int timeout = 12000);

signals:

public slots:

private:
    bool canDoOperate();
    // no delete
    GatherController* _controller;
};

#endif // SENSORCONTROLLER_H
