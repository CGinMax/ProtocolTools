#include "sensoroperationdlg.h"
#include "ui_sensoroperationdlg.h"

#include <QFont>

SensorOperationDlg::SensorOperationDlg(const QString &title, const QString &info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorOperationDlg)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->txtInfo->setText(info);
    auto font = ui->txtInfo->font();
    font.setBold(true);
    font.setPixelSize(16);
    ui->txtInfo->setFont(font);
}

SensorOperationDlg::~SensorOperationDlg()
{
    delete ui;
}
