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
