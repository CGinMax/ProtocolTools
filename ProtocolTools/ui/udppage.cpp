#include "udppage.h"

UdpPage::UdpPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent)
    : QWidget(parent)
    , m_udp(new UdpSocket(this))
    , m_settingData(ptCfg)
    , m_centerWidget(new CDTWorkWidget(m_udp, ptCfg, this))
{
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}

UdpPage::~UdpPage()
{

}

bool UdpPage::start()
{
    if (!m_settingData.isNull()) {
        return start(m_settingData->m_ip, m_settingData->m_port, m_settingData->m_remoteIp, m_settingData->m_remotePort);
    }

    qInfo("错误，设置数据为空");
    return false;
}

bool UdpPage::start(const QString &localIp, int localPort, const QString &remoteIp, int remotePort)
{
    auto udp = dynamic_cast<UdpSocket*>(m_udp.data());
    udp->setRemoteParam(remoteIp, remotePort);
    udp->open(localIp, static_cast<ushort>(localPort));
    m_centerWidget->startCommunication(m_settingData);
    return true;

}

void UdpPage::stop()
{
    m_centerWidget->stopCommunication();
}

void UdpPage::onUpdateData()
{
    m_centerWidget.reset(new CDTWorkWidget(m_udp, m_settingData, this));
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}
