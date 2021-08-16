#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include <QMessageBox>
#include "cdtsettingdlg.h"
#include "../common/threadpool.h"

TabPage::TabPage(const QString& name, QWidget *parent)
    : QWidget(parent)
    , m_settingData(new SettingData)
    , m_serverPage(new ServerPage(m_settingData, this))
    , m_clientPage(new ClientPage(m_settingData,this))
    , m_udpPage(new UdpPage(m_settingData, this))
    , m_serialPage(new SerialPortPage(m_settingData, this))
    , m_pageName(name)
    , ui(new Ui::TabPage)

{
    ui->setupUi(this);
    initWidget();

}

TabPage::TabPage(const QSharedPointer<SettingData> &settingData, const QString& name, QWidget *parent)
    : QWidget(parent)
    , m_settingData(settingData)
    , m_serverPage(new ServerPage(settingData, this))
    , m_clientPage(new ClientPage(settingData,this))
    , m_udpPage(new UdpPage(settingData, this))
    , m_serialPage(new SerialPortPage(m_settingData, this))
    , m_pageName(name)
    , ui(new Ui::TabPage)
{
    ui->setupUi(this);
    initWidget();
    emit updateData();
}

TabPage::~TabPage()
{
    delete ui;
}

void TabPage::initWidget()
{
    ui->splitter->setChildrenCollapsible(false);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    auto* intValid = new QIntValidator(0, 65535);
    QRegularExpression regExp(QLatin1String("^((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}$"));
    auto* regValid = new QRegularExpressionValidator(regExp);
    ui->editIp->setText(m_settingData->m_portParam.m_localIp);
    ui->editPort->setText(QString::number(m_settingData->m_portParam.m_localPort));
    ui->editIp->setValidator(regValid);
    ui->editPort->setValidator(intValid);
    ui->editRemoteIp->setText(m_settingData->m_portParam.m_remoteIp);
    ui->editReomtePort->setText(QString::number(m_settingData->m_portParam.m_remotePort));
    ui->editRemoteIp->setValidator(regValid);
    ui->editReomtePort->setValidator(intValid);

    auto devList = QSerialPortInfo::availablePorts();
    for (auto& devInfo : devList) {
        ui->cbbDevList->addItem(devInfo.portName(), devInfo.portName());
    }
    auto baudrateList = QSerialPortInfo::standardBaudRates();
    for (auto& baudrate : baudrateList) {
        ui->cbbBaudRate->addItem(QString::number(baudrate), baudrate);
    }
    for (int i = 8; i >= 5; i--){
        ui->cbbDataBit->addItem(QString::number(i), i);
    }
    ui->cbbStopBit->addItem(QString("1"), 1);
    ui->cbbStopBit->addItem(QString("1.5"), 3);
    ui->cbbStopBit->addItem(QString("2"), 2);
    ui->cbbParityBit->addItem(tr("None"), 0);
    ui->cbbParityBit->addItem(tr("Even Parity"), 2);
    ui->cbbParityBit->addItem(tr("Odd Parity"), 3);
    ui->cbbParityBit->addItem(tr("Space Parity"), 4);
    ui->cbbParityBit->addItem(tr("Mark Parity"), 5);

    ui->cbbBaudRate->setCurrentText(QLatin1String("9600"));

    ui->cbbStationType->setCurrentIndex(m_settingData->m_stationType);

    ui->paramStackedWidget->setCurrentIndex(static_cast<int>(m_settingData->m_networkType) >= 3 ? 1 : 0);

    auto btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->btnStart);
    btnGroup->addButton(ui->btnStop);
    btnGroup->setExclusive(true);

    setConfigureWidgetEnabled(true);

    ui->pageStackedWidget->addWidget(m_serverPage.data());
    ui->pageStackedWidget->addWidget(m_clientPage.data());
    ui->pageStackedWidget->addWidget(m_udpPage.data());
    ui->pageStackedWidget->addWidget(m_serialPage.data());
    ui->pageStackedWidget->setCurrentIndex(m_settingData->m_networkType);
    connect(this, &TabPage::updateData, m_serverPage.data(), &ServerPage::onUpdateData);
    connect(this, &TabPage::updateData, m_clientPage.data(), &ClientPage::onUpdateData);
    connect(this, &TabPage::updateData, m_udpPage.data(), &UdpPage::onUpdateData);
    connect(this, &TabPage::updateData, m_serialPage.data(), &SerialPortPage::onUpdateData);
    connect(m_clientPage.data(), &ClientPage::clientDisconnected, this, &TabPage::on_btnStop_clicked);

}

