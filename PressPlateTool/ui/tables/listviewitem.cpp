#include "listviewitem.h"
#include "ui_listviewitem.h"
#include <QPainter>
#include <climits>

ListViewItem::ListViewItem(int address, YBSensorData *data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListViewItem)
    , m_data(data)
{
    ui->setupUi(this);
    ui->txtName->setText(tr("Sensor #%1").arg(address));
    ui->editAddr->setValue(address);
    initWidget();
}

void ListViewItem::setSensorData(YBSensorData *data)
{
    m_data = data;
}

YBSensorData *ListViewItem::sensorData()
{
    return m_data;
}

void ListViewItem::setName(const QString &name)
{
    ui->txtName->setText(name);
}

void ListViewItem::setAddress(int addr)
{
    m_data->setAddr(static_cast<uint8_t>(addr));
    ui->editAddr->setValue(addr);
}

int ListViewItem::address() const
{
    return ui->editAddr->value();
}

void ListViewItem::setCurrentStatus(int status)
{
    m_data->setCurrentStatus(YBStatus(status));
    ui->txtCurStatus->setText(QString::number(status));
}

void ListViewItem::setConfigedStatus(int status)
{
    m_data->setConfigedStatus(YBStatus(status));
    ui->txtSetStatus->setText(QString::number(status));
}

void ListViewItem::setHardwareVersion(const QString &version)
{
    m_data->setHardwareVersion(version);
    ui->txtHardwareVer->setText(version);
}

void ListViewItem::setSoftwareVersion(const QString &version)
{
    m_data->setSoftwareVersion(version);
    ui->txtSoftwareVer->setText(version);
}

void ListViewItem::setProductionDescription(const QString &desc)
{
    m_data->setProductDesc(desc);
    ui->txtProductDesc->setText(desc);
}

void ListViewItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(QColor(Qt::darkGray)));
    painter.drawRoundedRect(rect(), 3, 3);
}

void ListViewItem::initWidget()
{

    auto font = ui->txtName->font();
    font.setBold(true);
    font.setPixelSize(14);
    ui->txtName->setFont(font);
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
