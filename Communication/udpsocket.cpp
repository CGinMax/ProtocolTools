#include "udpsocket.h"
#include <QNetworkDatagram>
UdpSocket::UdpSocket(QObject *parent)
    : m_localAddress("0.0.0.0")
    , m_localPort(0)
    , m_remoteAddress("127.0.0.1")
    , m_remotePort(7990)
    , m_udpMode(PortParam::UdpSingle)
    , m_socket(new QUdpSocket(this))
{
    setParent(parent);
    connect(m_socket.data(), &QUdpSocket::disconnected, this, &UdpSocket::disconnected);
    connect(m_socket.data(), &QUdpSocket::readyRead, this, &UdpSocket::onReadyRead);
}

bool UdpSocket::open()
{
    return isActived();
//    if (isActived()) {
//        return true;
//    }
}

bool UdpSocket::open(const PortParam &param)
{
    m_localAddress = QHostAddress(param.m_localIp);
    m_localPort = static_cast<quint16>(param.m_localPort);
    m_remoteAddress = QHostAddress(param.m_remoteIp);
    m_remotePort = static_cast<quint16>(param.m_remotePort);
    m_udpMode = param.m_udpMode;
    bool success = false;
    QAbstractSocket::BindFlag bindFlag = QAbstractSocket::DefaultForPlatform;

    if (m_udpMode == PortParam::UdpMulticastGroup)
    {
        // 可配?
        m_socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
        bindFlag = QAbstractSocket::ShareAddress;
    }

    success = m_socket->bind(m_localAddress, m_localPort, QAbstractSocket::ShareAddress);

    if (success && m_udpMode == PortParam::UdpMulticastGroup)
    {// 组播
        success = m_socket->joinMulticastGroup(m_remoteAddress);
    }

    return success;
}

void UdpSocket::close()
{
//    m_socket->close();
//    m_socket == nullptr;??

    if (m_udpMode == PortParam::UdpMulticastGroup)
    {
        m_socket->leaveMulticastGroup(m_remoteAddress);
    }
    m_socket->close();
}

bool UdpSocket::write(const char *data, int size)
{
    QHostAddress sendAddr = m_udpMode == PortParam::UdpBroadcast ? QHostAddress::Broadcast : m_remoteAddress;
    auto len = m_socket->writeDatagram(data, size, sendAddr, m_remotePort);
    m_socket->flush();
    return len > 0;
}

bool UdpSocket::write(const QByteArray &data)
{
//    QHostAddress sendAddr = m_udpMode == PortParam::UdpBroadcast ? QHostAddress::Broadcast : m_remoteAddress;
    auto len = m_socket->writeDatagram(data, m_remoteAddress, m_remotePort);
    m_socket->flush();
    return len > 0;
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
