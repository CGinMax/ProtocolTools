#include "cdtworkwidget.h"
#include "ui_cdtworkwidget.h"
#include "tables/ditablemodel.h"
#include "tables/aitablemodel.h"
#include "tables/delegates/comboboxdelegate.h"
#include "tables/delegates/digitlimitedelegate.h"
#include "tables/diheaderview.h"
#include "tables/aiheaderview.h"
#include "../protocol/standard/cdtprotocol.h"
#include "../protocol/interacte/cdtinteracte.h"
#include "../protocol/cycle/cdtstandard.h"
#include "../protocol/nr/cdtexnr.h"
#include "../protocol/ut/cdtexut.h"
#include "../protocol/nrudp/nrudpprotocol.h"
#include "../common/threadpool.h"
#include "../common/util.h"
#include "dialog/ykdialog.h"
#include <QDebug>
#include <QMenu>
#include <QThread>

#include <climits>

CDTWorkWidget::CDTWorkWidget(const QSharedPointer<NetworkBase> &network, const QSharedPointer<SettingData> &settingData, QWidget *parent)
    : QWidget(parent)
    , m_protocol(nullptr)
    , m_network(network)
    , ui(new Ui::CDTWorkWidget)
{
    ui->setupUi(this);

    ui->vecSplitter->setCollapsible(0, false);
    ui->vecSplitter->setCollapsible(1, false);
    ui->edPtId->setRange(0, INT_MAX);

    m_diModel = new DiTableModel({tr("IO"), tr("Name"), tr("Value")}, settingData->m_ptCfg->m_globalDiList, ui->viewDi);
    auto diHorHeader = new DiHeaderView(Qt::Horizontal, ui->viewDi);
    diHorHeader->setMinimumHeight(30);
    connect(diHorHeader, &DiHeaderView::notifyAllChanged, m_diModel, &DiTableModel::onNotifyAllChanged);

    ui->viewDi->setHorizontalHeader(diHorHeader);
    ui->viewDi->setModel(m_diModel);
    ui->viewDi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewDi->verticalHeader()->setVisible(false);
    ui->viewDi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewDi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto diDelegate = new ComboBoxDelegate(ui->viewDi);
    diDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewDi->setItemDelegateForColumn(2, diDelegate);
    for (int i = 0; i < m_diModel->rowCount(QModelIndex()); i++) {
        ui->viewDi->openPersistentEditor(m_diModel->index(i, 2));
    }
    connect(diDelegate, &ComboBoxDelegate::delegateValueChanged, this, [=](){
        QString protocolString;
        if (settingData->m_ptCfg->m_protocol == eProtocol::NRUdp) {
            protocolString = Util::bytes2String(NrUdpProtocol::buildYXProtocol(settingData));
        }
        else {
            protocolString = Util::bytes2String(CDTProtocol::buildYXProtocol(settingData), 6);
        }
        ui->editDiProtocol->clear();
        ui->editDiProtocol->appendPlainText(protocolString);
    });
    emit diDelegate->delegateValueChanged();

    m_aiModel = new AiTableModel({tr("IO"), tr("Name"), tr("Value")}, settingData->m_ptCfg->m_globalAiList, ui->viewAi);
    auto aiHorHeader = new AiHeaderView(Qt::Horizontal, ui->viewAi);
    aiHorHeader->setMinimumHeight(30);
    connect(aiHorHeader, &AiHeaderView::notifyIsRandom, m_aiModel, &AiTableModel::onNotifyRandom);
    ui->viewAi->setHorizontalHeader(aiHorHeader);
    ui->viewAi->setModel(m_aiModel);
    ui->viewAi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewAi->horizontalHeader()->setMinimumHeight(30);
    ui->viewAi->verticalHeader()->setVisible(false);
    ui->viewAi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewAi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto aiDelegate = new DigitLimiteDelegate();
    ui->viewAi->setItemDelegateForColumn(2, aiDelegate);
    for (int i = 0; i < m_aiModel->rowCount(QModelIndex()); i++) {
        ui->viewAi->openPersistentEditor(m_aiModel->index(i, 2));
    }
    connect(aiDelegate, &DigitLimiteDelegate::delegateValueChanged, this, [=](){
        QString protocolString;
        if (settingData->m_ptCfg->m_protocol == eProtocol::NRUdp) {
            protocolString = Util::bytes2String(NrUdpProtocol::buildYCProtocol(settingData));
        }
        else {
            protocolString = Util::bytes2String(CDTProtocol::buildYCProtocol(settingData), 6);
        }
        ui->editAiProtocol->clear();
        ui->editAiProtocol->appendPlainText(protocolString);
    });
    emit aiDelegate->delegateValueChanged();

    m_vdiModel = new DiTableModel({tr("IO"), tr("Name"), tr("Value")}, settingData->m_ptCfg->m_globalVDiList, ui->viewVDi);
    auto vdiHorHeader = new DiHeaderView(Qt::Horizontal, ui->viewVDi);
    vdiHorHeader->setMinimumHeight(30);
    connect(vdiHorHeader, &DiHeaderView::notifyAllChanged, m_vdiModel, &DiTableModel::onNotifyAllChanged);
    ui->viewVDi->setHorizontalHeader(vdiHorHeader);
    ui->viewVDi->setModel(m_vdiModel);
    ui->viewVDi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->viewVDi->verticalHeader()->setVisible(false);
    ui->viewVDi->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->viewVDi->setSelectionBehavior(QAbstractItemView::SelectItems);
    auto vyxDelegate = new ComboBoxDelegate(ui->viewVDi);
    vyxDelegate->setItems({QStringLiteral("分"), QStringLiteral("合")});
    ui->viewVDi->setItemDelegateForColumn(2, vyxDelegate);
    for (int i = 0; i < m_vdiModel->rowCount(QModelIndex()); i++) {
        ui->viewVDi->openPersistentEditor(m_vdiModel->index(i, 2));
    }
    connect(vyxDelegate, &ComboBoxDelegate::delegateValueChanged, this, [=](){
        QString protocolString;
        if (settingData->m_ptCfg->m_protocol == eProtocol::NRUdp) {
            protocolString = Util::bytes2String(NrUdpProtocol::buildVYXProtocol(settingData));
        }
        else {
            protocolString = Util::bytes2String(CDTProtocol::buildVYXProtocol(settingData), 6);
        }
        ui->editVDiProtocol->clear();
        ui->editVDiProtocol->appendPlainText(protocolString);
    });
    emit vyxDelegate->delegateValueChanged();

    connect(&m_viewTimer, &QTimer::timeout, this, [this]{
        m_aiModel->randomNumber();
        ui->viewAi->viewport()->update();
        ui->viewDi->viewport()->update();
        emit m_diModel->dataChanged(m_diModel->index(0, 2), m_diModel->index(m_diModel->rowCount(QModelIndex()), 2));
        emit m_aiModel->dataChanged(m_aiModel->index(0, 2), m_aiModel->index(m_aiModel->rowCount(QModelIndex()), 2));
        emit m_vdiModel->dataChanged(m_vdiModel->index(0, 2), m_vdiModel->index(m_vdiModel->rowCount(QModelIndex()), 2));
    });

    ui->edPtId->setMinimum(settingData->m_ptCfg->m_globalDiList->first()->io());

    ui->textYkInfo->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textYkInfo, &QPlainTextEdit::customContextMenuRequested, this, &CDTWorkWidget::onPlainTextContextMenuRequested);
    ui->textBrowser->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textBrowser, &QTextBrowser::customContextMenuRequested, this, &CDTWorkWidget::onTextBrowserContextMenuRequested);

    connect(ui->btnLock, &QPushButton::clicked, this, [=]{
        emit this->lockOrUnlock(true);
    });
    connect(ui->btnUnlock, &QPushButton::clicked, this, [=]{
        emit this->lockOrUnlock(false);
    });
}

