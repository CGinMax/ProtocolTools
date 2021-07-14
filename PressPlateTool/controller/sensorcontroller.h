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

    Q_INVOKABLE void querySensorVersion(int addr, int timeout);
    Q_INVOKABLE void querySensorStatus(int addr, int timeout);
    Q_INVOKABLE void configureSensorAddress(int addr, int timeout);
    Q_INVOKABLE void configureSensorStatus(int addr, int status, int timeout);

signals:
    void queryVersionCallback(const QVariantMap& result/*bool success, const QString& errorMsg = QString(),  const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString()*/);
    void configureAddressCallback(const QVariantMap& result/*bool success, const QString& errorMsg = QString(), int addr = 0*/);
    void queryStateCallback(const QVariantMap& result/*bool success, const QString& errorMsg = QString(), int curState = 0xFF, int confState = 0xFF*/);
    void configureStateCallback(const QVariantMap& result/*bool success, const QString& errorMsg = QString(), int state = 0xFF*/);

public slots:

private:
    // no delete
    GatherController* _controller;
};

#endif // SENSORCONTROLLER_H
