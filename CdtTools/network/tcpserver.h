#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "networkbase.h"
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QScopedPointer>

class TcpServer : public NetworkBase
{
    Q_OBJECT
public:
    explicit TcpServer(const QString& ip, ushort port, QObject* parent = nullptr);
    ~TcpServer() override;

    // NetworkBase interface
public:
    void open() override;
    void close() override;
    bool write(const QByteArray& data) override;
    QByteArray read() override;
    bool isActived() override;

    QString ip() const;
    ushort port() const;

signals:

public:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QString m_ip;
    ushort m_port;
    QScopedPointer<QTcpServer> m_server;
    QList<QTcpSocket*> m_sockets;
};

#endif // TCPSERVER_H
