#include "tcpclient.h"

TcpClient::TcpClient(const QString &ip, ushort port, QObject *parent)
    : m_ip(ip)
    , m_port(port)
    , m_socket(new QTcpSocket(this))
{
    setParent(parent);
    connect(m_socket.data(), &QTcpSocket::connected, this, &TcpClient::connected);
    connect(m_socket.data(), &QTcpSocket::disconnected, this, &TcpClient::disconnected);
    connect(m_socket.data(), &QTcpSocket::readyRead, this, &TcpClient::readyRead);
}

TcpClient::TcpClient(QObject *parent)
    : m_socket(new QTcpSocket(this))
{
    setParent(parent);
    connect(m_socket.data(), &QTcpSocket::connected, this, &TcpClient::connected);
    connect(m_socket.data(), &QTcpSocket::disconnected, this, &TcpClient::disconnected);
    connect(m_socket.data(), &QTcpSocket::readyRead, this, &TcpClient::readyRead);
}

TcpClient::~TcpClient()
{

}

bool TcpClient::open()
{
    if (isActived()) {
        return true;
    }
    m_socket->connectToHost(m_ip, m_port);
    return m_socket->waitForConnected(100);
}

bool TcpClient::open(const PortParam &param)
{
    if (isActived()) {
        return true;
    }
    m_socket->connectToHost(param.m_ip, param.m_port);
    return m_socket->waitForConnected(100);
}

void TcpClient::close()
{
    if (isActived()) {
        m_socket->disconnectFromHost();
    }
}

bool TcpClient::write(const char *data, int size)
{
    return m_socket->write(data, size) > 0;
}

bool TcpClient::write(const QByteArray &data)
{
    return m_socket->write(data) > 0;
}

int TcpClient::read(char *data, int size)
{
    return m_socket->read(data, size);
}

QByteArray TcpClient::readAll()
{
    return m_socket->readAll();
}

bool TcpClient::isActived()
{
    return !m_socket.isNull() && m_socket->state() == QTcpSocket::ConnectedState;
}

QString TcpClient::toString()
{
    if (isActived()) {
        return QString("%1:%2").arg(m_socket->peerName()).arg(m_socket->peerPort());
    }
    return QLatin1String("Unnamed");
}

void TcpClient::writeData(const QByteArray &data)
{
    m_socket->write(data);
}
