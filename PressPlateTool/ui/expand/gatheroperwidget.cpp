#include "gatheroperwidget.h"
#include "ui_gatheroperwidget.h"

GatherOperWidget::GatherOperWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GatherOperWidget)
{
    ui->setupUi(this);
}

GatherOperWidget::~GatherOperWidget()
{
    delete ui;
}

void GatherOperWidget::on_btnSetAddr_clicked()
{
    emit setGatherAddress(ui->editAddr->text().toInt());
}

void GatherOperWidget::on_btnReset_clicked()
{
    emit resetSensorCount(ui->editYBNum->text().toInt());
}
