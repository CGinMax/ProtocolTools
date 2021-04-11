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
    m_stackedController = new StackedController(ui->pageStackedWidget, this);
    m_tcpClientTabs = new MainTabWidget(m_saveController/*, this*/);
    m_tcpServerTabs = new MainTabWidget(m_saveController/*, this*/);
    m_udpTabs = new MainTabWidget(m_saveController/*, this*/);

    m_mainSplitter->setOrientation(Qt::Horizontal);
    m_mainSplitter->insertWidget(0, m_treeWidget);
    m_mainSplitter->insertWidget(1, ui->pageStackedWidget);
    m_mainSplitter->setCollapsible(0, false);
    m_mainSplitter->setCollapsible(1, false);
    m_mainSplitter->setStretchFactor(0, 1);
    m_mainSplitter->setStretchFactor(1, 2);
    auto mainLayout = new QVBoxLayout(centralWidget());
    mainLayout->addWidget(m_mainSplitter);

    connect(m_treeWidget, &ChannelTreeWidget::notifyItemSelected, m_stackedController, &StackedController::onNotifyItemSelected);
    connect(m_treeWidget, &ChannelTreeWidget::notifyAddNewChannel, m_stackedController, &StackedController::onNotifyAddNewChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyDeleteChannel, m_stackedController, &StackedController::onNotifyDeleteChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChangeName, m_stackedController, &StackedController::onNotifyChangeName);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStart, m_stackedController, &StackedController::onNotifyChannelStart);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStop, m_stackedController, &StackedController::onNotifyChannelStop);
    connect(m_stackedController, &StackedController::addNewPage, this, &MainWindow::onAddNewPage);
    connect(m_stackedController, &StackedController::removePage, this, &MainWindow::onRemovePage);
    connect(m_stackedController, &StackedController::changePageName, this, &MainWindow::onChangePageName);

    m_stackedController->insertInitWidget(m_treeWidget->tcpClientItem(), m_tcpClientTabs);
    m_stackedController->insertInitWidget(m_treeWidget->tcpServerItem(), m_tcpServerTabs);
    m_stackedController->insertInitWidget(m_treeWidget->udpItem(), m_udpTabs);

    connect(m_saveController, &SaveController::importFinish, this, &MainWindow::onImportFinish);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_saveController;
    delete m_stackedController;
}

//void MainWindow::onAddNewPage()
//{
//    static int pageNum = 1;
//    auto defaultName = QString("Page%1").arg(pageNum);
//    NamedDialog dlg(defaultName);
//    auto ret = dlg.exec();
//    if (ret == QDialog::Accepted) {
//        auto tabPage = new TabPage(dlg.getNameString(), m_mainTabs);
//        m_mainTabs->addTab(tabPage, dlg.getNameString());
//        if (defaultName.compare(dlg.getNameString()) == 0) {
//            pageNum++;
//        }
//    }

//    m_mainTabs->backToBeforeIndex(ret == QDialog::Rejected);
//}

void MainWindow::onImportFinish(const QMultiMap<QString, SettingData *> &settingMap)
{
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
//        m_mainTabs->addTab(new TabPage(QSharedPointer<SettingData>(iter.value()), iter.key()), iter.key());
    }
}

void MainWindow::onAddNewPage(TabPage *page, eNetworkType type)
{
    switch (type) {
    case eNetworkType::eTcpClient:
        m_tcpClientTabs->onAddNewPage(page);
        break;
    case eNetworkType::eTcpServer:
        m_tcpServerTabs->onAddNewPage(page);
        break;
    case eNetworkType::eUdp:
        m_udpTabs->onAddNewPage(page);
        break;
    default:
        break;
    }
}

void MainWindow::onRemovePage(TabPage *page, eNetworkType type)
{
    switch (type) {
    case eNetworkType::eTcpClient:
        m_tcpClientTabs->onRemovePage(page);
        break;
    case eNetworkType::eTcpServer:
        m_tcpServerTabs->onRemovePage(page);
        break;
    case eNetworkType::eUdp:
        m_udpTabs->onRemovePage(page);
        break;
    default:
        break;
    }
}

void MainWindow::onChangePageName(TabPage *page, eNetworkType type)
{
    switch (type) {
    case eNetworkType::eTcpClient:
        m_tcpClientTabs->onChangePageName(page);
        break;
    case eNetworkType::eTcpServer:
        m_tcpServerTabs->onChangePageName(page);
        break;
    case eNetworkType::eUdp:
        m_udpTabs->onChangePageName(page);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionImport_triggered()
{
    m_saveController->onActionImportTriggered();
}

void MainWindow::on_actionSave_triggered()
{
    QMultiMap<QString, SettingData*> settingMap;
    settingMap.unite(m_tcpClientTabs->getAllChildrenSetting());
    settingMap.unite(m_tcpServerTabs->getAllChildrenSetting());
    settingMap.unite(m_udpTabs->getAllChildrenSetting());
    m_saveController->onActionSaveTriggered(settingMap);
}
