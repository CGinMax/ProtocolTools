#include "ybtableview.h"
#include "listdelegate.h"
#include <QDebug>

YBTableView::YBTableView(QWidget *parent) : QListView(parent)
{
    m_model = new YBTableModel({tr("Id"), tr("Current Status"), tr("Set Status"), tr("Version"), tr("Address")}, this);
    setModel(m_model);

    setStyleSheet("QListView{border: transparent;}");
}

YBTableView::~YBTableView()
{

}

void YBTableView::addYBSensor(int count)
{
    for (int i = 0; i < count; i++) {
        m_model->append();
        int currentRow = m_model->rowCount(QModelIndex()) - 1;
        auto delegate = new ListDelegate(qobject_cast<QAbstractListModel*>(model()), this);
        setItemDelegateForRow(currentRow, delegate);
        this->openPersistentEditor(m_model->index(currentRow));
    }
}

void YBTableView::clearAllYBSensor()
{
    m_model->clearAllSensor();
}
