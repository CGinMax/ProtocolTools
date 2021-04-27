#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "communicationbase.h"
#include <QSerialPortInfo>

class COMMUNICATIONSHARED_EXPORT SerialPort : public CommunicationBase
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort() override;

    // NetworkBase interface
    bool open() override;
    bool open(const PortParam& param) override;
    void close() override;
    bool write(const char *data, int size) override;
    bool write(const QByteArray &data) override;
    int read(char *data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;

public slots:
    void writeData(const QByteArray &data) override;


private:
    PortParam m_portParam;
    int _ReadTimeout;
    int _WriteTimeout;
    bool _RtsEnable;
    bool _DtrEnable;
    QScopedPointer<QSerialPort> m_serialPort;
};

#endif // SERIALPORT_H
