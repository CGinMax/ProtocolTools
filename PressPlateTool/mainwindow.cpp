#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

#include "ui/expand/expandwidgetitem.h"
#include "ui/expand/expandwidget.h"
#include "ui/expand/gatheroperwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainSplitter->setChildrenCollapsible(false);
    ui->mainSplitter->setStretchFactor(0, 2);
    ui->mainSplitter->setStretchFactor(1, 5);

//    auto tile = new ExpandTile("title");
//    auto widget = new ExpandWidgetItem(tile);
//    widget->setBorderRadius(8);
//    widget->setContentWidget(new GatherOperWidget(widget));
//    ui->expandWidget->addExpandItem(widget);

//    auto expandWidget = new ExpandWidget(this);
    for (int i = 0; i < 10; i++) {
        auto tile = new ExpandTile("title");
        auto widget = new ExpandWidgetItem(tile);
        widget->setBorderRadius(5);
        widget->setContentWidget(new GatherOperWidget(widget));
        ui->expandWidget->addExpandItem(widget);
    }

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
