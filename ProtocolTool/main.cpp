#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QFontDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontid = QFontDatabase::addApplicationFont(QLatin1String(":/fonts/resources/fonts/OPPOSans-M.ttf"));
    auto fontFamilies = QFontDatabase::applicationFontFamilies(fontid);
    QFont font(fontFamilies.first());
    a.setFont(font);
    auto customTrans = new QTranslator();
    customTrans->load(QLatin1String(":/translations/ProtocolTool_zh.qm"));
    a.installTranslator(customTrans);

    auto systemTrans = new QTranslator();
    systemTrans->load(QLatin1String(":/translations/qt_zh_CN.qm"));
    a.installTranslator(systemTrans);

    MainWindow w;
    w.show();
    return a.exec();
}
