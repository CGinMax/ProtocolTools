#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include "ui/components/switchbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto customTrans = new QTranslator();
    customTrans->load(QLatin1String(":/translations/ProtocolTools_zh.qm"));
    a.installTranslator(customTrans);

    auto systemTrans = new QTranslator();
    systemTrans->load(QLatin1String(":/translations/qt_zh_CN.qm"));
    a.installTranslator(systemTrans);

    MainWindow w;
    w.show();
//    SwitchButton bt;
//    bt.setGeometry(100, 100 ,100,100);
//    bt.show();

    return a.exec();
}
