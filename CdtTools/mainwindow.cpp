#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QTabBar>
#include <QApplication>
#include <QDebug>
#include "ui/tabpage.h"
#include "ui/dialog/nameddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    m_mainTabs = new MainTabWidget(this);
    m_mainTabs->addTab(new TabPage(), tr("Default Page"));
    centralWidget()->layout()->addWidget(m_mainTabs);
    connect(m_mainTabs, &MainTabWidget::addNewPage, this, &MainWindow::onAddNewPage);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddNewPage()
{
    static int pageNum = 1;
    auto defaultName = QString("Page%1").arg(pageNum);
    NamedDialog dlg(defaultName);
    auto ret = dlg.exec();
    if (ret == QDialog::Accepted) {
        auto tabPage = new TabPage(m_mainTabs);
        m_mainTabs->addTab(tabPage, dlg.getNameString());
        if (!defaultName.compare(dlg.getNameString())) {
            pageNum++;
        }
    }

    m_mainTabs->backToBeforeIndex(ret == QDialog::Rejected);
}

