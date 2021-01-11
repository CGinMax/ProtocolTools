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
    TcpServer(QTcpSocket* socket, QObject* parent = nullptr);
    ~TcpServer() override;

    // NetworkBase interface
public:
    void open() override;
    void close() override;
    bool write(const char* data, int size) override;
    bool write(const QByteArray& data) override;
    int read(char* data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;

    QString ip() const;
    ushort port() const;

signals:

public slots:
    void writeData(const QByteArray &data) override;
//    void onNewConnection();
//    void onReadyRead();
//    void onDisconnected();

private:
    QString m_ip;
    ushort m_port;
    QTcpSocket* m_socket;
//    QScopedPointer<QTcpServer> m_server;
//    QList<QTcpSocket*> m_sockets;
};

#endif // TCPSERVER_H
