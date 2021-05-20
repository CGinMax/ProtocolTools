#include "ybtableview.h"
#include "listviewitem.h"
#include <QVBoxLayout>
#include <QDebug>

YBTableView::YBTableView(QWidget *parent) : QWidget(parent)
{
    setObjectName("YBListView");
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addSpacerItem(new QSpacerItem(width(), 100, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setStyleSheet("QWidget#YBListView{border: transparent;background-color:white;}");
}

YBTableView::~YBTableView()
{
    qDeleteAll(m_itemList);
    m_itemList.clear();
}

int YBTableView::sensorCount() const
{
    return m_itemList.count();
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
        const int index = m_itemList.isEmpty() ? 0 : m_itemList.last()->address();
        auto item = new ListViewItem(index + 1, this);
        m_itemList.append(item);

        m_layout->insertWidget(m_layout->count() -1, item);

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
        ListViewItem* item = *beginIter;
        m_layout->removeWidget(item);
        beginIter = m_itemList.erase(beginIter);
        begin++;
        delete item;
    }

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
