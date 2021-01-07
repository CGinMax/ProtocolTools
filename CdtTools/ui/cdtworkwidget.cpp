#include "cdtworkwidget.h"
#include "ui_cdtworkwidget.h"
#include "tables/ditablemodel.h"
#include "tables/aitablemodel.h"
#include "tables/delegates/comboboxdelegate.h"
#include "tables/delegates/digitlimitedelegate.h"
#include <QDebug>

CDTWorkWidget::CDTWorkWidget(const QSharedPointer<PtCfg>& ptcfg, ProtocolBase *protocol, QWidget *parent)
    : QWidget(parent)
    , m_protocol(protocol)
    , ui(new Ui::CDTWorkWidget)
{
    ui->setupUi(this);

    ui->horSplitter->setCollapsible(0, false);
    ui->horSplitter->setCollapsible(1, false);
    ui->vecSplitter->setCollapsible(0, false);
    ui->vecSplitter->setCollapsible(1, false);

    m_diModel = new DiTableModel({"Id", "Name", "Value"}, ptcfg, ui->viewDi);
    ui->viewDi->setModel(m_diModel);
    ui->viewDi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewDi->verticalHeader()->setVisible(false);
    ui->viewDi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewDi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto diDelegate = new ComboBoxDelegate(ui->viewDi);
    diDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, diDelegate);


    m_aiModel = new AiTableModel({"Id", "Name", "Value"}, ptcfg, ui->viewAi);
    ui->viewAi->setModel(m_aiModel);
    ui->viewAi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewAi->verticalHeader()->setVisible(false);
    ui->viewAi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewAi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto aiDelegate = new DigitLimiteDelegate();
    ui->viewAi->setItemDelegateForColumn(2, aiDelegate);

    m_vyxModel = new DiTableModel({"Id", "Name", "Value"}, ptcfg, ui->viewVYx);
    ui->viewVYx->setModel(m_vyxModel);
    ui->viewVYx->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewVYx->verticalHeader()->setVisible(false);
    ui->viewVYx->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewVYx->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto vyxDelegate = new ComboBoxDelegate(ui->viewVYx);
    vyxDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, vyxDelegate);

    connect(&m_aiTimer, &QTimer::timeout, [=]{
        m_aiModel->randomNumber();
        ui->viewAi->viewport()->update();
    });
}

CDTWorkWidget::~CDTWorkWidget()
{
    if (m_protocol) {
        delete m_protocol;
        m_protocol = nullptr;
    }
}

void CDTWorkWidget::resetAiRandom(bool start)
{
    if (start) {
        m_aiTimer.start(2000);
    }
    else {
        m_aiTimer.stop();
    }
}
