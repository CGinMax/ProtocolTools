#include "networkbase.h"


NetworkBase::~NetworkBase()
{

}

PortParam::PortParam()
{

}

PortParam::PortParam(const QString &ip, ushort port)
    : m_ip(ip)
    , m_port(port)
{

}

PortParam::PortParam(const QString &portName, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits, QSerialPort::Parity parity)
    : m_portName(portName)
    , m_baudRate(0)
    , m_dataBits(dataBits)
    , m_stopBits(stopBits)
    , m_parity(parity)
{

}
