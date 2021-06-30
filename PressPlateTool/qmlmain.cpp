#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "qmlexport.h"
#include "Qaterial/Qaterial.hpp"
#include "QtAwesome/faiconprovider.h"
//#include "provider/faiconprovider.h"

int main(int argc, char *argv[])
{

    QGuiApplication a(argc, argv);
    // auto translator = new QTranslator();
    // translator->load(QGuiApplication::applicationDirPath() + "/PressPlateTool_zh.qm");
    // a.installTranslator(translator);


    QQmlApplicationEngine engine;
    QmlExport::registerPressPlateType();
    FAIconProvider::registerProvider(&engine);
//    engine.addImageProvider(QString("FAIcon"), reinterpret_cast<QQmlImageProviderBase*>(new FAIconProvider));

    engine.addImportPath(QString("qrc:///"));

    qaterial::Utils::loadResources();

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
