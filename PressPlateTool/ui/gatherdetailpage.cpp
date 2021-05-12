#include "gatherdetailpage.h"
#include "ui_gatherdetailpage.h"
#include "tables/listdelegate.h"
#include "tables/listheader.h"
#include "expand/gathercontroller.h"
#include "../protocol/ybprotocolchannel.h"

GatherDetailPage::GatherDetailPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GatherDetailPage)
{
    ui->setupUi(this);
    m_tablePage = new TablePage(ui->tabWidget);
    ui->tabWidget->addTab(m_tablePage, tr("Sensors"));
}

GatherDetailPage::~GatherDetailPage()
{
    delete ui;
}

void GatherDetailPage::onItemChanged(GatherController *controller)
{
    if (!m_gatherData.isNull()) {
        disconnect(m_gatherData.data(), &GatherData::nameChanged, this, &GatherDetailPage::onNameChanged);
        disconnect(m_gatherData.data(), &GatherData::addrChanged, this, &GatherDetailPage::onAddrChanged);
    }
    if (controller != nullptr) {
        m_tablePage->setProtocol(controller->protocol());
        m_gatherData = controller->gatherData();
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
