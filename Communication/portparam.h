#ifndef PORTPARAM_H
#define PORTPARAM_H

#include <QSerialPort>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include "communication_global.h"

class COMMUNICATIONSHARED_EXPORT PortParam : public QObject{
    Q_OBJECT
//    Q_PROPERTY(QString localIp READ localIp WRITE setLocalIp)
//    Q_PROPERTY(int localPort READ localPort WRITE setLocalPort)
//    Q_PROPERTY(QString remoteIp READ remoteIp WRITE setRemoteIp)
//    Q_PROPERTY(int remotePort READ remotePort WRITE setRemotePort)
//    Q_PROPERTY(int udpMode READ udpMode WRITE setUdpMode)

    Q_PROPERTY(QString portName READ portName WRITE setPortName)
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate)
    Q_PROPERTY(QSerialPort::DataBits dataBit READ dataBit WRITE setDataBit)
    Q_PROPERTY(QSerialPort::StopBits stopBit READ stopBit WRITE setStopBit)
    Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity)
public:
    enum eUdpMode {
        UdpSingle = 0,
        UdpBroadcast = 1,
        UdpMulticastGroup = 2,
    };
    PortParam() = default;
    explicit PortParam(const QString& localIp, int localPort, const QString& remoteIp, int remotePort);
    explicit PortParam(const QString& portName, int baudRate, QSerialPort::DataBits dataBit
              , QSerialPort::StopBits stopBit, QSerialPort::Parity parity);
    PortParam(const PortParam& other);
    PortParam& operator=(const PortParam& other);

    void save(QDataStream& dataStream);

    void load(QDataStream& dataStream);

    QJsonObject saveJson();

    void loadJson(const QJsonObject& root);

    QString portName() const;
    void setPortName(const QString &portName);
    int baudRate() const;
    void setBaudRate(int baudRate);
    QSerialPort::DataBits dataBit() const;
    void setDataBit(const QSerialPort::DataBits &dataBit);
    QSerialPort::StopBits stopBit() const;
    void setStopBit(const QSerialPort::StopBits &stopBit);
    QSerialPort::Parity parity() const;
    void setParity(const QSerialPort::Parity &parity);

    // network
    QString m_localIp{QLatin1String("127.0.0.1")};
    int m_localPort{2404};
    QString m_remoteIp{QLatin1String("127.0.0.1")};
    int m_remotePort{2404};

    eUdpMode m_udpMode{eUdpMode::UdpSingle};

private:
    // serial port
    QString m_portName{QString()};
    int m_baudRate{9600};
    QSerialPort::DataBits m_dataBit{QSerialPort::Data8};
    QSerialPort::StopBits m_stopBit{QSerialPort::OneStop};
    QSerialPort::Parity m_parity{QSerialPort::NoParity};

};

#endif // PORTPARAM_H
