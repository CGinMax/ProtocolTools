#include "mainwindow.h"
#include <QApplication>
#include "ui/cdtworkwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedPointer<PtCfg> pt(new PtCfg);
    CDTWorkWidget widget(pt);
    widget.show();
//    MainWindow w;
//    w.show();

    return a.exec();
}
