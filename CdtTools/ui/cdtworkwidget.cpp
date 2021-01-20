#include "cdtworkwidget.h"
#include "ui_cdtworkwidget.h"
#include "tables/ditablemodel.h"
#include "tables/aitablemodel.h"
#include "tables/delegates/comboboxdelegate.h"
#include "tables/delegates/digitlimitedelegate.h"
#include "../protocol/cdtprotocol.h"
#include "../protocol/cdtinteracte.h"
#include "../protocol/cdtcycle.h"
#include "../protocol/cdtexnr.h"
#include "../protocol/cdtexut.h"
#include "../common/threadpool.h"
#include "./dialog/ykdialog.h"
#include <QDebug>
#include <QThread>

CDTWorkWidget::CDTWorkWidget(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData, QWidget *parent)
    : QWidget(parent)
    , m_protocol(nullptr)
    , m_network(network)
    , m_floatBtnGroup(new FloatButtonGroup(this))
    , ui(new Ui::CDTWorkWidget)
{
    ui->setupUi(this);

    ui->horSplitter->setCollapsible(0, false);
    ui->horSplitter->setCollapsible(1, false);
    ui->vecSplitter->setCollapsible(0, false);
    ui->vecSplitter->setCollapsible(1, false);

    m_diModel = new DiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg->m_globalDiList, ui->viewDi);
    ui->viewDi->setModel(m_diModel);
    ui->viewDi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewDi->verticalHeader()->setVisible(false);
    ui->viewDi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewDi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto diDelegate = new ComboBoxDelegate(ui->viewDi);
    diDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, diDelegate);
//    ui->viewDi->openPersistentEditor(m_diModel->index(0, 2));

    m_aiModel = new AiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg->m_globalAiList, ui->viewAi);
    ui->viewAi->setModel(m_aiModel);
    ui->viewAi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewAi->verticalHeader()->setVisible(false);
    ui->viewAi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewAi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto aiDelegate = new DigitLimiteDelegate();
    ui->viewAi->setItemDelegateForColumn(2, aiDelegate);

    m_vyxModel = new DiTableModel({"Id", "Name", "Value"}, settingData->m_ptCfg->m_globalDiList, ui->viewVYx);
    ui->viewVYx->setModel(m_vyxModel);
    ui->viewVYx->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewVYx->verticalHeader()->setVisible(false);
    ui->viewVYx->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewVYx->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto vyxDelegate = new ComboBoxDelegate(ui->viewVYx);
    vyxDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, vyxDelegate);

    m_cbRandom = new QCheckBox(QStringLiteral("Value"), this);
    m_cbRandom->resize(60, 40);
    auto aiHorHeader = ui->viewAi->horizontalHeader();
    aiHorHeader->setIndexWidget(m_aiModel->index(0, 2), m_cbRandom);
    connect(&m_viewTimer, &QTimer::timeout, [this]{
        if (this->m_cbRandom->isChecked())
            m_aiModel->randomNumber();
        ui->viewAi->viewport()->update();
        ui->viewDi->viewport()->update();
    });
    m_viewTimer.start(2000);

    auto btn = new QPushButton(tr("clear"), this);
    connect(btn, &QPushButton::clicked, [this](){
        this->ui->textBrowser->clear();
    });
    m_floatBtnGroup->addButton(btn);
    m_floatBtnGroup->move(ui->textBrowser->x() + width() - 18 - m_floatBtnGroup->width(), ui->textBrowser->y() + 9);
    m_floatBtnGroup->raise();

    ThreadPool::instance()->run([&network, &settingData, this](){
        switch (settingData->m_ptCfg->m_protocol) {
        case eProtocol::CDTStandard:
            this->m_protocol = new CDTProtocol(network, settingData);
            break;
        case eProtocol::CDTGcInterace:
            this->m_protocol = new CDTInteracte(network, settingData);
            break;
        case eProtocol::CDTGcCycle:
            this->m_protocol = new CDTCycle(network, settingData);
            break;
        case eProtocol::CDTUt:
            this->m_protocol = new CDTExUt(network, settingData);
            break;
        case eProtocol::CDTNr:
            this->m_protocol = new CDTExNr(network, settingData);
            break;

        default:
            break;
        }
//        connect(this->m_protocol, &ProtocolBase::ykExecuteFinish, [this](const QString& msg){
//            qDebug("cdt work widget yk finished");
//            ui->textBrowser->append(msg);
//            ui->btnExecute->setEnabled(true);
//        });
        connect(this->m_protocol, &ProtocolBase::sendProtocolMsg, this, &CDTWorkWidget::recvMessage);
        connect(this, &CDTWorkWidget::stop, this->m_protocol, &ProtocolBase::stop, Qt::BlockingQueuedConnection);
        connect(this, &CDTWorkWidget::startYK, this->m_protocol, &ProtocolBase::startYK);
        connect(this, &CDTWorkWidget::reverseYx, this->m_protocol, &ProtocolBase::reverseYx);
        connect(this->m_protocol, &ProtocolBase::notifyYK, this, &CDTWorkWidget::onNotifyYK);
        this->m_protocol->start();
    });
}

CDTWorkWidget::~CDTWorkWidget()
{
    if (m_protocol) {
        delete m_protocol;
//        m_protocol->deleteLater();
        m_protocol = nullptr;
    }
    m_viewTimer.stop();
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

void CDTWorkWidget::resizeEvent(QResizeEvent *event)
{
    if ((width() + 36) <= m_floatBtnGroup->width() || height() <= m_floatBtnGroup->height()) {
        return ;
    }

    m_floatBtnGroup->move(ui->textBrowser->x() + width() - 18 - m_floatBtnGroup->width(), ui->textBrowser->y() + 9);
    QWidget::resizeEvent(event);
}

void CDTWorkWidget::recvMessage(const QString &msg)
{
    ui->textBrowser->append(msg);
}

void CDTWorkWidget::onNotifyYK(int ptId)
{
    QString info = QStringLiteral("是否对点%1进行变位").arg(ptId);
    YKDialog dialog(info, "Dialog");
    auto globalPos = mapToGlobal(QPoint(x(), y()));
    dialog.move(globalPos.x() + width() / 2 - dialog.width() / 2, globalPos.y() + height() / 2 - dialog.height() / 2);
    int ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        emit reverseYx(ptId);
    }
}

void CDTWorkWidget::on_btnExecute_clicked()
{
    emit startYK(ui->edPtId->value(), ui->cbbYKOper->currentIndex() > 0);
    qDebug("start yk");
//    ui->btnExecute->setEnabled(false);
}
