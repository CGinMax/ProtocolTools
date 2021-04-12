#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "networkbase.h"
#include <QTcpSocket>

class TcpClient : public NetworkBase
{
    Q_OBJECT
public:
    explicit TcpClient(const QString& ip, ushort port, QObject *parent = nullptr);
    explicit TcpClient(QObject* parent = nullptr);

    ~TcpClient() override;

    // NetworkBase interface
    bool open() override;
    bool open(const QString& ip, ushort port);
    void close() override;
    bool write(const char* data, int size) override;
    bool write(const QByteArray &data) override;
    int read(char* data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;
signals:

public slots:
    void writeData(const QByteArray &data) override;

private:
    QString m_ip;
    ushort m_port;
    QScopedPointer<QTcpSocket> m_socket;

};

#endif // TCPCLIENT_H
