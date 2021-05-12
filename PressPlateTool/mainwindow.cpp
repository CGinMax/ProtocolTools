#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

#include "ui/expand/expandwidgetitem.h"
#include "ui/expand/expandwidget.h"
#include "ui/dialogs/serialportdialog.h"
#include "ui/buttons/fabbutton.h"

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
    auto oneBtn = new FabButton(m_fabMenu);
    oneBtn->setIcon(QIcon(":/icons/add-one.png"));
    oneBtn->setCorner(Qt::TopLeftCorner);
    oneBtn->setOffset(0, 0);
    oneBtn->setIconSize(18);
    oneBtn->setCheckable(false);
    oneBtn->setDiameter(36);
    oneBtn->setShadowEnabled(false);
    oneBtn->setHoverEnabled(false);
    auto multiBtn = new FabButton(m_fabMenu);
    multiBtn->setIcon(QIcon(":/icons/add-multi.png"));
    multiBtn->setCorner(Qt::TopLeftCorner);
    multiBtn->setOffset(0, 0);
    multiBtn->setIconSize(18);
    multiBtn->setCheckable(false);
    multiBtn->setDiameter(36);
    multiBtn->setShadowEnabled(false);
    multiBtn->setHoverEnabled(false);
//    auto btn3 = new FabButton(this);
//    btn3->setCorner(Qt::TopLeftCorner);
//    btn3->setOffset(0, 0);
//    btn3->setIconSize(18);
//    btn3->setCheckable(false);
//    btn3->setDiameter(36);
//    auto btn4 = new FabButton(this);
//    btn4->setCorner(Qt::TopLeftCorner);
//    btn4->setOffset(0, 0);
//    btn4->setIconSize(18);
//    btn4->setCheckable(false);
//    btn4->setDiameter(36);
    m_fabMenu->addButton(oneBtn);
    m_fabMenu->addButton(multiBtn);
//    m_fabMenu->addButton(btn3);
//    m_fabMenu->addButton(btn4);
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
        ui->expandWidget->addExpandItem(ExpandWidget::createExpandWidget(dialog.portParam(), tr("Gather%1").arg(createNo++), 8));
    }
}

void MainWindow::onNotifyAddMulti()
{
    SerialPortDialog dialog(true, this);
    if (dialog.exec() == QDialog::Accepted) {
        int num = dialog.gatherNum();
        for (int i = 0; i < num; i++) {
            ui->expandWidget->addExpandItem(ExpandWidget::createExpandWidget(dialog.portParam(), tr("Gather%1").arg(createNo++), 8));
        }
    }
}
