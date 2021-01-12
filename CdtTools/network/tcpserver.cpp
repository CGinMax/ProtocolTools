#include "tcpserver.h"
#include <QDebug>
#include <QThread>

TcpServer::TcpServer(const QString &ip, ushort port, QObject *parent)
    : m_ip(ip)
    , m_port(port)
    , m_socket(nullptr)
{
    setParent(parent);
}

TcpServer::TcpServer(QTcpSocket *socket, QObject *parent)
    : m_socket(socket)
{
    setParent(parent);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpServer::disconnected);
}

TcpServer::~TcpServer()
{
}

void TcpServer::open()
{
    if (isActived()) {
        return;
    }

}

void TcpServer::close()
{
    m_socket->close();
}

bool TcpServer::write(const char *data, int size)
{
    return m_socket->write(data, size) > 0;
}

bool TcpServer::write(const QByteArray &data)
{
    qDebug() << "socket" << QThread::currentThread();
    return m_socket->write(data) > 0;
}

int TcpServer::read(char *data, int size)
{
    return m_socket->read(data, size);
}

QByteArray TcpServer::readAll()
{
    return m_socket->readAll();
}

bool TcpServer::isActived()
{
    return m_socket != nullptr && m_socket->state() == QAbstractSocket::ConnectedState;
}

QString TcpServer::toString()
{
    if (isActived()) {
        return QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
    }
    return QLatin1String("Unnamed");
}

ushort TcpServer::port() const
{
    return m_port;
}

void TcpServer::writeData(const QByteArray &data)
{
    m_socket->write(data);
}

QString TcpServer::ip() const
{
    return m_ip;
}

//void TcpServer::onNewConnection()
//{
//    auto socket = m_server->nextPendingConnection();
//    connect(socket, &QTcpSocket::readyRead, this,&TcpServer::onReadyRead);
//    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
//    m_sockets.append(socket);
//    emit connected();
//}

//void TcpServer::onReadyRead()
//{
//    auto socket = qobject_cast<QTcpSocket*>(sender());
////    auto readData = socket->readAll();

////    emit recvData(readData);
//}

//void TcpServer::onDisconnected()
//{
//    auto socket = qobject_cast<QTcpSocket*>(sender());
//    m_sockets.removeAt(m_sockets.indexOf(socket));
//    // fix me
//    socket->deleteLater();
//}
