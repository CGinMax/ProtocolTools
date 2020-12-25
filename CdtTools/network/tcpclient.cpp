#include "tcpclient.h"

TcpClient::TcpClient(const QString &ip, ushort port, QObject *parent)
    : m_ip(ip)
    , m_port(port)
    , m_socket(new QTcpSocket(this))
{
    setParent(parent);
    connect(m_socket.get(), &QTcpSocket::connected, this, &TcpClient::connected);
}

TcpClient::~TcpClient()
{

}

void TcpClient::open()
{
    if (isActived()) {
        return;
    }
    m_socket->connectToHost(m_ip, m_port);
}

void TcpClient::close()
{
    if (isActived()) {
        m_socket->disconnectFromHost();
    }
}

bool TcpClient::write(const QByteArray &data)
{
    qint64 writeLen = m_socket->write(data);
    return writeLen > 0;
}

QByteArray TcpClient::read()
{
    return QByteArray();
}

bool TcpClient::isActived()
{
    return !m_socket.isNull() && m_socket->state() == QTcpSocket::ConnectedState;
}
