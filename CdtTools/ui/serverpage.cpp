#include "serverpage.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QMessageBox>
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtinteracte.h"
#include <QDebug>

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
    stop();
}

void ServerPage::start()
{
    if (!m_settingData.isNull()) {
        start(m_settingData->m_ip, m_settingData->m_port);
    }
    else {
        qInfo("settin data empty");
    }
}

void ServerPage::start(const QString &ip, int port)
{
    if (ip == "0.0.0.0") {
        m_tcpServer->listen(QHostAddress::Any, port);
    }
    else {
        m_tcpServer->listen(QHostAddress(ip), port);
    }
}

void ServerPage::stopListen()
{
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
    }
}

void ServerPage::stop()
{
    stopListen();

    for (int i = 0; i < m_tabClients->count(); i++) {
        auto widget = qobject_cast<CDTWorkWidget*>(m_tabClients->widget(i));
        if (widget->isConnection()) {
            widget->stopCommunication();
        }
    }

}

void ServerPage::onNewConnection()
{

    QSharedPointer<NetworkBase> server(new TcpServer(m_tcpServer->nextPendingConnection()));

    auto centerWidget = new CDTWorkWidget(server, m_settingData);
    qDebug() << centerWidget;
//    m_tabClients->insertTab(0, centerWidget, server->toString());
//    m_tabClients->setCurrentIndex(0);
    m_tabClients->addTab(centerWidget, server->toString());

}

void ServerPage::onTabCloseRequested(int index)
{
    auto widget = qobject_cast<CDTWorkWidget*>(m_tabClients->widget(index));
    qDebug() << widget;
    if (widget->isConnection()) {
        auto ret = QMessageBox::warning(widget, QStringLiteral("提示"), QStringLiteral("通讯正在进行，是否断开？"), QMessageBox::Ok, QMessageBox::Cancel);

        if (ret != QMessageBox::Ok) {
            return ;
        }
        widget->stopCommunication();
    }

    delete widget;
    m_tabClients->removeTab(index);
}