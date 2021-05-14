#include "tablepage.h"
#include "ui_tablepage.h"
#include <QScrollArea>

TablePage::TablePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TablePage)
    , m_currentIndex(0)
    , m_currentConfAddr(1)
    , m_protocol(nullptr)
{
    ui->setupUi(this);
    auto scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString("scrollArea"));
    scrollArea->setStyleSheet(QLatin1String("QScrollArea#scrollArea{border: transparent; background-color: white;}"));
    m_table = new YBTableView(this);
    scrollArea->setWidget(m_table);
    scrollArea->setWidgetResizable(true);

    ui->editBegin->setRange(0x01, 0x7E);
    ui->editEnd->setRange(0x01, 0x7E);
    ui->mainLayout->addWidget(scrollArea);

    connect(ui->btnAddOne, &QAbstractButton::clicked, this, [=]{
        this->m_table->addYBSensor(1);
    });
    connect(ui->btnAddMulti, &QAbstractButton::clicked, this, [=]{
        this->m_table->addYBSensor(10);
    });
    connect(ui->btnDeleteAll, &QAbstractButton::clicked, this, [=]{
        this->m_table->deleteAllYBSensor();
    });

    connect(m_table, &YBTableView::setSensorAddr, this, &TablePage::onSetSensorAddr);
    connect(m_table, &YBTableView::querySensorStatus, this, &TablePage::onQuerySensorStatus);
    connect(m_table, &YBTableView::querySensorVersion, this, &TablePage::onQuerySensorVersion);
    connect(m_table, &YBTableView::changeSensorStatus, this, &TablePage::onChangeSensorStatus);
}

TablePage::~TablePage()
{
    delete ui;
}

void TablePage::setProtocol(YBProtocolChannel *protocol)
{
    m_protocol = protocol;
}

void TablePage::confAddrRecursion()
{
    if (m_currentConfAddr > ui->editEnd->value()) {
        qDebug("set address finish");
        on_btnQueryAllStatus_clicked();
        return;
    }
    auto reply = m_protocol->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(m_currentConfAddr));
    YBProtocolChannel::processReply(reply, [=]{
        if (reply->result->success()) {
            this->m_table->setListItemAddr(this->m_currentIndex, this->m_currentConfAddr);
            this->m_currentIndex++;
            this->m_currentConfAddr++;
            this->confAddrRecursion();
        } else {
            qDebug("sensor set address failed");
        }
    }, [=]{qDebug("sensor set address error");});
}

void TablePage::queryStatusRecursion()
{
    if (m_currentIndex >= m_table->sensorCount()) {
        qDebug("query status finish");
        return ;
    }
    auto reply = m_protocol->queryStatus(static_cast<uint16_t>(m_table->getListItemAddr(m_currentIndex)));
    YBProtocolChannel::processReply(reply, [=]{
        this->m_table->setListItemStatus(m_currentIndex, reply->result->currentStatusCode(), reply->result->configedStatusCode());
        this->m_currentIndex++;
        this->queryStatusRecursion();
    }, [=]{qDebug("query status error");});
}

void TablePage::queryVersionRecursion()
{
    if (m_currentIndex >= m_table->sensorCount()) {
        qDebug("query version finish");
        return ;
    }
    auto reply = m_protocol->queryVersion(eYBFrameType::YBSensor, static_cast<uint8_t>(m_table->getListItemAddr(m_currentIndex)));
    YBProtocolChannel::processReply(reply, [=]{
        this->m_table->setListItemVersion(this->m_currentIndex
                                    , QString::fromStdString(reply->result->hardwareVersion())
                                    , QString::fromStdString(reply->result->softwareVersion())
                                    , QString::fromStdString(reply->result->productDescript()));
        this->m_currentIndex++;
        this->queryVersionRecursion();
    }, [=]{qDebug("sensor query version error");});
}

void TablePage::onSetSensorAddr(int index, int addr)
{
    auto reply = m_protocol->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr));
    YBProtocolChannel::processReply(reply, [=]{
        if (reply->result->success()) {
            this->m_table->setListItemAddr(index, addr);
        } else {
            qDebug("set sensor address failed!");
        }
    }, [=]{ qDebug("set sensor address error!");});
}

void TablePage::onQuerySensorStatus(int index, int addr)
{
    auto reply = m_protocol->queryStatus(static_cast<uint16_t>(addr));
    YBProtocolChannel::processReply(reply, [=]{
        this->m_table->setListItemStatus(index, reply->result->currentStatusCode(), reply->result->configedStatusCode());
    }, [=]{ qDebug("query sensor status error!");});
}

void TablePage::onQuerySensorVersion(int index, int addr)
{
    auto reply = m_protocol->queryVersion(eYBFrameType::YBSensor, static_cast<uint16_t>(addr));
    YBProtocolChannel::processReply(reply, [=]{
        this->m_table->setListItemVersion(index
                                          , QString::fromStdString(reply->result->hardwareVersion())
                                          , QString::fromStdString(reply->result->softwareVersion())
                                          , QString::fromStdString(reply->result->productDescript()));
    }, [=]{ qDebug("query sensor version error!");});
}

void TablePage::onChangeSensorStatus(int index, int addr, int status)
{
    auto reply = m_protocol->setStatus(static_cast<uint8_t>(status & 0xFF), static_cast<uint16_t>(addr));
    YBProtocolChannel::processReply(reply, [=]{
        if (reply->result->success()) {
            this->m_table->setListItemConfigedStatus(index, static_cast<uint8_t>(status & 0xFF));
        } else {
            qDebug("change status failed!");
        }
    }, [=]{qDebug("change status error!");});
}

void TablePage::on_btnConfAllAddr_clicked()
{
    m_currentIndex = 0;
    m_currentConfAddr = ui->editBegin->value();
    confAddrRecursion();
}

void TablePage::on_btnQueryAllStatus_clicked()
{
    m_currentIndex = 0;
    queryStatusRecursion();
}

void TablePage::on_btnQueryAllVer_clicked()
{
    m_currentIndex = 0;
    queryVersionRecursion();
}

void TablePage::on_editBegin_valueChanged(int arg1)
{
    ui->editEnd->setRange(arg1, arg1 + m_table->sensorCount());
}
