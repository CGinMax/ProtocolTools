#include "serverpage.h"
#include "ui_cdtworkwidget.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include "../protocol/cdtprotocol.h"

ServerPage::ServerPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent)
    : QWidget(parent)
    , m_tcpServer(new QTcpServer(this))
    , m_tabClients(new QTabWidget(this))
    , m_settingData(ptCfg)
{

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_tabClients.data());
    layout->setContentsMargins(0, 0, 0, 0);
    m_tabClients->setTabsClosable(true);

    connect(m_tabClients.data(), &QTabWidget::tabCloseRequested, this, &ServerPage::onTabCloseRequested);
    connect(m_tcpServer.data(), &QTcpServer::newConnection, this, &ServerPage::onNewConnection);
}

ServerPage::~ServerPage()
{
    close();
}

void ServerPage::start(const QString &ip, int port, eStationType type)
{
    if (ip == "0.0.0.0") {
        m_tcpServer->listen(QHostAddress::Any, port);
    }
    else {
        m_tcpServer->listen(QHostAddress(ip), port);
    }
    //m_stationType = type;
}

void ServerPage::stopListen()
{
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
    }
}

void ServerPage::close()
{
    stopListen();
    for (auto& client : m_tcpClients) {
        client->close();
    }

}

void ServerPage::onNewConnection()
{

    QSharedPointer<NetworkBase> server(new TcpServer(m_tcpServer->nextPendingConnection()));
    m_tcpClients.append(server);


    ProtocolBase* protocol = nullptr;
    switch (m_settingData->m_ptCfg->m_protocol) {
    case eProtocol::CDTStandard:
        protocol = new CDTProtocol(server, m_settingData);
        break;
    case eProtocol::CDTUt:
        break;
    case eProtocol::CDTNr:
        break;
    case eProtocol::CDTGc:
        break;
    default:
        break;
    }

    m_tabClients->insertTab(0, new CDTWorkWidget(m_settingData->m_ptCfg, protocol, m_tabClients.data()), server->toString());

    ThreadPool::instance()->run([protocol](){
        protocol->start();
    });
}

void ServerPage::onTabCloseRequested(int index)
{

}
