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
