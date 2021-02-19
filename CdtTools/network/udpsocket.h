#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "networkbase.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QScopedPointer>

class UdpSocket : public NetworkBase
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = nullptr);

public:
    void open() override;
    void open(const QString &ip, ushort port) override;
    void close() override;
    bool write(const char *data, int size) override;
    bool write(const QByteArray &data) override;
    int read(char *data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;


public slots:
    void writeData(const QByteArray &data) override;
signals:

public slots:

private:
    QHostAddress m_address;
    quint16 m_port;
    QScopedPointer<QUdpSocket> m_socket;
};

#endif // UDPSOCKET_H
