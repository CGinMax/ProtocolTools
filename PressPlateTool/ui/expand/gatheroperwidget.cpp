#include "gatheroperwidget.h"
#include "ui_gatheroperwidget.h"
#include <climits>

GatherOperWidget::GatherOperWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GatherOperWidget)
{
    ui->setupUi(this);

    ui->editAddr->setRange(0, INT_MAX);
    ui->editYBNum->setRange(0, 100);

    setButtonsOpened(false);

    connect(ui->btnOpen, &QAbstractButton::clicked, this, &GatherOperWidget::openCommunication);
    connect(ui->btnClose, &QAbstractButton::clicked, this, &GatherOperWidget::closeCommunication);
}

GatherOperWidget::~GatherOperWidget()
{
    delete ui;
}

int GatherOperWidget::getInputAddress()
{
    return ui->editAddr->value();
}

void GatherOperWidget::setButtonsOpened(bool isOpen)
{
    ui->btnOpen->setEnabled(!isOpen);
    ui->btnClose->setEnabled(isOpen);
}

void GatherOperWidget::on_btnSetAddr_clicked()
{
    emit setGatherAddress(ui->editAddr->text().toInt());
}

void GatherOperWidget::on_btnReset_clicked()
{
    emit resetSensorCount(ui->editYBNum->text().toInt());
}
