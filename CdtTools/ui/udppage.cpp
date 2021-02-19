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
    return start(m_settingData->m_ip, m_settingData->m_port);
}

bool UdpPage::start(const QString &ip, int port)
{
    if (!m_settingData.isNull()) {
        m_udp->open(ip, static_cast<ushort>(port));
        m_centerWidget->startCommunication(m_settingData);
        return true;
    }

    qInfo("错误，设置数据为空");
    return false;
}

void UdpPage::stop()
{
    m_centerWidget->stopCommunication();
}
