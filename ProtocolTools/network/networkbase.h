#ifndef NETWORKBASE_H
#define NETWORKBASE_H

#include <QObject>
#include <QSerialPort>
struct PortParam{
    PortParam();
    PortParam(const QString& ip, ushort port);
    PortParam(const QString& portName, int baudRate, QSerialPort::DataBits dataBits
              , QSerialPort::StopBits stopBits, QSerialPort::Parity parity);
    // network
    QString m_ip{QString()};
    ushort m_port{2404};

    // serial port
    QString m_portName{QString()};
    int m_baudRate{9600};
    QSerialPort::DataBits m_dataBits{QSerialPort::Data8};
    QSerialPort::StopBits m_stopBits{QSerialPort::OneStop};
    QSerialPort::Parity m_parity{QSerialPort::NoParity};
};

class NetworkBase : public QObject
{
    Q_OBJECT
public:
    virtual ~NetworkBase();

    virtual bool open() = 0;
    virtual bool open(const PortParam& param) = 0;
    virtual void close() = 0;
    virtual bool write(const char* data, int size) = 0;
    virtual bool write(const QByteArray& data) = 0;
    virtual int read(char* data, int size) = 0;
    virtual QByteArray readAll() = 0;
    virtual bool isActived() = 0;
    virtual QString toString() = 0;

signals:
    void connected();
    void disconnected();
    void readyRead();
    void recvData(const QByteArray& data);
    void showMessage(const QString& msg);

public slots:
    virtual void writeData(const QByteArray& data) = 0;
};

#endif // NETWORKBASE_H
