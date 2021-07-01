#ifndef GATHERDATA_H
#define GATHERDATA_H

#include <QObject>
#include <QSharedPointer>
#include "ybsensordata.h"
#include "portparam.h"

class GatherData : public QObject
{
    Q_OBJECT
public:
    explicit GatherData(const QString& name = QString(), QObject *parent = nullptr);
    ~GatherData() override;

    QString name() const;
    void setName(const QString& name);

    int addr() const;
    void setAddr(int addr);

    QString hardwareVersion() const;
    void setHardwareVersion(const QString &hardwareVersion);

    QString softwareVersion() const;
    void setSoftwareVersion(const QString& softwareVersion);

    QString productDescription() const;
    void setProductDesc(const QString& desc);

    int sensorCount() const;
    void setSensorCount(int count);

    void appendSensorData(const QSharedPointer<YBSensorData>& data);
    QList<QSharedPointer<YBSensorData>> sensorDataList() const;
    void removeSensorData(int index);
    void clearSensorDataList();

    PortParam portParam() const;
    void setPortParam(const PortParam &portParam);

    int gatherTimeout() const;
    void setGatherTimeout(int msecTimeout);

    int sensorTimeout() const;
    void setSensorTimeout(int msecTimeout);

    QJsonObject save();

    void load(const QJsonObject& root);

signals:
    void nameChanged(const QString& name);

    void addrChanged(int addr);

public slots:

private:
    QString m_name;
    int m_addr;
    QString m_hardwareVer;
    QString m_softwareVer;
    QString m_productDesc;
    int m_sensorCount;
    // delete here
    QList<QSharedPointer<YBSensorData>> m_ybDataList;
    PortParam m_portParam;

    int m_gatherTimeout;
    int m_sensorTimeout;
};

#endif // YBGATHERDATA_H
