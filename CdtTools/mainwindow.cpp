#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_page = new TabPage();
    centralWidget()->layout()->addWidget(m_page);

}

MainWindow::~MainWindow()
{
    delete ui;
}
