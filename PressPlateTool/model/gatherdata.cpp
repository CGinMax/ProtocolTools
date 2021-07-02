#include "gatherdata.h"

GatherData::GatherData(QObject *parent)
    : QObject(parent)
    , m_addr(1)
    , m_hardwareVer(QString("0.0"))
    , m_softwareVer(QString("0.0"))
    , m_productDesc(QString())
    , m_sensorCount(0)
    , m_gatherTimeout(12000)
    , m_sensorTimeout(12000)
{

}

GatherData::~GatherData()
{
}

int GatherData::addr() const
{
    return m_addr;
}

void GatherData::setAddr(int addr)
{
    if (m_addr == addr) {
        return ;
    }
    m_addr = addr;
    emit addrChanged(addr);
}

QString GatherData::hardwareVersion() const
{
    return m_hardwareVer;
}

void GatherData::setHardwareVersion(const QString &version)
{
    m_hardwareVer = version;
}

QString GatherData::softwareVersion() const
{
    return m_softwareVer;
}

void GatherData::setSoftwareVersion(const QString &softwareVersion)
{
    m_softwareVer = softwareVersion;
}

QString GatherData::productDescription() const
{
    return m_productDesc;
}

void GatherData::setProductDesc(const QString &desc)
{
    m_productDesc = desc;
}

int GatherData::sensorCount() const
{
    return m_sensorCount;
}

void GatherData::setSensorCount(int count)
{
    m_sensorCount = count;
}

PortParam GatherData::portParam() const
{
    return m_portParam;
}

void GatherData::setPortParam(const PortParam &portParam)
{
    m_portParam = portParam;
}

int GatherData::gatherTimeout() const
{
    return m_gatherTimeout;
}

void GatherData::setGatherTimeout(int msecTimeout)
{
    m_gatherTimeout = msecTimeout;
}

int GatherData::sensorTimeout() const
{
    return m_sensorTimeout;
}

void GatherData::setSensorTimeout(int msecTimeout)
{
    m_sensorTimeout = msecTimeout;
}
