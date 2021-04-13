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
    explicit TcpServer(QObject* parent = nullptr);
    explicit TcpServer(QTcpSocket* socket, QObject* parent = nullptr);
    ~TcpServer() override;

    // NetworkBase interface
public:
    bool open() override;
    bool open(const PortParam& param) override;
    void close() override;
    bool write(const char* data, int size) override;
    bool write(const QByteArray& data) override;
    int read(char* data, int size) override;
    QByteArray readAll() override;
    bool isActived() override;
    QString toString() override;

signals:

public slots:
    void writeData(const QByteArray &data) override;

private:
    QTcpSocket* m_socket;
};

#endif // TCPSERVER_H