CDTWorkWidget::~CDTWorkWidget()
{
    if (m_protocol != nullptr) {
        delete m_protocol;
        m_protocol = nullptr;
    }
    m_viewTimer.stop();
}

void CDTWorkWidget::startCommunication(const QSharedPointer<SettingData> &settingData)
{
    ThreadPool::instance()->run([&settingData, this](){
        switch (settingData->m_ptCfg->m_protocol) {
        case eProtocol::CDTStandardary:
            this->m_protocol = new CDTStandard(this->m_network, settingData);
            break;
        case eProtocol::CDTGcInterace:
            this->m_protocol = new CDTInteracte(this->m_network, settingData);
            break;
        case eProtocol::CDTUt:
            this->m_protocol = new CDTExUt(this->m_network, settingData);
            break;
        case eProtocol::CDTNr:
            this->m_protocol = new CDTExNr(this->m_network, settingData);
            break;
        case eProtocol::NRUdp:
            this->m_protocol = new NrUdpProtocol(this->m_network, settingData);
            break;
        default:
            break;
        }
        connect(this->m_protocol, &ProtocolBase::sendProtocolContent, this, &CDTWorkWidget::recvProtocolContent);
        connect(this->m_protocol, &ProtocolBase::sendYKMsg, this, &CDTWorkWidget::recvYKMsg);
        connect(this, &CDTWorkWidget::stop, this->m_protocol, &ProtocolBase::stop, Qt::BlockingQueuedConnection);
        connect(this, &CDTWorkWidget::lockOrUnlock, this->m_protocol, &ProtocolBase::lockOrUnlock);
        connect(this, &CDTWorkWidget::startYK, this->m_protocol, &ProtocolBase::sendYk);
        connect(this, &CDTWorkWidget::reverseYx, this->m_protocol, &ProtocolBase::onReverseYx);
        connect(this->m_protocol, &ProtocolBase::notifyYK, this, &CDTWorkWidget::onNotifyYK);
        connect(this->m_network.data(), &NetworkBase::disconnected, this, &CDTWorkWidget::disconnected);
        this->m_protocol->initStrategy();
        this->m_protocol->start();
    });

    m_viewTimer.start(2000);
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

    m_viewTimer.stop();
}

