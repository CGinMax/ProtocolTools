#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>

#include <QDebug>
#include "ui/tabpage.h"
#include "ui/dialog/nameddialog.h"
#include "common/threadpool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_saveController(new SaveController(this))
{

    ui->setupUi(this);
    m_mainTabController = new MainTabController(ui->mainTabWidget, this);

    ui->splitter->setChildrenCollapsible(false);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 10);
    ui->treeWidget->setHeaderLabel(tr("Channel"));
    ui->mainToolBar->addAction(QIcon(":/icon/resources/export-icon.png"), tr("Save"), this, &MainWindow::on_actionSave_triggered);
    ui->mainToolBar->addAction(QIcon(":/icon/resources/import-icon.png"), tr("Import"), this, &MainWindow::on_actionImport_triggered);
    ui->mainToolBar->addSeparator();
    m_start = ui->mainToolBar->addAction(QIcon(":/icon/resources/start-icon.png"),tr("Start"), ui->treeWidget, &ChannelTreeWidget::onStart);
    m_close = ui->mainToolBar->addAction(QIcon(":/icon/resources/close-icon.png"), tr("Close"), ui->treeWidget, &ChannelTreeWidget::onStop);
    m_closeAll =  ui->mainToolBar->addAction(QIcon(":/icon/resources/close-all-icon.png"), tr("Close All"), ui->treeWidget, &ChannelTreeWidget::onStopAll);
    m_delete = ui->mainToolBar->addAction(QIcon(":/icon/resources/delete-icon.png"), tr("Delete"), ui->treeWidget, &ChannelTreeWidget::onDelete);
    m_deleteAll = ui->mainToolBar->addAction(QIcon(":/icon/resources/delete-all-icon.png"), tr("Delete All"), ui->treeWidget, &ChannelTreeWidget::onDeleteAllChild);

    qRegisterMetaType<QMultiMap<QString, SettingData*>>("const QMultiMap<QString, SettingData*>&");

    connect(ui->treeWidget, &ChannelTreeWidget::itemChangeSelect, this, &MainWindow::onItemChangeSelect);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyItemSelected, m_mainTabController, &MainTabController::onNotifyItemSelected);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyAddNewChannel, m_mainTabController, &MainTabController::onNotifyAddNewChannel);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyDeleteChannel, m_mainTabController, &MainTabController::onNotifyDeleteChannel);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyChangeName, m_mainTabController, &MainTabController::onNotifyChangeName);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyChannelStart, m_mainTabController, &MainTabController::onNotifyChannelStart);
    connect(ui->treeWidget, &ChannelTreeWidget::notifyChannelStop, m_mainTabController, &MainTabController::onNotifyChannelStop);
    connect(m_mainTabController, &MainTabController::currentItemChanged, ui->treeWidget, &ChannelTreeWidget::onCurrentItemChanged);
    connect(m_mainTabController, &MainTabController::hasTabPage, this, [this](bool hasPage){
        ui->stackedWidget->setCurrentIndex(hasPage ? static_cast<int>(StackPage::TabWidgetPage)
                                                   : static_cast<int>(StackPage::EmptyPage));
    });
    connect(m_saveController, &SaveController::importFinish, this, &MainWindow::onImportFinish);

    onItemChangeSelect(false);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_saveController;
    delete m_mainTabController;
}

void MainWindow::onImportFinish(const QMultiMap<QString, SettingData *> &settingMap)
{
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
        auto item = ui->treeWidget->addChannel(iter.key(), iter.value()->m_networkType);
        m_mainTabController->onNotifyAddNewChannel(item, QSharedPointer<SettingData>(iter.value()));
    }
    ui->treeWidget->autoSelectFirstItem();
}

void MainWindow::onItemChangeSelect(bool isChild)
{

    m_start->setEnabled(isChild);
    m_close->setEnabled(isChild);
    m_delete->setEnabled(isChild);
    m_closeAll->setEnabled(!isChild);
    m_deleteAll->setEnabled(!isChild);
    if (isChild) {
    }
}

void MainWindow::on_actionImport_triggered()
{
    m_saveController->onActionImportTriggered();
}

void MainWindow::on_actionSave_triggered()
{
    QMultiMap<QString, SettingData*> settingMap = ui->mainTabWidget->getAllChildrenSetting();
    m_saveController->onActionSaveTriggered(settingMap);
}
