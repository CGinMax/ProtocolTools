#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "portparam.h"
#include "gatherdata.h"
#include "ybprotocolchannel.h"

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(QObject *parent = nullptr);
    ~GatherController() override;

    CommunicationBase* rawCommunicationBase();

    Q_INVOKABLE bool startCommunication(const QVariantMap& portMap);
    Q_INVOKABLE bool stopCommunication();

    Q_INVOKABLE bool isConnected();
    YBProtocolChannel* protocol();

    Q_INVOKABLE void queryGatherVersion(int addr);
    Q_INVOKABLE void configureGatherAddress(int addr);
    Q_INVOKABLE void configureSensorCount(int addr, int count);
signals:
    void startPortocolChannel();
    void stopProtocolChannel();
    void queryVersionCallback(bool success, const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString());
    void configureAddressCallback(bool success, int addr = 0);
    void configureCountCallback(bool success, int count = 0);

public slots:

private:
    bool canDoOperate();
    QSharedPointer<GatherData> _gatherData;
    QSharedPointer<CommunicationBase> _communication;
    QSharedPointer<ProtocolChannelBase> _protocol;

};

#endif // GATHERCONTROLLER_H
