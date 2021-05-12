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

    QString version() const;
    void setVersion(const QString &version);

signals:

public slots:

private:
    YBStatus m_currentStatus;
    YBStatus m_configedStatus;
    uint8_t m_addr;
    QString m_version;
};

#endif // YBSENSORDATA_H
