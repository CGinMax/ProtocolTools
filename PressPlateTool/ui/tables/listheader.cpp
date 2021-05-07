#include "listheader.h"
#include "ui_listheader.h"
#include <QPainter>
ListHeader::ListHeader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListHeader)
    , m_backgroundColor(QColor("#F7F7F8"))
{
    ui->setupUi(this);
//    auto txtId = new QLabel(tr("Id"), this);
//    auto txtAddr = new QLabel(tr("Address"), this);
//    auto txtCurrentStatus = new QLabel(tr("Current Status"), this);
//    auto txtConfigedStatus = new QLabel(tr("Configed Status"), this);
//    auto txtVersion = new QLabel(tr("Version"), this);
//    auto layout = new QHBoxLayout(this);
//    layout->addWidget(txtId);
//    layout->addWidget(txtAddr);
//    layout->addWidget(txtCurrentStatus);
//    layout->addWidget(txtConfigedStatus);
//    layout->addWidget(txtVersion);
}


void ListHeader::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(m_backgroundColor));
    painter.setPen(QPen(m_backgroundColor));
    painter.drawRoundedRect(rect(), 5, 5);
}

QColor ListHeader::backgroundColor() const
{
    return m_backgroundColor;
}

void ListHeader::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}
