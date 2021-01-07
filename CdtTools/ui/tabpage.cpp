#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include <QButtonGroup>
#include "enums.h"
#include "../common/threadpool.h"
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtcycle.h"

TabPage::TabPage(QWidget *parent)
    : QWidget(parent)
    , m_ptCfg(new PtCfg)
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
}

void TabPage::on_cbbProtocl_currentIndexChanged(int index)
{
}

void TabPage::on_btnStart_clicked()
{
    m_protocol.clear();
    m_network.clear();
    switch (ui->cbbProtocl->currentIndex()) {
    case eNetworkType::eTcpServer:
        m_network.reset(new TcpServer(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case eNetworkType::eTcpClient:
        m_network.reset(new TcpClient(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case eNetworkType::eUdp:
        break;
    case eNetworkType::eSerialPort:
        break;
    }
//    connect(m_network.get(), &NetworkBase::connected, [=](){
//        qDebug("Connect");

//        m_protocol.reset(new CDTProtocol(m_network, eStationType::Minitor));
//        ThreadPool::instance()->run([this](){
//            this->m_protocol->start();
//        });
//    });

    m_network->open();
    ui->btnStart->setEnabled(false);

}

void TabPage::on_btnStop_clicked()
{
    m_protocol->stop();
    if (m_network->isActived()) {
        m_network->close();
    }
    ui->btnStart->setEnabled(true);
}
