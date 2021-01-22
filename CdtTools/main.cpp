#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto translator = new QTranslator();
    translator->load("./translations/CdtTools_zh.qm");
    a.installTranslator(translator);

    MainWindow w;
    w.show();

    return a.exec();
}
