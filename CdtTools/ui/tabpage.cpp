#include "tabpage.h"
#include "ui_tabpage.h"
#include "enums.h"

TabPage::TabPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabPage)
{
    ui->setupUi(this);
}

TabPage::~TabPage()
{
    delete ui;
}

void TabPage::initWidget()
{

//    ui->editIp->setValidator()
}

void TabPage::on_cbbProtocl_currentIndexChanged(int index)
{
}

void TabPage::on_btnStart_clicked()
{
    m_network.clear();
    switch (ui->cbbProtocl->currentIndex()) {
    case NetworkType::TcpServer:
        m_network.reset(new class TcpServer(ui->editIp->text(), ui->editPort->text().toInt()));
        break;
    case NetworkType::TcpClient:
        break;
    case NetworkType::Udp:
        break;
    case NetworkType::SerialPort:
        break;
    }
    m_network->open();
}

void TabPage::on_btnStop_clicked()
{
    m_network->close();
}
