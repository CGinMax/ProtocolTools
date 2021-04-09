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

    qRegisterMetaType<QMultiMap<QString, SettingData*>>("const QMultiMap<QString, SettingData*>&");
    ui->setupUi(this);
    ui->mainToolBar->hide();

    m_mainTabs = new MainTabWidget(m_saveController, this);
    m_mainTabs->addTab(new TabPage(), tr("Default Page"));
    centralWidget()->layout()->addWidget(m_mainTabs);
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
