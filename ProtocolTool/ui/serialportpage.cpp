#include "serialportpage.h"
#include <QVBoxLayout>

SerialPortPage::SerialPortPage(const QSharedPointer<SettingData> &settingData, QWidget *parent)
    : QWidget(parent)
    , m_serialPort(new SerialPort())
    , m_settingData(settingData)
    , m_centerWidget(new CDTWorkWidget(m_serialPort, settingData, this))
{
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}

SerialPortPage::~SerialPortPage()
{

}

bool SerialPortPage::start()
{
    if (!m_settingData.isNull()) {
        if (m_serialPort->open(m_settingData->m_portParam)) {
            m_centerWidget->startCommunication(m_settingData);
            return true;
        }

    }
    qInfo("Error! SerialPort Start Failed!");
    return false;
}

void SerialPortPage::stop()
{
    m_centerWidget->stopCommunication();
}

void SerialPortPage::onUpdateData()
{
    m_centerWidget.reset(new CDTWorkWidget(m_serialPort, m_settingData, this));
    m_layout->addWidget(m_centerWidget.data());
    m_layout->setContentsMargins(0, 0, 0, 0);
}
