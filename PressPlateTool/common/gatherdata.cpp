#include "gatherdata.h"

GatherData::GatherData(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_id(-1)
    , m_addr(-1)
    , m_version(QString())
{

}

GatherData::~GatherData()
{
}

QString GatherData::name() const
{
    return m_name;
}

void GatherData::setName(const QString &name)
{
    if (m_name == name) {
        return ;
    }
    m_name = name;
    emit nameChanged(name);
}

int GatherData::id() const
{
    return m_id;
}

void GatherData::setId(int id)
{
    m_id = id;
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

QString GatherData::version() const
{
    return m_version;
}

void GatherData::setVersion(const QString &version)
{
    m_version = version;
}

PortParam GatherData::portParam() const
{
    return m_portParam;
}

void GatherData::setPortParam(const PortParam &portParam)
{
    m_portParam = portParam;
}