void TabPage::resetSettingData()
{
    m_settingData->m_portParam.m_localIp = ui->editIp->text();
    m_settingData->m_portParam.m_localPort = ui->editPort->text().toInt();
    m_settingData->m_portParam.m_remoteIp = ui->editRemoteIp->text();
    m_settingData->m_portParam.m_remotePort = ui->editReomtePort->text().toInt();

    m_settingData->m_portParam.setPortName(ui->cbbDevList->currentData().toString());
    m_settingData->m_portParam.setBaudRate(ui->cbbBaudRate->currentData().toInt());
    m_settingData->m_portParam.setDataBit(static_cast<QSerialPort::DataBits>(ui->cbbDataBit->currentData().toInt()));
    m_settingData->m_portParam.setStopBit(static_cast<QSerialPort::StopBits>(ui->cbbStopBit->currentData().toInt()));
    m_settingData->m_portParam.setParity(static_cast<QSerialPort::Parity>(ui->cbbParityBit->currentData().toInt()));

    m_settingData->m_stationType = eStationType(ui->cbbStationType->currentIndex());

}

void TabPage::setConfigureWidgetEnabled(bool enabled)
{
    ui->btnSetting->setEnabled(enabled);
    ui->btnStart->setEnabled(enabled);
    ui->btnStop->setEnabled(!enabled);
}

void TabPage::startCommunication()
{
    on_btnStart_clicked();
}

void TabPage::stopCommunication()
{
    on_btnStop_clicked();
}

SettingData *TabPage::getSettingData() const
{
    return m_settingData.data();
}

void TabPage::setPageName(const QString &name)
{
    m_pageName = name;
}

QString TabPage::getPageName() const
{
    return m_pageName;
}

void TabPage::on_btnStart_clicked()
{
    bool success = false;
    resetSettingData();
    switch (m_settingData->m_networkType) {
    case eNetworkType::eTcpServer:
        success = m_serverPage->start();
        break;
    case eNetworkType::eTcpClient:
        success = m_clientPage->start();
        break;
    case eNetworkType::eUdp:
        success = m_udpPage->start();
        break;
    case eNetworkType::eSerialPort:
        success = m_serialPage->start();
        break;

    default:
        break;
    }
    if (!success) {
        QMessageBox::critical(this, tr("Error"), tr("Open Communication Failed!"), QMessageBox::Ok, QMessageBox::Cancel);
        return ;
    }
    setConfigureWidgetEnabled(false);

}

void TabPage::on_btnStop_clicked()
{
    switch (m_settingData->m_networkType) {
    case eNetworkType::eTcpServer:
        m_serverPage->stop();
        break;
    case eNetworkType::eTcpClient:
        m_clientPage->stop();
        break;
    case eNetworkType::eUdp:
        m_udpPage->stop();
        break;
    case eNetworkType::eSerialPort:
        m_serialPage->stop();
        break;

    default:
        break;
    }
    setConfigureWidgetEnabled(true);
}

void TabPage::on_btnSetting_clicked()
{
    CDTSettingDlg dlg(m_settingData->m_ptCfg, this);
    dlg.exec();
    emit updateData();
}

void TabPage::on_chbBaudRate_toggled(bool checked)
{
    ui->cbbBaudRate->setEditable(checked);
}

void TabPage::on_cbbUdpMode_currentIndexChanged(int index)
{
    m_settingData->m_portParam.m_udpMode = PortParam::eUdpMode(index);
}
