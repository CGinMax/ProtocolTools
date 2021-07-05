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
    explicit GatherData(QObject *parent = nullptr);
    ~GatherData() override;

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

signals:
    void addrChanged(int addr);

public slots:

private:
    int m_addr;
    QString m_hardwareVer;
    QString m_softwareVer;
    QString m_productDesc;
    int m_sensorCount;

    PortParam m_portParam;
};

#endif // YBGATHERDATA_H
