#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "gatherdata.h"
#include "ybprotocolchannel.h"

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(const QSharedPointer<GatherData>& data, QObject *parent = nullptr);
    ~GatherController() override;

    GatherData* rawGatherData();
    void setGatherData(const QSharedPointer<GatherData>& gatherData);

    CommunicationBase* rawCommunicationBase();

    void appendSensorData(YBSensorData* data);

    Q_INVOKABLE bool startCommunication();
    Q_INVOKABLE bool stopCommunication();

    bool isConnected();
    YBProtocolChannel* protocol();

    void queryGatherVersion();
    void configureGatherAddress(int addr);
    void configureSensorCount(int count);
signals:
    void startPortocolChannel();
    void stopProtocolChannel();
    void deleteItem();
    void updateData();

public slots:
    void onTitleChanged(const QString& title);

private:
    bool canDoOperate();
    GatherController* setAddress(int addr);
    GatherController* setHardwareVersion(const QString& version);
    GatherController* setSoftwareVersion(const QString& version);
    GatherController* setProductDesc(const QString& desc);
    GatherController* setSensorCount(int count);
    GatherController* setQueryVersionState(int state);
    GatherController* setConfigureAddrState(int state);
    GatherController* setSensorCountState(int state);

    QSharedPointer<GatherData> _gatherData;

    QSharedPointer<CommunicationBase> _communication;
    QSharedPointer<ProtocolChannelBase> _protocol;

};

#endif // GATHERCONTROLLER_H
