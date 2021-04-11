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
    , m_stackedController(new StackedController(ui->pageStackedWidget, this))
{

    qRegisterMetaType<QMultiMap<QString, SettingData*>>("const QMultiMap<QString, SettingData*>&");
    m_mainTabs = new MainTabWidget(m_saveController/*, this*/);
    ui->setupUi(this);
    ui->mainToolBar->hide();

    m_mainSplitter->setOrientation(Qt::Horizontal);
    m_mainSplitter->insertWidget(0, m_treeWidget);
    m_mainSplitter->insertWidget(1, ui->pageStackedWidget);
    m_mainSplitter->setCollapsible(0, false);
    m_mainSplitter->setCollapsible(1, false);
    m_mainSplitter->setStretchFactor(0, 1);
    m_mainSplitter->setStretchFactor(1, 2);
    auto mainLayout = new QVBoxLayout(centralWidget());
    mainLayout->addWidget(m_mainSplitter);

    connect(m_treeWidget, &ChannelTreeWidget::notifyItemSelected, m_stackedController.data(), &StackedController::onNotifyItemSelected);
    connect(m_treeWidget, &ChannelTreeWidget::notifyAddNewChannel, m_stackedController.data(), &StackedController::onNotifyAddNewChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyDeleteChannel, m_stackedController.data(), &StackedController::onNotifyDeleteChannel);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChangeName, m_stackedController.data(), &StackedController::onNotifyChangeName);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStart, m_stackedController.data(), &StackedController::onNotifyChannelStart);
    connect(m_treeWidget, &ChannelTreeWidget::notifyChannelStop, m_stackedController.data(), &StackedController::onNotifyChannelStop);
    connect(m_stackedController.data(), &StackedController::addNewPage, m_mainTabs, &MainTabWidget::onAddNewPage);
    connect(m_stackedController.data(), &StackedController::removePage, m_mainTabs, &MainTabWidget::onRemovePage);
    connect(m_stackedController.data(), &StackedController::changePageName, m_mainTabs, &MainTabWidget::onChangePageName);
    ui->pageStackedWidget->insertWidget(0, m_mainTabs);
//    m_mainTabs->addTab(new TabPage(), tr("Default Page"));
//    centralWidget()->layout()->addWidget(m_mainTabs);
    connect(m_mainTabs, &MainTabWidget::addNewPage, this, &MainWindow::onAddNewPage);

    connect(m_saveController.data(), &SaveController::importFinish, this, &MainWindow::onImportFinish);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_mainTabs;
}

void MainWindow::onAddNewPage()
{
    static int pageNum = 1;
    auto defaultName = QString("Page%1").arg(pageNum);
    NamedDialog dlg(defaultName);
    auto ret = dlg.exec();
    if (ret == QDialog::Accepted) {
        auto tabPage = new TabPage(dlg.getNameString(), m_mainTabs);
        m_mainTabs->addTab(tabPage, dlg.getNameString());
        if (defaultName.compare(dlg.getNameString()) == 0) {
            pageNum++;
        }
    }

    m_mainTabs->backToBeforeIndex(ret == QDialog::Rejected);
}

void MainWindow::onImportFinish(const QMultiMap<QString, SettingData *> &settingMap)
{
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
        m_mainTabs->addTab(new TabPage(QSharedPointer<SettingData>(iter.value()), iter.key()), iter.key());
    }
}

void MainWindow::on_actionImport_triggered()
{
    m_saveController->onActionImportTriggered();
}

void MainWindow::on_actionSave_triggered()
{
    int tabCount = m_mainTabs->count();
    QMultiMap<QString, SettingData*> settingMap;
    for (int i = 0; i < tabCount - 1; i++) {
        auto tab = qobject_cast<TabPage*>(m_mainTabs->widget(i));
        tab->resetSettingData();
        settingMap.insert(tab->getPageName(), tab->getSettingData());
    }
    m_saveController->onActionSaveTriggered(settingMap);
}
