#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include "enums.h"
#include "cdtsettingdlg.h"
#include "../common/threadpool.h"
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtcycle.h"

TabPage::TabPage(QWidget *parent)
    : QWidget(parent)
    , m_settingData(new SettingData)
    , m_serverPage(new ServerPage(m_settingData, this))
    , m_clientPage(new ClientPage(this))
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

    auto btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->btnStart);
    btnGroup->addButton(ui->btnStop);
    btnGroup->setExclusive(true);

    ui->stackedWidget->addWidget(m_serverPage.data());
    ui->stackedWidget->addWidget(m_clientPage.data());
}

void TabPage::resetSettingData()
{
    m_settingData->m_ip = ui->editIp->text();
    m_settingData->m_port = ui->editPort->text().toInt();
    m_settingData->m_networkType = eNetworkType(ui->cbbNetworkType->currentIndex());
    m_settingData->m_stationType = eStationType(ui->cbbStationType->currentIndex());

}

void TabPage::on_cbbNetworkType_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void TabPage::on_btnStart_clicked()
{
    resetSettingData();
    switch (ui->cbbNetworkType->currentIndex()) {
    case eNetworkType::eTcpServer:
        m_serverPage->start();
        break;
    case eNetworkType::eTcpClient:
        m_clientPage->start();
        break;
    case eNetworkType::eUdp:
        break;
    case eNetworkType::eSerialPort:
        break;
    }
    ui->btnStart->setEnabled(false);

}

void TabPage::on_btnStop_clicked()
{
    switch (ui->cbbNetworkType->currentIndex()) {
    case eNetworkType::eTcpServer:
        m_serverPage->stop();
        break;
    case eNetworkType::eTcpClient:
        //m_clientPage->start();
        break;
    case eNetworkType::eUdp:
        break;
    case eNetworkType::eSerialPort:
        break;
    }
    ui->btnStart->setEnabled(true);
}

void TabPage::on_btnSetting_clicked()
{
    CDTSettingDlg dlg(m_settingData->m_ptCfg, this);
    dlg.exec();
}
