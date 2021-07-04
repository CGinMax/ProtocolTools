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

    Q_INVOKABLE void querySensorVersion(int index, int addr, int timeout = 12000);
    Q_INVOKABLE void querySensorStatus(int index, int addr, int timeout);
    Q_INVOKABLE void configureSensorAddress(int index, int addr, int timeout = 12000);
    Q_INVOKABLE void configureSensorStatus(int index, int addr, int status, int timeout = 12000);

signals:
    void queryVersionCallback(bool success, int index = 0, const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString());
    void configureAddressCallback(bool success, int index = 0, int addr = 0);
    void queryStateCallback(bool success, int index = 0, int curState = 0xFF, int confState = 0xFF);
    void configureStateCallback(bool success, int index = 0, int state = 0xFF);

public slots:

private:
    bool canDoOperate();
    // no delete
    GatherController* _controller;
};

#endif // SENSORCONTROLLER_H
