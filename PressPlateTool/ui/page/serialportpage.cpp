#include "serialportpage.h"
#include "ui_serialportpage.h"
#include "../../Communication/portparam.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <climits>

SerialPortPage::SerialPortPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPortPage)
{
    ui->setupUi(this);
    ui->editNum->setRange(1, INT_MAX);

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
}

SerialPortPage::~SerialPortPage()
{
    delete ui;
}

void SerialPortPage::setCountEditHidden(bool isHidden)
{
    ui->txtNum->setHidden(isHidden);
    ui->editNum->setHidden(isHidden);
}

void SerialPortPage::setBtnGroupHidden(bool isHidden)
{
    ui->btnOK->setHidden(isHidden);
    ui->btnCancel->setHidden(isHidden);
}

PortParam SerialPortPage::getPortParam() const
{
    PortParam param;
    param.m_portName = ui->cbbDevList->currentData().toString();
    param.m_baudRate = ui->cbbBaudRate->currentData().toInt();
    param.m_dataBits = static_cast<QSerialPort::DataBits>(ui->cbbDataBit->currentData().toInt());
    param.m_stopBits = static_cast<QSerialPort::StopBits>(ui->cbbStopBit->currentData().toInt());
    param.m_parity = static_cast<QSerialPort::Parity>(ui->cbbParityBit->currentData().toInt());

    return param;
}
