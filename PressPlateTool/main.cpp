#include "mainwindow.h"
#include <QApplication>

#include "ui/buttons/raisebutton.h"
#include "ui/buttons/flatbutton.h"
#include "ui/buttons/outlinebutton.h"
#include "ui/buttons/iconbutton.h"

#include "ui/base/faicon.h"
class Widget : public QWidget
{
public:
    Widget() {
        auto btn = new Ui::IconButton(FAIcon::instance()->awesome()->icon("plus"), this);
        btn->move(50, 50);
        btn->setXRadius(btn->width());
        btn->setYRadius(btn->height());
        btn->setBackgroundEnabled(false);

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
