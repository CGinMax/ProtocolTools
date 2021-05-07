#include "listviewitem.h"
#include "ui_listviewitem.h"
#include <QPainter>
ListViewItem::ListViewItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListViewItem)
{
    ui->setupUi(this);
}

void ListViewItem::setId(const QString &id)
{
    ui->txtId->setText(id);
}

void ListViewItem::setVersion(const QString &version)
{
    ui->txtVersion->setText(version);
}


void ListViewItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(QColor(Qt::darkGray)));
//    painter.setPen(QPen(QColor("#F7F7F8")));
//    painter.drawLine(pos() + QPoint(5, height()), pos() + QPoint(width(), height()));
    painter.drawRoundedRect(rect(), 3, 3);
}
