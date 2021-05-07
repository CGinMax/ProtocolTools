#include "ybtableview.h"
#include "ybtablemodel.h"

YBTableView::YBTableView(QWidget *parent) : QListView(parent)
{
    auto model = new YBTableModel({tr("Id"), tr("Current Status"), tr("Set Status"), tr("Version"), tr("Address")}, this);
    setModel(model);

    model->append();
    model->append();

    setStyleSheet("QListView{border: transparent;}");
}
