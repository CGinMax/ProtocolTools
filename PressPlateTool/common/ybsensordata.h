#ifndef YBSENSORDATA_H
#define YBSENSORDATA_H

#include <QObject>

enum YBStatus {
    OffStatus = 0x00,
    OnStatus = 0x01,
    ErrorOffStatus = 0x02,
    ErrorOnStatus = 0x03,
    WaitOffStatus = 0x04,
    WaitOnStatus = 0x05,
    UnsetStatus = 0xFF,
};

class YBSensorData : public QObject
{
    Q_OBJECT
public:
    explicit YBSensorData(QObject *parent = nullptr);
    ~YBSensorData() override = default;
    YBSensorData(const YBSensorData& other);
    YBSensorData& operator=(const YBSensorData& other);

    YBStatus currentStatus() const;
    void setCurrentStatus(const YBStatus &currentStatus);

    YBStatus configedStatus() const;
    void setConfigedStatus(const YBStatus &configedStatus);

    uint8_t addr() const;
    void setAddr(const uint8_t &addr);

    QString hardwareVersion() const;
    void setHardwareVersion(const QString &version);

    QString softwareVersion() const;
    void setSoftwareVersion(const QString& version);

    QString productDescription() const;
    void setProductDesc(const QString& desc);

    QJsonObject save();

    void load(const QJsonObject& root);

signals:

public slots:

private:
    YBStatus m_currentStatus;
    YBStatus m_configedStatus;
    uint8_t m_addr;
    QString m_hardwareVer;
    QString m_softwareVer;
    QString m_productDesc;
};

#endif // YBSENSORDATA_H
