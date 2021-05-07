#include "mainwindow.h"
#include <QApplication>
#include "ui/tables/ybtableview.h"
#include "ui/tables/listdelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    YBTable table;
//    auto delegate = new ListDelegate(qobject_cast<QAbstractListModel*>(table.model()));
//    table.setItemDelegate(delegate);
//    table.openPersistentEditor(table.model()->index(0, 0));
//    table.openPersistentEditor(table.model()->index(1, 0));
//    table.show();

    return a.exec();
}
