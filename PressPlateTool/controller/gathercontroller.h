#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "../model/gatherdata.h"
#include "../protocol/ybprotocolchannel.h"

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(QObject *parent = nullptr);
    ~GatherController() override;

    QSharedPointer<GatherData> gatherData() const;
    void setGatherData(const QSharedPointer<GatherData> &gatherData);

    void appendSensorData(YBSensorData* data);

    bool isCommunicationActive();
    YBProtocolChannel* protocol();

signals:
    void stopProtocolChannel();
    void deleteItem();

public slots:
    void onQueryVersion();
    void onTitleChanged(const QString& title);
    void onSetGatherAddress(int addr);
    void onResetSensorCount(int count);

private:
    bool canDoOperate();
    GatherController* setAddress(int addr);
    GatherController* setHardwareVersion(const QString& version);
    GatherController* setSoftwareVersion(const QString& version);
    GatherController* setProductDesc(const QString& desc);
    GatherController* setSensorCount(int count);

private:
    QSharedPointer<GatherData> m_gatherData;

    QSharedPointer<CommunicationBase> m_communication;
    QSharedPointer<ProtocolChannelBase> m_protocol;

};

#endif // GATHERCONTROLLER_H
