#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "communicationbase.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QScopedPointer>

class COMMUNICATIONSHARED_EXPORT UdpSocket : public CommunicationBase
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = nullptr);

public:
    bool open() override;
    bool open(const PortParam& param) override;
    void close() override;
    bool write(const char *data, int size) override;
    bool write(const QByteArray &data) override;
    int read(char *data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;

    void setRemoteParam(const QString& ip, int port);

public slots:
    void writeData(const QByteArray &data) override;
signals:

public slots:
    void onReadyRead();

private:
    QHostAddress m_localAddress;
    quint16 m_localPort;
    QHostAddress m_remoteAddress;
    quint16 m_remotePort;
    PortParam::eUdpMode m_udpMode;
    QScopedPointer<QUdpSocket> m_socket;
};

#endif // UDPSOCKET_H
