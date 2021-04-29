#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

#include <QVBoxLayout>
#include "ui/expandwidgetitem.h"
#include "ui/expandwidget.h"
#include <QPlainTextEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto mainLayout = new QVBoxLayout(ui->centralWidget);

    auto expandWidget = new ExpandWidget(this);

    for (int i = 0; i < 10; i++) {
        auto tile = new ExpandTile("title");
        auto widget = new ExpandWidgetItem(tile);
        widget->setContentWidget(new QPlainTextEdit(widget));
        expandWidget->addExpandItem(widget);

    }

    mainLayout->addWidget(expandWidget);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
