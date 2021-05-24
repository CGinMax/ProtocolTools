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
    , m_dataBits(dataBits)
    , m_stopBits(stopBits)
    , m_parity(parity)
{}

void PortParam::save(QDataStream &dataStream)
{
    dataStream << m_localIp << m_localPort << m_remoteIp << m_remotePort << m_portName << m_baudRate
               << static_cast<int>(m_dataBits) << static_cast<int>(m_stopBits) << static_cast<int>(m_parity);
}

void PortParam::load(QDataStream &dataStream)
{
    int dataBit = 0;
    int stopBit = 0;
    int parity = 0;
    dataStream >> m_localIp >> m_localPort >> m_remoteIp >> m_remotePort >> m_portName >> m_baudRate
               >> dataBit >> stopBit >> parity;

    m_dataBits = QSerialPort::DataBits(dataBit);
    m_stopBits = QSerialPort::StopBits(stopBit);
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
    root["dataBits"] = m_dataBits;
    root["stopBits"] = m_stopBits;
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

    m_dataBits = QSerialPort::DataBits(dataBit);
    m_stopBits = QSerialPort::StopBits(stopBit);
    m_parity = QSerialPort::Parity(parity);
}
