#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "networkbase.h"
#include <QTcpSocket>

class TcpClient : public NetworkBase
{
    Q_OBJECT
public:
    explicit TcpClient(const QString& ip, ushort port, QObject *parent = nullptr);
    ~TcpClient() override;

    // NetworkBase interface
    void open() override;
    void close() override;
    bool write(const QByteArray &data) override;
    QByteArray read() override;
    bool isActived() override;
signals:

public slots:

private:
    QString m_ip;
    ushort m_port;
    QScopedPointer<QTcpSocket> m_socket;
};

#endif // TCPCLIENT_H
