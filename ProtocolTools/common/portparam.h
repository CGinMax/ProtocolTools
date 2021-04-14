#ifndef PORTPARAM_H
#define PORTPARAM_H

#include <QSerialPort>
struct PortParam{
    PortParam() = default;
    PortParam(const QString& localIp, int localPort, const QString& remoteIp, int remotePort)
        : m_localIp(localIp)
        , m_localPort(localPort)
        , m_remoteIp(remoteIp)
        , m_remotePort(remotePort)
    {}
    PortParam(const QString& portName, int baudRate, QSerialPort::DataBits dataBits
              , QSerialPort::StopBits stopBits, QSerialPort::Parity parity)
        : m_portName(portName)
        , m_baudRate(baudRate)
        , m_dataBits(dataBits)
        , m_stopBits(stopBits)
        , m_parity(parity)
    {}

    // network
    QString m_localIp{QLatin1String("127.0.0.1")};
    int m_localPort{2404};
    QString m_remoteIp{QLatin1String("127.0.0.1")};
    int m_remotePort{2404};

    // serial port
    QString m_portName{QString()};
    int m_baudRate{9600};
    QSerialPort::DataBits m_dataBits{QSerialPort::Data8};
    QSerialPort::StopBits m_stopBits{QSerialPort::OneStop};
    QSerialPort::Parity m_parity{QSerialPort::NoParity};
};

#endif // PORTPARAM_H
