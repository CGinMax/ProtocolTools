#include "gatherdata.h"

GatherData::GatherData(QObject *parent) : QObject(parent)
{

}

QString GatherData::id() const
{
    return m_id;
}

void GatherData::setId(const QString &id)
{
    m_id = id;
}

QString GatherData::addr() const
{
    return m_addr;
}

void GatherData::setAddr(const QString &addr)
{
    m_addr = addr;
}

QString GatherData::version() const
{
    return m_version;
}

void GatherData::setVersion(const QString &version)
{
    m_version = version;
}
