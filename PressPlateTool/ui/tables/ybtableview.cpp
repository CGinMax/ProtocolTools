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

int YBTableView::sensorCount() const
{
    return m_model->rowCount(QModelIndex());
}

void YBTableView::setListItemAddr(int index, int addr)
{
    if (index > m_itemList.count()) {
        return;
    }
    auto item = m_itemList.at(index);
    item->setAddress(addr);

}

int YBTableView::getListItemAddr(int index)
{
    if (index > m_itemList.count()) {
        return -1;
    }
    auto item = m_itemList.at(index);
    return item->address();
}

void YBTableView::setListItemStatus(int index, uint8_t curStatus, uint8_t configedStatus)
{
    if (index > m_itemList.count()) {
        return ;
    }
    auto item = m_itemList.at(index);
    item->setCurrentStatus(curStatus);
    item->setConfigedStatus(configedStatus);
}

void YBTableView::setListItemVersion(int index, const QString &hardVer, const QString &softVer, const QString &productDesc)
{
    if (index > m_itemList.count()) {
        return;
    }
    auto item = m_itemList.at(index);
    item->setHardwareVersion(hardVer);
    item->setSoftwareVersion(softVer);
    item->setProductionDescription(productDesc);
}

void YBTableView::setListItemConfigedStatus(int index, uint8_t status)
{
    if (index > m_itemList.count()) {
        return ;
    }
    auto item = m_itemList.at(index);
    item->setConfigedStatus(status);
}

void YBTableView::addYBSensor(int count)
{
    for (int i = 0; i < count; i++) {
        m_model->append();
        int currentRow = m_model->rowCount(QModelIndex()) - 1;
        auto delegate = new ListDelegate(qobject_cast<QAbstractListModel*>(model()), this);
        setItemDelegateForRow(currentRow, delegate);
        this->openPersistentEditor(m_model->index(currentRow));
        auto item = delegate->getListItem();
        m_itemList.append(item);
        connect(item, &ListViewItem::notifySetAddr, this, [=](int addr){
            int index = m_itemList.indexOf(qobject_cast<ListViewItem*>(sender()));
            emit this->setSensorAddr(index, addr);
        });
        connect(item, &ListViewItem::notifyQueryStatus, this, [=](int addr){
            int index = m_itemList.indexOf(qobject_cast<ListViewItem*>(sender()));
            emit this->querySensorStatus(index, addr);
        });
        connect(item, &ListViewItem::notifyQueryVersion, this, [=](int addr){
            int index = m_itemList.indexOf(qobject_cast<ListViewItem*>(sender()));
            emit this->querySensorVersion(index, addr);
        });
        connect(item, &ListViewItem::statusChanged, this, [=](int addr, int status){
            int index = m_itemList.indexOf(qobject_cast<ListViewItem*>(sender()));
            emit this->changeSensorStatus(index, addr, status);
        });
        connect(item, &ListViewItem::notifyDelete, this, &YBTableView::onNotifyDelete);
    }
}

void YBTableView::deleteYBSensor(int first, int last)
{
    int begin = first;
    auto beginIter = m_itemList.begin() + first;
    while (begin < last && beginIter != m_itemList.end()) {
        beginIter = m_itemList.erase(beginIter);
        begin++;
    }

    m_model->deleteSensors(first, last);
}

void YBTableView::deleteAllYBSensor()
{
    deleteYBSensor(0, sensorCount());
}

void YBTableView::onNotifyDelete()
{
    auto item = qobject_cast<ListViewItem*>(sender());
    int index = m_itemList.indexOf(item);
    if (index == -1) {
        qDebug("error index");
        return;
    }

    deleteYBSensor(index, index + 1);
}
