#include "udpsocket.h"
#include <QNetworkDatagram>
UdpSocket::UdpSocket(QObject *parent)
    : m_localAddress("0.0.0.0")
    , m_localPort(0)
    , m_remoteAddress("127.0.0.1")
    , m_remotePort(7990)
    , m_socket(new QUdpSocket(this))
{
    setParent(parent);
    connect(m_socket.data(), &QUdpSocket::disconnected, this, &UdpSocket::disconnected);
//    connect(m_socket.data(), &QUdpSocket::readyRead, this, &NetworkBase::readyRead);
    connect(m_socket.data(), &QUdpSocket::readyRead, this, &UdpSocket::onReadyRead);
}

void UdpSocket::open()
{
    if (isActived()) {
        return;
    }
}

void UdpSocket::open(const QString &ip, ushort port)
{
    m_localAddress = QHostAddress(ip);
    m_localPort = port;
    m_socket->bind(QHostAddress(ip), port, QUdpSocket::ShareAddress);
}

void UdpSocket::close()
{
    m_socket->disconnectFromHost();
    m_socket->close();
}

bool UdpSocket::write(const char *data, int size)
{
    return m_socket->writeDatagram(data, size, m_remoteAddress, m_remotePort) > 0;
}

bool UdpSocket::write(const QByteArray &data)
{
    return m_socket->writeDatagram(data, m_remoteAddress, m_remotePort) > 0;
}

int UdpSocket::read(char *data, int size)
{
    return static_cast<int>(m_socket->readDatagram(data, size));
}

QByteArray UdpSocket::readAll()
{
    char *datagram = new char[4096];
    memset(datagram, 0, strlen(datagram));
    auto readLen = m_socket->readDatagram(datagram, 4096, &m_localAddress, &m_localPort);
    QByteArray ba(datagram, static_cast<int>(readLen));
    delete[] datagram;
    return ba;
//    auto datagram = m_socket->receiveDatagram();
//    m_address = datagram.senderAddress();
//    m_port = datagram.senderPort();
//    return datagram.data();
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

void UdpSocket::setRemoteParam(const QString &ip, int port)
{
    m_remoteAddress = QHostAddress(ip);
    m_remotePort = port;
}

void UdpSocket::writeData(const QByteArray &data)
{
    this->write(data);
}

void UdpSocket::onReadyRead()
{
    QByteArray readBytes = readAll();
    emit recvData(readBytes);
}
