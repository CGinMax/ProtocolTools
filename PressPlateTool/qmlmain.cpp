#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "qmlserialporthelper.h"
#include "Qaterial/Qaterial.hpp"

int main(int argc, char *argv[])
{

    QGuiApplication a(argc, argv);
    // auto translator = new QTranslator();
    // translator->load(QGuiApplication::applicationDirPath() + "/PressPlateTool_zh.qm");
    // a.installTranslator(translator);

    QQmlApplicationEngine engine;

    engine.addImportPath(QString("qrc:///"));

    qmlRegisterType<QmlSerialPortHelper>("PressPlateTools", 1, 0, "QmlSerialPortHelper");

    qaterial::Utils::loadResources();

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
