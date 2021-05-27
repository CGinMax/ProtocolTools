#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QEvent>
#include <QDebug>
#include <QQuickStyle>
#include <QQmlApplicationEngine>

#include "ui/notification/snackbar.h"
#include "ui/base/faicon.h"
class Widget : public QWidget
{
public:
    Widget() {
        bar = new Ui::SnackBar(FAIcon::instance()->icon("infocircle"), QString("你好这是开发者"), this);
        bar->raise();
        bar->setTextFlag(Qt::TextSingleLine);
        bar->setAction("RETRY", [=](){
            bar->hideBar();
        });
        bar->move((width() - bar->width()) / 2, height() + 2);
        bar->setSlidePos(QPoint((width() - bar->width()) / 2, height() + 2));
//        bar->resize(200, 60);
    }

    bool event(QEvent* event) override {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move) {
            bar->move((width() - bar->width()) / 2, height() + 2);
            bar->setSlidePos(QPoint((width() - bar->width()) / 2, height() + 2));
        } else if (event->type() == QEvent::MouseButtonPress) {
            bar->showBar();
        }
        return QWidget::event(event);
    }
private:
    Ui::SnackBar* bar;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto translator = new QTranslator();
    translator->load(QLatin1String(":/translations/PressPlateTool_zh.qm"));
    QApplication::installTranslator(translator);
    MainWindow w;
    w.show();

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    qDebug() << QApplication::applicationDirPath();
    engine.addImportPath(QApplication::applicationDirPath());
    engine.load(QUrl("qrc:/qml/main.qml"));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    Widget widget;
//    widget.setGeometry(100, 100, 300, 300);
//    widget.show();
    return a.exec();
}
