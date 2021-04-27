#include "serverpage.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QMessageBox>
#include <QTabBar>
#include <QMenu>
#include <QDebug>


ServerPage::ServerPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent)
    : QWidget(parent)
    , m_tcpServer(new QTcpServer(this))
    , m_tabClients(new QTabWidget(this))
    , m_settingData(ptCfg)
    , m_layout(new QVBoxLayout(this))
{

    initTabWidget();

    connect(m_tcpServer.data(), &QTcpServer::newConnection, this, &ServerPage::onNewConnection);
}

ServerPage::~ServerPage()
{
    stop();
}

void ServerPage::initTabWidget()
{
    m_layout->addWidget(m_tabClients.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_tabClients->setTabsClosable(true);
    auto tabbar = m_tabClients->tabBar();
    tabbar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabbar, &QTabBar::customContextMenuRequested, this, [this](const QPoint& /*pos*/){
        QMenu menu;
        menu.addAction(tr("Close disconnected tab"), this, &ServerPage::onCloseDisconnected);
        menu.exec(QCursor::pos());
    });
    connect(m_tabClients.data(), &QTabWidget::tabCloseRequested, this, &ServerPage::onTabCloseRequested);
}

bool ServerPage::start()
{
    if (!m_settingData.isNull()) {
        return start(m_settingData->m_portParam);
    }

    qInfo("Failed:setting data empty");
    return false;
}

bool ServerPage::start(const PortParam &param)
{
    QHostAddress address;
    if (param.m_localIp == "0.0.0.0") {
        address = QHostAddress::Any;
    }
    else {
        address = QHostAddress(param.m_localIp);
    }
    return m_tcpServer->listen(address, static_cast<quint16>(param.m_localPort));
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

void ServerPage::onUpdateData()
{
    for (int i = 0; i < m_tabClients->count(); i++) {
        onTabCloseRequested(i);
    }
    m_tabClients->clear();
    m_tabClients.reset(new QTabWidget(this));
    initTabWidget();
}

void ServerPage::onNewConnection()
{

    QSharedPointer<CommunicationBase> server(new TcpServer(m_tcpServer->nextPendingConnection()));

    auto centerWidget = new CDTWorkWidget(server, m_settingData);
    centerWidget->startCommunication(m_settingData);
    connect(centerWidget, &CDTWorkWidget::disconnected, this, &ServerPage::onDisconnected);
    connect(server.data(), &CommunicationBase::disconnected, this, [=](){
        if (centerWidget) {
//            if (m_closedClient.count() > 6) {
//                auto clientWidget = m_closedClient.head();
//                m_closedClient.pop_front();
//                delete clientWidget;
//                clientWidget = nullptr;
//            }
            m_closedClient.append(centerWidget);
        }
    });

    m_tabClients->insertTab(0, centerWidget, QIcon(":/icon/resources/signal-connect.png"), server->toString());
    m_tabClients->setCurrentIndex(0);

}

void ServerPage::onDisconnected()
{
    auto widget = qobject_cast<CDTWorkWidget*>(sender());
    for (int i = 0; i < m_tabClients->count(); i++) {
        if (m_tabClients->widget(i) == widget) {
            m_tabClients->setTabIcon(i, QIcon(":/icon/resources/signal-close.png"));
            break;
        }
    }
}

void ServerPage::onTabCloseRequested(int index)
{
    auto widget = qobject_cast<CDTWorkWidget*>(m_tabClients->widget(index));
    if (widget->isConnection()) {
        auto ret = QMessageBox::warning(widget, QStringLiteral("提示"), QStringLiteral("通讯正在进行，是否断开？"), QMessageBox::Ok, QMessageBox::Cancel);

        if (ret != QMessageBox::Ok) {
            return ;
        }
        widget->stopCommunication();
    }
    m_closedClient.removeOne(widget);
    delete widget;
    widget = nullptr;
}

void ServerPage::onCloseDisconnected()
{
//    QList<int> delIndexs;
//    for (int i = 0; i < m_tabClients->count(); i++) {
//        qDebug("count:%d", m_tabClients->count());
//        auto widget = qobject_cast<CDTWorkWidget*>(m_tabClients->widget(i));
//        if (!widget->isConnection()) {
//            delete widget;
//            widget = nullptr;
//            delIndexs.append(i);
//        }
//    }
    std::for_each(m_closedClient.begin(), m_closedClient.end(), [](CDTWorkWidget* widget){
        delete widget;
        widget = nullptr;
    });
    m_closedClient.clear();

    m_tabClients->setCurrentIndex(-1);
}
