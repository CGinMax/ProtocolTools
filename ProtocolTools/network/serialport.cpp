#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
    : m_serialPort(new QSerialPort())
{
    setParent(parent);
//    connect(m_serialPort.data(), )
    connect(m_serialPort.data(), &QSerialPort::readyRead, this, &SerialPort::readyRead);
}

SerialPort::~SerialPort()
{

}


bool SerialPort::open()
{
    if (isActived()) {
        return true;
    }

    return m_serialPort->open(QIODevice::ReadWrite);
}

bool SerialPort::open(const PortParam &param)
{
    if (isActived()) {
        return true;
    }
    m_portParam = param;
    m_serialPort->setBaudRate(param.m_baudRate);
    m_serialPort->setDataBits(param.m_dataBits);
    m_serialPort->setStopBits(param.m_stopBits);
    m_serialPort->setParity(param.m_parity);
    m_serialPort->setPortName(param.m_portName);

    return m_serialPort->open(QIODevice::ReadWrite);
}

void SerialPort::close()
{
    m_serialPort->close();
}

bool SerialPort::write(const char *data, int size)
{
    return m_serialPort->write(data, size) > 0;
}

bool SerialPort::write(const QByteArray &data)
{
    return m_serialPort->write(data) > 0;
}

int SerialPort::read(char *data, int size)
{
    // TODO(shijm):更改读方式
    return m_serialPort->read(data, size) ;
}

QByteArray SerialPort::readAll()
{
    return m_serialPort->readAll();
}

bool SerialPort::isActived()
{
    return !m_serialPort.isNull() && m_serialPort->isOpen();
}

QString SerialPort::toString()
{
    if (isActived()) {
        return m_portParam.m_portName;
    }
    return QLatin1String("Unkonw");
}

void SerialPort::writeData(const QByteArray &data)
{
    m_serialPort->write(data);
}
