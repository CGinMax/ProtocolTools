#ifndef PORTPARAM_H
#define PORTPARAM_H

#include <QSerialPort>
#include <QDataStream>
#include "communication_global.h"

class COMMUNICATIONSHARED_EXPORT PortParam{
public:
    enum eUdpMode {
        UdpSingle = 0,
        UdpBroadcast = 1,
        UdpMulticastGroup = 2,
    };
    PortParam() = default;
    PortParam(const QString& localIp, int localPort, const QString& remoteIp, int remotePort);
    PortParam(const QString& portName, int baudRate, QSerialPort::DataBits dataBits
              , QSerialPort::StopBits stopBits, QSerialPort::Parity parity);

    void save(QDataStream& dataStream);

    void load(QDataStream& dataStream);

    // network
    QString m_localIp{QLatin1String("127.0.0.1")};
    int m_localPort{2404};
    QString m_remoteIp{QLatin1String("127.0.0.1")};
    int m_remotePort{2404};

    eUdpMode m_udpMode{eUdpMode::UdpSingle};

    // serial port
    QString m_portName{QString()};
    int m_baudRate{9600};
    QSerialPort::DataBits m_dataBits{QSerialPort::Data8};
    QSerialPort::StopBits m_stopBits{QSerialPort::OneStop};
    QSerialPort::Parity m_parity{QSerialPort::NoParity};
};

#endif // PORTPARAM_H
