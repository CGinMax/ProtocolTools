#include "cdtworkwidget.h"
#include "ui_cdtworkwidget.h"
#include "tables/ditablemodel.h"
#include "tables/aitablemodel.h"
#include "tables/delegates/comboboxdelegate.h"
#include "tables/delegates/digitlimitedelegate.h"
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtinteracte.h"
#include "../common/threadpool.h"
#include <QDebug>
#include <QThread>

CDTWorkWidget::CDTWorkWidget(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData, QWidget *parent)
    : QWidget(parent)
    , m_protocol(nullptr)
    , m_network(network)
    , ui(new Ui::CDTWorkWidget)
{
    ui->setupUi(this);

    ui->horSplitter->setCollapsible(0, false);
    ui->horSplitter->setCollapsible(1, false);
    ui->vecSplitter->setCollapsible(0, false);
    ui->vecSplitter->setCollapsible(1, false);

    m_diModel = new DiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg, ui->viewDi);
    ui->viewDi->setModel(m_diModel);
    ui->viewDi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewDi->verticalHeader()->setVisible(false);
    ui->viewDi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewDi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto diDelegate = new ComboBoxDelegate(ui->viewDi);
    diDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, diDelegate);
//    ui->viewDi->openPersistentEditor(m_diModel->index(0, 2));

    m_aiModel = new AiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg, ui->viewAi);
    ui->viewAi->setModel(m_aiModel);
    ui->viewAi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewAi->verticalHeader()->setVisible(false);
    ui->viewAi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewAi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto aiDelegate = new DigitLimiteDelegate();
    ui->viewAi->setItemDelegateForColumn(2, aiDelegate);

    m_vyxModel = new DiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg, ui->viewVYx);
    ui->viewVYx->setModel(m_vyxModel);
    ui->viewVYx->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewVYx->verticalHeader()->setVisible(false);
    ui->viewVYx->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewVYx->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto vyxDelegate = new ComboBoxDelegate(ui->viewVYx);
    vyxDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, vyxDelegate);

    connect(&m_viewTimer, &QTimer::timeout, [=]{
        m_aiModel->randomNumber();
        ui->viewAi->viewport()->update();
        ui->viewDi->viewport()->update();
    });

    ThreadPool::instance()->run([&network, &settingData, this](){
        switch (settingData->m_ptCfg->m_protocol) {
        case eProtocol::CDTStandard:
            this->m_protocol = new CDTProtocol(network, settingData);
            break;
        case eProtocol::CDTUt:
            break;
        case eProtocol::CDTNr:
            break;
        case eProtocol::CDTGc:
            this->m_protocol = new CDTInteracte(network, settingData);
            break;
        default:
            break;
        }
        connect(this->m_protocol, &ProtocolBase::ykExecuteFinish, [=](){
            qDebug("cdt work widget yk finished");
            ui->btnExecute->setEnabled(true);
        });
        connect(this->m_protocol, &ProtocolBase::sendProtocolMsg, this, &CDTWorkWidget::recvMessage);
        connect(this, &CDTWorkWidget::stop, this->m_protocol, &ProtocolBase::stop);
        connect(this, &CDTWorkWidget::startYK, this->m_protocol, &ProtocolBase::startYK);
        this->m_protocol->start();
    });
}

CDTWorkWidget::~CDTWorkWidget()
{
    if (m_protocol) {
//        delete m_protocol;
        m_protocol->deleteLater();
        m_protocol = nullptr;
    }
}

void CDTWorkWidget::resetAiRandom(bool start)
{
    if (start) {
        m_viewTimer.start(1000);
    }
    else {
        m_viewTimer.stop();
    }
}

void CDTWorkWidget::stopCommunication()
{
    emit stop();
    m_network->close();
}

bool CDTWorkWidget::isConnection()
{
    return m_protocol->isConnection();
}

void CDTWorkWidget::recvMessage(const QString &msg)
{
    ui->textBrowser->append(msg);
}

void CDTWorkWidget::on_btnExecute_clicked()
{
    emit startYK(ui->edPtId->value(), ui->cbbYKOper->currentIndex() > 0);
    qDebug("start yk");
//    ui->btnExecute->setEnabled(false);
}
