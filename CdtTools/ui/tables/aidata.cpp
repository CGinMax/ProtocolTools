#include "aidata.h"

AiData::AiData(QObject *parent) : QObject(parent)
{

}

AiData::AiData(int io, const QString &name, int value, QObject *parent)
    : QObject (parent)
    , m_io(io)
    , m_name(name)
    , m_value(value)
{

}

AiData::AiData(const AiData &other)
{
    *this = other;
}

AiData &AiData::operator=(const AiData &other)
{
    m_io = other.io();
    m_name = other.name();
    m_value = other.value();
    return *this;
}

AiData::AiData(AiData &&other) noexcept
{
    *this = std::move(other);
}

AiData &AiData::operator=(AiData &&other) noexcept
{
    m_io = other.io();
    m_name = other.name();
    m_value = other.value();
    return *this;
}
