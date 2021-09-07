#include "ybsensordata.h"
#include <QJsonObject>

YBSensorData::YBSensorData(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_currentStatus(YBStatus::OffStatus)
    , m_configedStatus(YBStatus::UnsetStatus)
    , m_addr(1)
    , m_hardwareVer(QString("0.0"))
    , m_softwareVer(QString("0.0"))
    , m_productDesc(QString())
{

}

YBSensorData::YBSensorData(const YBSensorData &other)
{
    *this = other;
}

YBSensorData &YBSensorData::operator=(const YBSensorData &other)
{
    m_name = other.m_name;
    m_currentStatus = other.m_currentStatus;
    m_configedStatus = other.m_configedStatus;
    m_addr = other.m_addr;
    m_hardwareVer = other.m_hardwareVer;
    m_softwareVer = other.m_softwareVer;
    m_productDesc = other.m_productDesc;
    return *this;
}

QString YBSensorData::name() const
{
    return m_name;
}

void YBSensorData::setName(const QString &name)
{
    m_name = name;
}

YBStatus YBSensorData::currentStatus() const
{
    return m_currentStatus;
}

void YBSensorData::setCurrentStatus(const YBStatus &currentStatus)
{
    m_currentStatus = currentStatus;
}

YBStatus YBSensorData::configedStatus() const
{
    return m_configedStatus;
}

void YBSensorData::setConfigedStatus(const YBStatus &configedStatus)
{
    m_configedStatus = configedStatus;
}

uint8_t YBSensorData::addr() const
{
    return m_addr;
}

void YBSensorData::setAddr(const uint8_t &addr)
{
    m_addr = addr;
}

QString YBSensorData::hardwareVersion() const
{
    return m_hardwareVer;
}

void YBSensorData::setHardwareVersion(const QString &version)
{
    m_hardwareVer = version;
}

QString YBSensorData::softwareVersion() const
{
    return m_softwareVer;
}

void YBSensorData::setSoftwareVersion(const QString &version)
{
    m_softwareVer = version;
}

QString YBSensorData::productDescription() const
{
    return m_productDesc;
}

void YBSensorData::setProductDesc(const QString &desc)
{
    m_productDesc =desc;
}

QJsonObject YBSensorData::save()
{
    QJsonObject root;
    root.insert(QLatin1String("name"), m_name);
    root.insert(QLatin1String("currentStatus"), m_currentStatus);
    root.insert(QLatin1String("configedStatus"), m_configedStatus);
    root.insert(QLatin1String("address"), m_addr);
    root.insert(QLatin1String("hardwareVersion"), m_hardwareVer);
    root.insert(QLatin1String("softwareVersion"), m_softwareVer);
    root.insert(QLatin1String("productDescription"), m_productDesc);
    return root;
}

void YBSensorData::load(const QJsonObject &root)
{
    m_name = root.value(QLatin1String("name")).toString();
    m_currentStatus = YBStatus(root.value(QLatin1String("currentStatus")).toInt());
    m_configedStatus = YBStatus(root.value(QLatin1String("configedStatus")).toInt());
    m_addr = static_cast<uint8_t>(root.value(QLatin1String("address")).toInt());
    m_hardwareVer = root.value(QLatin1String("hardwareVersion")).toString();
    m_softwareVer = root.value(QLatin1String("softwareVersion")).toString();
    m_productDesc = root.value(QLatin1String("productDescription")).toString();
}
