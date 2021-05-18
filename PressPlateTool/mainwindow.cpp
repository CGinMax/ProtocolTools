﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

#include "ui/expand/expandwidgetitem.h"
#include "ui/expand/expandwidget.h"
#include "ui/dialogs/serialportdialog.h"
#include "ui/buttons/iconbutton.h"

int MainWindow::createNo = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("QWidget#centralWidget{background-color:#F0F3F4;}");
    ui->mainSplitter->setStretchFactor(0, 1);
    ui->mainSplitter->setStretchFactor(1, 2);
    ui->mainSplitter->setStyleSheet("QSplitter::handle{background-color:lightgray;}");
    connect(ui->expandWidget, &ExpandWidget::itemChanged, ui->gatherDetailPage, &GatherDetailPage::onItemChanged);

    for (int i = 0; i < 1; i++) {
//        ui->expandWidget->addExpandItem(ExpandWidget::createExpandWidget(tr("untitled"), 8));
//        auto tile = new ExpandTile("title");
//        auto widget = new ExpandWidgetItem(tile);
//        widget->setBorderRadius(5);
//        widget->setContentWidget(new GatherOperWidget(widget));
//        ui->expandWidget->addExpandItem(widget);
    }

    m_fabMenu = new FabCircularMenu(this);
    auto oneBtn = new Ui::IconButton(QIcon(":/icons/add-one.png"), this);
    oneBtn->setIconSize(QSize(16, 16));
    oneBtn->setCheckable(false);
    oneBtn->resize(36, 36);
    oneBtn->setXRadius(oneBtn->width())->setYRadius(oneBtn->height());
    auto multiBtn = new Ui::IconButton(QIcon(":/icons/add-multi.png"), this);
    multiBtn->setIconSize(QSize(16, 16));
    multiBtn->setCheckable(false);
    multiBtn->resize(36, 36);
    multiBtn->setXRadius(multiBtn->width())->setYRadius(multiBtn->height());

    m_fabMenu->addButton(oneBtn);
    m_fabMenu->addButton(multiBtn);
    connect(oneBtn, &QAbstractButton::clicked, this, &MainWindow::onNotifyAddOne);
    connect(multiBtn, &QAbstractButton::clicked, this, &MainWindow::onNotifyAddMulti);


    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNotifyAddOne()
{
    SerialPortDialog dialog(false, this);
    if(dialog.exec() == QDialog::Accepted) {
        m_fabMenu->setChecked(false);
        ui->expandWidget->addExpandItem(ExpandWidget::createExpandWidget(dialog.portParam(), tr("Gather%1").arg(createNo++), 8));
    }
}

void MainWindow::onNotifyAddMulti()
{
    SerialPortDialog dialog(true, this);
    if (dialog.exec() == QDialog::Accepted) {
        int num = dialog.gatherNum();
        for (int i = 0; i < num; i++) {
            m_fabMenu->setChecked(false);
            ui->expandWidget->addExpandItem(ExpandWidget::createExpandWidget(dialog.portParam(), tr("Gather%1").arg(createNo++), 8));
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->expandWidget->scrolldown();
}
