#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
    : m_serialPort(new QSerialPort())
{
    setParent(parent);
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
    m_serialPort->setPortName(param.portName());
    m_serialPort->setBaudRate(param.baudRate());
    m_serialPort->setDataBits(param.dataBit());
    m_serialPort->setStopBits(param.stopBit());
    m_serialPort->setParity(param.parity());

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
    qint64 numRead = 0;
    int numReadTotal = 0;
    char buff[100] = {0};

     for (;;) {
         memset(buff, 0, sizeof(buff)/sizeof(char));
         numRead  = m_serialPort->read(buff, 100);

         memcpy(data + numReadTotal, buff, static_cast<size_t>(numRead));

         numReadTotal += numRead;
         if ((numRead == 0 || numReadTotal > size) && !m_serialPort->waitForReadyRead(30)) {
             break;
         }
     }
    return numReadTotal;
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
        return m_portParam.portName();
    }
    return QLatin1String("Unkonw");
}

void SerialPort::writeData(const QByteArray &data)
{
    m_serialPort->write(data);
}
