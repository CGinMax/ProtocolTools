#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <climits>

SerialPortDialog::SerialPortDialog(bool isMulti, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SerialPortDialog)
    , m_gatherNum(1)

{
    ui->setupUi(this);
    ui->txtNum->setHidden(!isMulti);
    ui->editNum->setHidden(!isMulti);

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

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

PortParam SerialPortDialog::portParam() const
{
    return m_portParam;
}

int SerialPortDialog::gatherNum() const
{
    return m_gatherNum;
}

void SerialPortDialog::on_btnOk_clicked()
{
    m_gatherNum = ui->editNum->value();
    m_portParam.m_portName = ui->cbbDevList->currentData().toString();
    m_portParam.m_baudRate = ui->cbbBaudRate->currentData().toInt();
    m_portParam.m_dataBits = static_cast<QSerialPort::DataBits>(ui->cbbDataBit->currentData().toInt());
    m_portParam.m_stopBits = static_cast<QSerialPort::StopBits>(ui->cbbStopBit->currentData().toInt());
    m_portParam.m_parity = static_cast<QSerialPort::Parity>(ui->cbbParityBit->currentData().toInt());
    accept();
}

void SerialPortDialog::on_btnCancel_clicked()
{
    reject();
}
