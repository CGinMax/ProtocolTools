#include "tcpserver.h"

TcpServer::TcpServer(const QString &ip, ushort port, QObject *parent)
    : m_ip(ip)
    , m_port(port)
    , m_server(new QTcpServer(this))
{
    connect(m_server.get(), &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

TcpServer::~TcpServer()
{
}

void TcpServer::open()
{
    if (isActived()) {
        return;
    }

    if (!m_server->listen(QHostAddress(m_ip), m_port)) {
        // failed notify
        qDebug("listen failed");
    }
}

void TcpServer::close()
{
    m_server->close();
    for (auto& socket : m_sockets) {
        socket->close();
    }
    QList<QTcpSocket*>().swap(m_sockets);
}

bool TcpServer::write(const QByteArray &data)
{
    bool ok = false;
    for (auto& socket : m_sockets) {
        if (socket->write(data) >= 0) {
            ok = true;
        }
    }

    return ok;
}

QByteArray TcpServer::read()
{
    QByteArray ba;
    for (auto& socket : m_sockets) {
        //qDebug("%s:%d", qPrintable(socket->peerAddress().toString()), socket->peerPort());
        //char data[4096]={0};
        //qDebug("%d",socket->read(data, 4096));
//        ba.append(socket->read(4096));
//        ba.append(socket->readAll());
    }
    return ba;
}

bool TcpServer::isActived()
{
    return !m_server.isNull() && m_server->isListening();
}

ushort TcpServer::port() const
{
    return m_port;
}

QString TcpServer::ip() const
{
    return m_ip;
}

void TcpServer::onNewConnection()
{
    auto socket = m_server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this,&TcpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
    m_sockets.append(socket);
    emit connected();
}

void TcpServer::onReadyRead()
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    auto readData = socket->readAll();

    emit recvData(readData);
}

void TcpServer::onDisconnected()
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    m_sockets.removeAt(m_sockets.indexOf(socket));
//            m_sockets.erase()
}