bool CDTWorkWidget::isConnection()
{
    return m_protocol->isConnection();
}

void CDTWorkWidget::recvProtocolContent(const QString &msg)
{
    ui->textBrowser->append(msg);
}

void CDTWorkWidget::recvYKMsg(const QString &msg)
{
    ui->textYkInfo->appendPlainText(msg);
}

void CDTWorkWidget::onNotifyYK(int ptId)
{
    QString info = QStringLiteral("是否对点%1进行变位").arg(ptId);
    YKDialog dialog(info, this);

    auto globalPos = mapToGlobal(QPoint(x(), y()));
    dialog.move(globalPos.x() + width() / 2 - dialog.width() / 2, globalPos.y() + height() / 2 - dialog.height() / 2);

    int ret = dialog.exec();
    emit reverseYx(ptId, ret == QDialog::Accepted);
}

void CDTWorkWidget::on_btnExecute_clicked()
{
    emit startYK(ui->edPtId->value(), ui->cbbYKOper->currentIndex() > 0);

}

void CDTWorkWidget::onPlainTextContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu menu;
    menu.addAction(tr("Clear"), this, [this]{
        this->ui->textYkInfo->clear();
    });
    menu.exec(QCursor::pos());
}

void CDTWorkWidget::onTextBrowserContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu menu;
    menu.addAction(tr("Clear"), this, [this]{
        this->ui->textBrowser->clear();
    });
    menu.exec(QCursor::pos());
}
