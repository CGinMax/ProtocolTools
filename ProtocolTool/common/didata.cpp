#include "didata.h"

DiData::DiData(QObject *parent) : QObject(parent)
{

}

DiData::DiData(int io, const QString &name, bool value, QObject *parent)
    : QObject (parent)
    , m_io(io)
    , m_name(name)
    , m_value(value)
{

}

DiData::DiData(const DiData &other): QObject(nullptr)
{
    *this = other;
}

DiData &DiData::operator=(const DiData &other)
{
    m_io = other.io();
    m_name = other.name();
    m_value = other.value();
    return *this;
}

DiData::DiData(DiData &&other) noexcept
{
    *this = std::move(other);
}

DiData &DiData::operator=(DiData &&other) noexcept
{
    m_io = other.io();
    m_name = other.name();
    m_value = other.value();
    return *this;
}
