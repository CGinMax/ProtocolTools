#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include <QMessageBox>
#include "../enums.h"
#include "cdtsettingdlg.h"
#include "../common/threadpool.h"

TabPage::TabPage(const QString& name, QWidget *parent)
    : QWidget(parent)
    , m_settingData(new SettingData)
    , m_serverPage(new ServerPage(m_settingData, this))
    , m_clientPage(new ClientPage(m_settingData,this))
    , m_udpPage(new UdpPage(m_settingData, this))
    , m_pageName(name)
    , ui(new Ui::TabPage)

{
    ui->setupUi(this);
    initWidget();

}

TabPage::TabPage(QSharedPointer<SettingData> settingData, const QString& name, QWidget *parent)
    : QWidget(parent)
    , m_settingData(settingData)
    , m_serverPage(new ServerPage(settingData, this))
    , m_clientPage(new ClientPage(settingData,this))
    , m_udpPage(new UdpPage(settingData, this))
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
    ui->splitter->setCollapsible(0, false);
    ui->splitter->setCollapsible(1, false);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    auto* intValid = new QIntValidator(0, 65535);
    QRegularExpression regExp(QLatin1String("^((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}$"));
    auto* regValid = new QRegularExpressionValidator(regExp);
    ui->editIp->setText(m_settingData->m_ip);
    ui->editPort->setText(QString::number(m_settingData->m_port));
    ui->editIp->setValidator(regValid);
    ui->editPort->setValidator(intValid);
    ui->editRemoteIp->setText(m_settingData->m_remoteIp);
    ui->editReomtePort->setText(QString::number(m_settingData->m_remotePort));
    ui->editRemoteIp->setValidator(regValid);
    ui->editReomtePort->setValidator(intValid);
    ui->cbbNetworkType->setCurrentIndex(m_settingData->m_networkType);
    ui->cbbStationType->setCurrentIndex(m_settingData->m_stationType);

    auto btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->btnStart);
    btnGroup->addButton(ui->btnStop);
    btnGroup->setExclusive(true);

    ui->stackedWidget->addWidget(m_serverPage.data());
    ui->stackedWidget->addWidget(m_clientPage.data());
    ui->stackedWidget->addWidget(m_udpPage.data());
    ui->stackedWidget->setCurrentIndex(m_settingData->m_networkType);
    connect(this, &TabPage::updateData, m_serverPage.data(), &ServerPage::onUpdateData);
    connect(this, &TabPage::updateData, m_clientPage.data(), &ClientPage::onUpdateData);
    connect(this, &TabPage::updateData, m_udpPage.data(), &UdpPage::onUpdateData);
    connect(m_clientPage.data(), &ClientPage::clientDisconnected, this, &TabPage::on_btnStop_clicked);
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
