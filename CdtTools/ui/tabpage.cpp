#include "tabpage.h"
#include "ui_tabpage.h"
#include "enums.h"
#include <QRegularExpressionValidator>
#include <QIntValidator>

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
    switch (ui->cbbProtocl->currentIndex()) {
    case NetworkType::TcpServer:
        m_network.reset(new class TcpServer(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case NetworkType::TcpClient:
        m_network.reset(new class TcpClient(ui->editIp->text(), static_cast<ushort>(ui->editPort->text().toInt())));
        break;
    case NetworkType::Udp:
        break;
    case NetworkType::SerialPort:
        break;
    }
    connect(m_network.get(), &NetworkBase::connected, [=](){
        qDebug("Connect");
    });
    m_network->open();
}

void TabPage::on_btnStop_clicked()
{
    if (m_network->isActived()) {
        m_network->close();

    }
}
