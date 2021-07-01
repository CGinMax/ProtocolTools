#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "portparam.h"
#include "ybprotocolchannel.h"

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(QObject *parent = nullptr);
    ~GatherController() override;

    CommunicationBase* rawCommunicationBase();

//    void appendSensorData(YBSensorData* data);
    Q_INVOKABLE bool startCommunication(QObject* param);
    Q_INVOKABLE bool stopCommunication();

    Q_INVOKABLE bool isConnected();
    YBProtocolChannel* protocol();

    Q_INVOKABLE void queryGatherVersion(int addr, int timeout = 12000);
    Q_INVOKABLE void configureGatherAddress(int addr, int timeout = 12000);
    Q_INVOKABLE void configureSensorCount(int addr, int count, int timeout);
signals:
    void startPortocolChannel();
    void stopProtocolChannel();
    void deleteItem();
    void queryVersionCallback(bool success, const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString());
    void configureAddressCallback(bool success, int addr = 0);
    void configureCountCallback(bool success, int count = 0);

public slots:
//    void onTitleChanged(const QString& title);

private:
    bool canDoOperate();
//    GatherController* setAddress(int addr);
//    GatherController* setHardwareVersion(const QString& version);
//    GatherController* setSoftwareVersion(const QString& version);
//    GatherController* setProductDesc(const QString& desc);
//    GatherController* setSensorCount(int count);
//    GatherController* setQueryVersionState(int state);
//    GatherController* setConfigureAddrState(int state);
//    GatherController* setSensorCountState(int state);

    QSharedPointer<CommunicationBase> _communication;
    QSharedPointer<ProtocolChannelBase> _protocol;

};

#endif // GATHERCONTROLLER_H
