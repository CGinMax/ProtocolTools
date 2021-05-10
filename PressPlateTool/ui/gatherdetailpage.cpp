#include "gatherdetailpage.h"
#include "ui_gatherdetailpage.h"
#include "tables/listdelegate.h"
#include "tables/listheader.h"

GatherDetailPage::GatherDetailPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GatherDetailPage)
{
    ui->setupUi(this);
    auto header = new ListHeader(this);
    ui->tableLayout->addWidget(header);
    m_table = new YBTableView(this);
    auto delegate = new ListDelegate(qobject_cast<QAbstractListModel*>(m_table->model()), m_table);
    m_table->setItemDelegate(delegate);
    m_table->openPersistentEditor(m_table->model()->index(0, 0));
    m_table->openPersistentEditor(m_table->model()->index(1, 0));
    ui->tableLayout->addWidget(m_table);
    m_table->stackUnder(header);
}

GatherDetailPage::~GatherDetailPage()
{
    delete ui;
}

void GatherDetailPage::onItemChanged(const QSharedPointer<GatherData> &gatherData)
{
    if (!m_gatherData.isNull()) {
        disconnect(m_gatherData.data(), &GatherData::nameChanged, this, &GatherDetailPage::onNameChanged);
        disconnect(m_gatherData.data(), &GatherData::addrChanged, this, &GatherDetailPage::onAddrChanged);
    }
    if (!gatherData.isNull()) {
        m_gatherData = gatherData;
        ui->txtName->setText(m_gatherData->name());
        ui->txtAddress->setText(QString::number(m_gatherData->addr()));

        connect(m_gatherData.data(), &GatherData::nameChanged, this, &GatherDetailPage::onNameChanged);
        connect(m_gatherData.data(), &GatherData::addrChanged, this, &GatherDetailPage::onAddrChanged);

        ui->stackedWidget->setCurrentIndex(1);
        return ;
    }
    m_gatherData.reset(nullptr);
    ui->stackedWidget->setCurrentIndex(0);
}

void GatherDetailPage::onNameChanged(const QString &name)
{
    ui->txtName->setText(name);
}

void GatherDetailPage::onAddrChanged(int addr)
{
    ui->txtAddress->setText(QString::number(addr));
}
