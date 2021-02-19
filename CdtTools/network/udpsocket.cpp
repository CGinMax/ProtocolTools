#include "udpsocket.h"
#include <QNetworkDatagram>
UdpSocket::UdpSocket(QObject *parent)
    : m_socket(new QUdpSocket(this))
{
    setParent(parent);
    connect(m_socket.data(), &QUdpSocket::disconnected, this, &UdpSocket::disconnected);
    connect(m_socket.data(), &QUdpSocket::readyRead, this, &NetworkBase::readyRead);
}

void UdpSocket::open()
{
    if (isActived()) {
        return;
    }
}

void UdpSocket::open(const QString &ip, ushort port)
{
    m_socket->bind(QHostAddress(ip), port, QUdpSocket::ShareAddress);
}

void UdpSocket::close()
{
    m_socket->disconnectFromHost();
    m_socket->close();
}

bool UdpSocket::write(const char *data, int size)
{
    return m_socket->writeDatagram(data, size, m_address, m_port) > 0;
}

bool UdpSocket::write(const QByteArray &data)
{
    return m_socket->writeDatagram(data, m_address, m_port) > 0;
}

int UdpSocket::read(char *data, int size)
{
    return static_cast<int>(m_socket->readDatagram(data, size));
}

QByteArray UdpSocket::readAll()
{
    auto datagram = m_socket->receiveDatagram();
    m_address = datagram.senderAddress();
    m_port = datagram.senderPort();
    return datagram.data();
}

bool UdpSocket::isActived()
{
    return !m_socket.isNull() && m_socket->state() == QUdpSocket::BoundState;
}

QString UdpSocket::toString()
{
    if (isActived()) {
        return QString("%1:%2").arg(m_socket->peerAddress().toString()).arg(m_socket->peerPort());
    }
    return QLatin1String("Unnamed");
}

void UdpSocket::writeData(const QByteArray &data)
{
    this->write(data);
}
