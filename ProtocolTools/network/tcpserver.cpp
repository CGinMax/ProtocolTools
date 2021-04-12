#include "tcpserver.h"
#include <QDebug>
#include <QThread>

TcpServer::TcpServer(QObject *parent)
    : m_socket(nullptr)
{
    setParent(parent);
}

TcpServer::TcpServer(QTcpSocket *socket, QObject *parent)
    : m_socket(socket)
{
    setParent(parent);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpServer::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpServer::readyRead);
}

TcpServer::~TcpServer()
{
}

bool TcpServer::open()
{
    return isActived();
//    if (isActived()) {
//        return;
//    }

}

bool TcpServer::open(const QString &ip, ushort port)
{
    Q_UNUSED(ip)
    Q_UNUSED(port)
    return true;
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

void TcpServer::writeData(const QByteArray &data)
{
    m_socket->write(data);
}
