#include "gatherpage.h"
#include "ui_gatherpage.h"

#include "../buttons/iconbutton.h"
#include "../base/faicon.h"

#include <QMessageBox>
GatherPage::GatherPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GatherPage)
{
    ui->setupUi(this);

    auto delBtn = new Ui::IconButton(FAIcon::instance()->icon(QString("trasho")), this);
    delBtn->setBackgroundEnabled(false);
    delBtn->setIconColor(Qt::red);
    delBtn->setIconSize(QSize(20, 20));

//    delBtn->setXRadius(del)

    ui->topLayout->addWidget(delBtn);
//    delBtn->setXRadius()
    connect(delBtn, &QAbstractButton::clicked, this, [=]{
        int ret = QMessageBox::information(this, tr("Delete All"), tr("Do you want to delete all items?"), QMessageBox::Ok, QMessageBox::Cancel);
        if (ret == QMessageBox::Ok) {
            ui->expandWidget->removeAllItem();
        }
    });

    connect(ui->expandWidget, &ExpandWidget::itemChanged, this, &GatherPage::itemChanged);
}

GatherPage::~GatherPage()
{
    delete ui;
}

void GatherPage::addExpandItem(ExpandWidgetItem *item)
{
    ui->expandWidget->addExpandItem(item);
}
