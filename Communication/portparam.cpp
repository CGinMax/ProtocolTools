#include "portparam.h"
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
