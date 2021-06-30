#include "portparam.h"
#include <QJsonDocument>
PortParam::PortParam(const QString& localIp, int localPort, const QString& remoteIp, int remotePort)
    : m_localIp(localIp)
    , m_localPort(localPort)
    , m_remoteIp(remoteIp)
    , m_remotePort(remotePort)
{}

PortParam::PortParam(const QString& portName, int baudRate, QSerialPort::DataBits dataBits
          , QSerialPort::StopBits stopBits, QSerialPort::Parity parity)
    : m_portName(portName)
    , m_baudRate(baudRate)
    , m_dataBit(dataBits)
    , m_stopBit(stopBits)
    , m_parity(parity)
{}

PortParam::PortParam(const QVariantMap &values)
{
    m_portName = values.value(QLatin1String("portName")).toString();
    m_baudRate = values.value(QLatin1String("baudRate")).toInt();
    m_dataBit = static_cast<QSerialPort::DataBits>(values.value(QLatin1String("dataBit")).toInt());
    m_stopBit = static_cast<QSerialPort::StopBits>(values.value(QLatin1String("stopBit")).toInt());
    m_parity = static_cast<QSerialPort::Parity>(values.value(QLatin1String("parity")).toInt());
}

PortParam::PortParam(const PortParam &other)
{
    *this = other;
}

PortParam &PortParam::operator=(const PortParam &other)
{
    this->m_localIp = other.m_localIp;
    this->m_localPort = other.m_localPort;
    this->m_remoteIp = other.m_remoteIp;
    this->m_remotePort = other.m_remotePort;
    this->m_udpMode = other.m_udpMode;

    this->m_portName = other.m_portName;
    this->m_baudRate = other.m_baudRate;
    this->m_dataBit = other.m_dataBit;
    this->m_stopBit = other.m_stopBit;
    this->m_parity = other.m_parity;
    return *this;
}

void PortParam::save(QDataStream &dataStream)
{
    dataStream << m_localIp << m_localPort << m_remoteIp << m_remotePort << m_portName << m_baudRate
               << static_cast<int>(m_dataBit) << static_cast<int>(m_stopBit) << static_cast<int>(m_parity);
}

void PortParam::load(QDataStream &dataStream)
{
    int dataBit = 0;
    int stopBit = 0;
    int parity = 0;
    dataStream >> m_localIp >> m_localPort >> m_remoteIp >> m_remotePort >> m_portName >> m_baudRate
               >> dataBit >> stopBit >> parity;

    m_dataBit = QSerialPort::DataBits(dataBit);
    m_stopBit = QSerialPort::StopBits(stopBit);
    m_parity = QSerialPort::Parity(parity);
}

QJsonObject PortParam::saveJson()
{
    QJsonObject root;
    root["localIp"] = m_localIp;
    root["localPort"] = m_localPort;
    root["remoteIp"] = m_remoteIp;
    root["remotePort"] = m_remotePort;
    root["portName"] = m_portName;
    root["baudRate"] = m_baudRate;
    root["dataBits"] = m_dataBit;
    root["stopBits"] = m_stopBit;
    root["parity"] = m_parity;
    return root;
}

void PortParam::loadJson(const QJsonObject &root)
{
    m_localIp = root.value(QLatin1String("localIp")).toString();
    m_localPort = root.value(QLatin1String("localPort")).toInt();
    m_remoteIp = root.value(QLatin1String("remoteIp")).toString();
    m_remotePort = root.value(QLatin1String("remotePort")).toInt();
    m_portName = root.value(QLatin1String("portName")).toString();
    m_baudRate = root.value(QLatin1String("baudRate")).toInt();
    int dataBit = root.value(QLatin1String("dataBits")).toInt();
    int stopBit = root.value(QLatin1String("stopBits")).toInt();
    int parity = root.value(QLatin1String("parity")).toInt();

    m_dataBit = QSerialPort::DataBits(dataBit);
    m_stopBit = QSerialPort::StopBits(stopBit);
    m_parity = QSerialPort::Parity(parity);
}

QSerialPort::Parity PortParam::parity() const
{
    return m_parity;
}

void PortParam::setParity(const QSerialPort::Parity &parity)
{
    m_parity = parity;
}

QSerialPort::StopBits PortParam::stopBit() const
{
    return m_stopBit;
}

void PortParam::setStopBit(const QSerialPort::StopBits &stopBits)
{
    m_stopBit = stopBits;
}

QSerialPort::DataBits PortParam::dataBit() const
{
    return m_dataBit;
}

void PortParam::setDataBit(const QSerialPort::DataBits &dataBits)
{
    m_dataBit = dataBits;
}

int PortParam::baudRate() const
{
    return m_baudRate;
}

void PortParam::setBaudRate(int baudRate)
{
    m_baudRate = baudRate;
}

QString PortParam::portName() const
{
    return m_portName;
}

void PortParam::setPortName(const QString &portName)
{
    m_portName = portName;
}
