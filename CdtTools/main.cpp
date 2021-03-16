#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QStyle>
#include <QDialog>
#include "../qt-material-widgets/qtmaterialraisedbutton.h"
#include <QVBoxLayout>
#include <QScroller>
class Dialog : public QDialog
{
public:
    Dialog(QWidget *parent = nullptr) : QDialog(parent){
        setGeometry(300, 200, 300, 300);
        auto layout = new QVBoxLayout(this);
        auto rb = new QtMaterialRaisedButton("raise");
        rb->setIcon(QIcon(style()->standardIcon(QStyle::SP_FileIcon)));
        rb->setIconPlacement(Material::RightIcon);
        rb->setHaloVisible(false);
        QScroller *sc = QScroller::scroller(rb);
        sc->scrollTo(QPointF(100, 100));
        layout->addWidget(rb);
    }
    ~Dialog() = default;


};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto customTrans = new QTranslator();
    customTrans->load(QLatin1String(":/translations/CdtTools_zh.qm"));
    a.installTranslator(customTrans);

    auto systemTrans = new QTranslator();
    systemTrans->load(QLatin1String(":/translations/qt_zh_CN.qm"));
    a.installTranslator(systemTrans);

    MainWindow w;
    w.show();
//    Dialog dlg;
//    dlg.show();

    return a.exec();
}
