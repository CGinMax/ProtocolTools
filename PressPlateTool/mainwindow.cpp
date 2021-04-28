#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

#include <QVBoxLayout>
#include "ui/expandwidgetitem.h"
#include <QPlainTextEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto mainLayout = new QVBoxLayout(ui->centralWidget);

    auto tile = new ExpandTile("title");
    auto widget = new ExpandWidgetItem (tile);
    widget->setContentWidget(new QPlainTextEdit(widget));
    mainLayout->addWidget(widget);
    mainLayout->addWidget(new QPlainTextEdit(this));

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
