#include "clientpage.h"
#include <QVBoxLayout>
#include <QHostAddress>

ClientPage::ClientPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent)
    : QWidget(parent)
    , m_tcpClient(new TcpClient())
    , m_settingData(ptCfg)
    , m_centerWidget(new CDTWorkWidget(m_tcpClient, ptCfg, this))
{
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}

ClientPage::~ClientPage()
{
}

bool ClientPage::start()
{
    if (!m_settingData.isNull()) {
        m_tcpClient->open(m_settingData->m_ip, m_settingData->m_port);
        m_centerWidget->startCommunication(m_settingData);
        return true;
    }
    else {
        qInfo("setting data empty");
        return false;
    }
}

void ClientPage::stop()
{

    m_centerWidget->stopCommunication();
}

void ClientPage::onUpdateData()
{
    m_centerWidget.reset(new CDTWorkWidget(m_tcpClient, m_settingData, this));
    m_layout->addWidget(m_centerWidget.data());
}

