#include "tabpage.h"
#include "ui_tabpage.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include "enums.h"
#include "../common/threadpool.h"
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtcycle.h"

TabPage::TabPage(QWidget *parent)
    : QWidget(parent)
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
}

void TabPage::on_cbbProtocl_currentIndexChanged(int index)
{
}

void TabPage::on_btnStart_clicked()
{
    m_network.clear();
    m_protocol.clear();
    switch (ui->cbbProtocl->currentIndex()) {
    case NetworkType::eTcpServer:
        m_network.reset(new TcpServer(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case NetworkType::eTcpClient:
        m_network.reset(new TcpClient(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case NetworkType::eUdp:
        break;
    case NetworkType::eSerialPort:
        break;
    }
    connect(m_network.get(), &NetworkBase::connected, [=](){
        qDebug("Connect");
    });
    m_network->open();
    m_protocol.reset(new CDTProtocol(m_network, eStationType::Minitor));
    ThreadPool::instance()->run([this](){
        this->m_protocol->start();
    });
}

void TabPage::on_btnStop_clicked()
{
    if (m_network->isActived()) {
        m_network->close();
    }
    m_protocol->stop();
}
