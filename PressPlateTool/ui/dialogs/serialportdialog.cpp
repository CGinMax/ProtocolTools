#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include "portparam.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <climits>

SerialPortDialog::SerialPortDialog(bool isMulti, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SerialPortDialog)

{
    ui->setupUi(this);
    ui->serialportConfWidget->setCountEditHidden(!isMulti);


    connect(ui->serialportConfWidget, &SerialPortPage::okClicked, this, &SerialPortDialog::accept);
    connect(ui->serialportConfWidget, &SerialPortPage::cancelClicked, this, &SerialPortDialog::reject);
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

PortParam SerialPortDialog::portParam() const
{
    return ui->serialportConfWidget->getPortParam();
}

int SerialPortDialog::gatherNum() const
{
    return ui->serialportConfWidget->getGatherCount();
}
