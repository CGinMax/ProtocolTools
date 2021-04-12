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
    , m_treeWidget(new ChannelTreeWidget())
    , m_mainSplitter(new QSplitter(this))
    , m_saveController(new SaveController(this))
{

    ui->setupUi(this);
    ui->mainToolBar->hide();
    qRegisterMetaType<QMultiMap<QString, SettingData*>>("const QMultiMap<QString, SettingData*>&");
    m_mainTabWidget = new MainTabWidget(m_saveController/*, this*/);

    m_mainTabController = new MainTabController(m_mainTabWidget, this);

    auto mainLayout = new QVBoxLayout(centralWidget());
    mainLayout->addWidget(m_mainSplitter);
    m_mainSplitter->setOrientation(Qt::Horizontal);
    m_mainSplitter->insertWidget(0, m_treeWidget);
    m_mainSplitter->insertWidget(1, m_mainTabWidget);
    m_mainSplitter->setCollapsible(0, false);
    m_mainSplitter->setCollapsible(1, false);
    m_mainSplitter->setStretchFactor(0, 1);
    m_mainSplitter->setStretchFactor(1, 3);

    connect(m_treeWidget, &ChannelTreeWidget::notifyItemSelected, m_mainTabController, &MainTabController::onNotifyItemSelected);
    connect(m_treeWidget, &ChannelTreeWidget::notifyAddNewChannel, m_mainTabController, &MainTabController::onNotifyAddNewChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyDeleteChannel, m_mainTabController, &MainTabController::onNotifyDeleteChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChangeName, m_mainTabController, &MainTabController::onNotifyChangeName);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStart, m_mainTabController, &MainTabController::onNotifyChannelStart);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStop, m_mainTabController, &MainTabController::onNotifyChannelStop);
    connect(m_mainTabController, &MainTabController::currentItemChanged, m_treeWidget, &ChannelTreeWidget::onCurrentItemChanged);

    connect(m_saveController, &SaveController::importFinish, this, &MainWindow::onImportFinish);

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
        auto item = m_treeWidget->addChannel(iter.key(), iter.value()->m_networkType);
        m_mainTabController->onNotifyAddNewChannel(item, QSharedPointer<SettingData>(iter.value()));
    }
}

void MainWindow::on_actionImport_triggered()
{
    m_saveController->onActionImportTriggered();
}

void MainWindow::on_actionSave_triggered()
{
    QMultiMap<QString, SettingData*> settingMap = m_mainTabWidget->getAllChildrenSetting();
    m_saveController->onActionSaveTriggered(settingMap);
}
