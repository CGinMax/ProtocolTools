#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Qaterial/Qaterial.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    QQmlApplicationEngine engine;

    engine.addImportPath(QString("qrc:///"));

    qaterial::Utils::loadResources();

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
