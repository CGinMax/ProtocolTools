#include "mainwindow.h"
#include <QApplication>

#include "ui/buttons/raisebutton.h"
#include "ui/buttons/flatbutton.h"
#include "ui/buttons/outlinebutton.h"
class Widget : public QWidget
{
public:
    Widget() {
        auto btn = new Ui::OutlineButton("hello", this);
//        btn->setIcon(QIcon(":/icons/add-multi.png"));
//        btn->resize(100, 50);
        btn->move(50, 50);

    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Widget btn;
    btn.setGeometry(200, 200, 200, 200);
    btn.show();
    return a.exec();
}
