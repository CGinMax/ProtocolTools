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

    connect(m_tcpClient.data(), &TcpClient::disconnected, this, &ClientPage::clientDisconnected);
}

ClientPage::~ClientPage()
{
}

bool ClientPage::start()
{
    if (!m_settingData.isNull()) {
        if (m_tcpClient->open(PortParam(m_settingData->m_remoteIp, static_cast<ushort>(m_settingData->m_remotePort)))) {
            m_centerWidget->startCommunication(m_settingData);
            return true;
        }

        return false;
    }
    qInfo("错误，设置数据为空");
    return false;
}

void ClientPage::stop()
{

    m_centerWidget->stopCommunication();
}

void ClientPage::onUpdateData()
{
    m_centerWidget.reset(new CDTWorkWidget(m_tcpClient, m_settingData, this));
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}

