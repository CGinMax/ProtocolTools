#include "sensoradddialog.h"
#include "ui_sensoradddialog.h"
#include "../buttons/outlinebutton.h"
#include "../buttons/raisebutton.h"

SensorAddDialog::SensorAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorAddDialog)
{
    ui->setupUi(this);

    auto okBtn = new Ui::RaiseButton(tr("OK"), this);

    auto cancelBtn = new Ui::OutlineButton(tr("Cancel"), this);

    ui->btnLayout->addWidget(cancelBtn);
    ui->btnLayout->addWidget(okBtn);

    connect(okBtn, &QAbstractButton::clicked, this, &SensorAddDialog::accept);
    connect(cancelBtn, &QAbstractButton::clicked, this, &SensorAddDialog::reject);
}

SensorAddDialog::~SensorAddDialog()
{
    delete ui;
}

int SensorAddDialog::getCount()
{
    return ui->editCount->value();
}
