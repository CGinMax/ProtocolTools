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
        return start(m_settingData->m_portParam);
    }

    qInfo("Error! Udp Start Failed!");
    return false;
}

bool UdpPage::start(const PortParam &param)
{
    auto udp = dynamic_cast<UdpSocket*>(m_udp.data());
    if (!udp->open(param)) {
        return false;
    }
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
