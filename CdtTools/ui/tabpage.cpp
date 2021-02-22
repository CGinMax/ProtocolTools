#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include <QMessageBox>
#include "../enums.h"
#include "cdtsettingdlg.h"
#include "../common/threadpool.h"

TabPage::TabPage(QWidget *parent)
    : QWidget(parent)
    , m_settingData(new SettingData)
    , m_serverPage(new ServerPage(m_settingData, this))
    , m_clientPage(new ClientPage(m_settingData,this))
    , m_udpPage(new UdpPage(m_settingData, this))
    , ui(new Ui::TabPage)

{
    ui->setupUi(this);
    initWidget();

}

TabPage::~TabPage()
{
    delete ui;
}

void TabPage::initWidget()
{
    auto* intValid = new QIntValidator(0, 65535);
    QRegularExpression regExp(QLatin1String("^((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}$"));
    auto* regValid = new QRegularExpressionValidator(regExp);
    ui->editIp->setText("127.0.0.1");
    ui->editPort->setText("2404");
    ui->editIp->setValidator(regValid);
    ui->editPort->setValidator(intValid);
    ui->editRemoteIp->setText("127.0.0.1");
    ui->editReomtePort->setText("9001");
    ui->editRemoteIp->setValidator(regValid);
    ui->editReomtePort->setValidator(intValid);

    auto btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->btnStart);
    btnGroup->addButton(ui->btnStop);
    btnGroup->setExclusive(true);

    ui->stackedWidget->addWidget(m_serverPage.data());
    ui->stackedWidget->addWidget(m_clientPage.data());
    ui->stackedWidget->addWidget(m_udpPage.data());
    connect(this, &TabPage::updateData, m_serverPage.data(), &ServerPage::onUpdateData);
    connect(this, &TabPage::updateData, m_clientPage.data(), &ClientPage::onUpdateData);
    connect(this, &TabPage::updateData, m_udpPage.data(), &UdpPage::onUpdateData);
}

void TabPage::resetSettingData()
{
    m_settingData->m_ip = ui->editIp->text();
    m_settingData->m_port = ui->editPort->text().toInt();
    m_settingData->m_remoteIp = ui->editRemoteIp->text();
    m_settingData->m_remotePort = ui->editReomtePort->text().toInt();
    m_settingData->m_networkType = eNetworkType(ui->cbbNetworkType->currentIndex());
    m_settingData->m_stationType = eStationType(ui->cbbStationType->currentIndex());

}

void TabPage::setConfigureWidgetEnabled(bool enabled)
{
    ui->btnSetting->setEnabled(enabled);
    ui->btnStart->setEnabled(enabled);
    ui->btnStop->setEnabled(!enabled);
}

void TabPage::on_cbbNetworkType_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void TabPage::on_btnStart_clicked()
{
    bool success = false;
    resetSettingData();
    switch (ui->cbbNetworkType->currentIndex()) {
    case eNetworkType::eTcpServer:
    {
        success = m_serverPage->start();
    }
        break;
    case eNetworkType::eTcpClient:
        success = m_clientPage->start();
        break;
    case eNetworkType::eUdp:
        success = m_udpPage->start();
        break;
    case eNetworkType::eSerialPort:
        break;
    }
    if (!success) {
        QMessageBox::critical(this, tr("错误"), tr("打开通讯端口失败"), QMessageBox::Ok, QMessageBox::Cancel);
        return ;
    }
    setConfigureWidgetEnabled(false);

}

void TabPage::on_btnStop_clicked()
{
    switch (ui->cbbNetworkType->currentIndex()) {
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
