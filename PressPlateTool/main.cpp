#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "qmlexport.h"
#include "Qaterial/Qaterial.hpp"
#include "QtAwesome/faiconprovider.h"


int main(int argc, char *argv[])
{

    QGuiApplication a(argc, argv);
     auto translator = new QTranslator();
     if (!translator->load(QString(":/translations/PressPlateTool_zh.qm"))) {
         qDebug("load failed");
     }
     a.installTranslator(translator);


    QQmlApplicationEngine engine;
    QmlExport::registerPressPlateType();
    FAIconProvider::registerProvider(&engine);

    engine.addImportPath(QString("qrc:///"));

    qaterial::Utils::loadResources();

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return a.exec();
}
