#include "ybsensordata.h"

YBSensorData::YBSensorData(QObject *parent) : QObject(parent)
{

}

YBSensorData::YBSensorData(const YBSensorData &other)
{
    *this = other;
}

YBSensorData &YBSensorData::operator=(const YBSensorData &other)
{
    m_id = other.m_id;
    m_currentStatus = other.m_currentStatus;
    m_configedStatus = other.m_configedStatus;
    m_addr = other.m_addr;
    m_version = other.m_version;
    return *this;
}

QString YBSensorData::id() const
{
    return m_id;
}

void YBSensorData::setId(const QString &id)
{
    m_id = id;
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

QString YBSensorData::version() const
{
    return m_version;
}

void YBSensorData::setVersion(const QString &version)
{
    m_version = version;
}
