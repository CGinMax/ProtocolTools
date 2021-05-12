#include "listviewitem.h"
#include "ui_listviewitem.h"
#include <QPainter>
#include <climits>
ListViewItem::ListViewItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListViewItem)
{
    ui->setupUi(this);
    ui->editAddr->setRange(0, INT_MAX);

    connect(ui->btnQueryStatus, &QPushButton::clicked, this, &ListViewItem::notifyQueryStatus);
    connect(ui->btnQueryVersion, &QPushButton::clicked, this, &ListViewItem::notifyQueryVersion);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ListViewItem::notifyDelete);
}

void ListViewItem::setName(const QString &name)
{
    ui->txtName->setText(name);
}

void ListViewItem::setAddress(int addr)
{
    ui->editAddr->setValue(addr);
}

void ListViewItem::setHardwareVersion(const QString &version)
{
    ui->txtHardwareVer->setText(version);
}

void ListViewItem::setSoftwareVersion(const QString &version)
{
    ui->txtSoftwareVer->setText(version);
}

void ListViewItem::setProductionDescription(const QString &desc)
{
    ui->txtProductDesc->setText(desc);
}

void ListViewItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(QColor(Qt::darkGray)));
//    painter.setPen(QPen(QColor("#F7F7F8")));
//    painter.drawLine(pos() + QPoint(5, height()), pos() + QPoint(width(), height()));
    painter.drawRoundedRect(rect(), 3, 3);
}

void ListViewItem::on_btnSetAddr_clicked()
{
    emit notifySetAddr(ui->editAddr->value());
}
