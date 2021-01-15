#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QScreen>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->mainToolBar->hide();

    m_addTabBtn = new QPushButton("+", this);
    connect(m_addTabBtn, &QPushButton::clicked, this, &MainWindow::onAddTabPage);
    ui->tabWidget->setCornerWidget(m_addTabBtn, Qt::TopRightCorner);
    ui->tabWidget->setTabsClosable(true);

    auto tabPage = new TabPage(ui->tabWidget);
    ui->tabWidget->addTab(tabPage, "Page1");

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddTabPage()
{
    static int pageNum = 2;
    auto tabPage = new TabPage(ui->tabWidget);
    ui->tabWidget->addTab(tabPage, QString("Page%1").arg(pageNum));

}
