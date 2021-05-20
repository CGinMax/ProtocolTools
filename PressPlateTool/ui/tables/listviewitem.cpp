#include "listviewitem.h"
#include "ui_listviewitem.h"
#include <QPainter>
#include <climits>
ListViewItem::ListViewItem(const QString &name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListViewItem)
{
    ui->setupUi(this);
    ui->txtName->setText(name);
    initWidget();
}

ListViewItem::ListViewItem(int address, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListViewItem)
{
    ui->setupUi(this);
    ui->txtName->setText(tr("Sensor #%1").arg(address));
    ui->editAddr->setValue(address);
    initWidget();
}

void ListViewItem::setName(const QString &name)
{
    ui->txtName->setText(name);
}

void ListViewItem::setAddress(int addr)
{
    ui->editAddr->setValue(addr);
}

int ListViewItem::address() const
{
    return ui->editAddr->value();
}

void ListViewItem::setCurrentStatus(int status)
{
    ui->txtCurStatus->setText(QString::number(status));
}

void ListViewItem::setConfigedStatus(int status)
{
    ui->txtSetStatus->setText(QString::number(status));
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

void ListViewItem::initWidget()
{
    ui->cbbChangeStatus->setCurrentIndex(2);
    ui->editAddr->setRange(0, INT_MAX);

    connect(ui->btnSetAddr, &QPushButton::clicked, this, [=]{ emit this->notifySetAddr(ui->editAddr->value()); });
    connect(ui->btnQueryStatus, &QPushButton::clicked, this, [=]{ emit this->notifyQueryStatus(ui->editAddr->value()); });
    connect(ui->btnQueryVersion, &QPushButton::clicked, this, [=]{ emit this->notifyQueryVersion(ui->editAddr->value()); });
    connect(ui->btnDelete, &QPushButton::clicked, this, &ListViewItem::notifyDelete);
}

void ListViewItem::on_cbbChangeStatus_currentIndexChanged(int index)
{
    int status =index;
    if (index != 0 && index != 1) {
        status = 0xFF;
    }
    emit statusChanged(ui->editAddr->value(), status);
}
