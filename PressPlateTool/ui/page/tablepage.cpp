#include "tablepage.h"
#include "ui_tablepage.h"

TablePage::TablePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TablePage)
    , m_protocol(nullptr)
{
    ui->setupUi(this);
    m_table = new YBTableView(this);
    ui->mainLayout->addWidget(m_table);

    connect(ui->btnAddOne, &QAbstractButton::clicked, this, [=]{
        this->m_table->addYBSensor(1);
    });
    connect(ui->btnAddMulti, &QAbstractButton::clicked, this, [=]{
        this->m_table->addYBSensor(10);
    });
    connect(ui->btnDeleteAll, &QAbstractButton::clicked, this, [=]{
        this->m_table->clearAllYBSensor();
    });
}

TablePage::~TablePage()
{
    delete ui;
}

void TablePage::setProtocol(YBProtocolChannel *protocol)
{
    m_protocol = protocol;
}
