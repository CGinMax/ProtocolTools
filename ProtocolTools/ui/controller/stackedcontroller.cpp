#include "stackedcontroller.h"
#include "../tabpage.h"

StackedController::StackedController(QStackedWidget *widget, QObject *parent)
    : QObject(parent)
    , m_widget(widget)
    , m_lastIndex(0)
{

}

StackedController::~StackedController()
{

}

void StackedController::onNotifyItemSelected(QTreeWidgetItem *item)
{
    auto itemIter = m_itemIndexMap.find(item);
    m_widget->setCurrentIndex(itemIter.value());
}

void StackedController::onNotifyAddNewChannel(QTreeWidgetItem *item, const QSharedPointer<SettingData> &settingData)
{
    // parent在TabWidget设置，由TabWidget管理
    auto newPage = new TabPage(settingData, item->text(0));
    m_widget->insertWidget(m_lastIndex, newPage);
    emit addNewPage(newPage);
    m_itemIndexMap.insert(item, m_lastIndex++);
}

void StackedController::onNotifyDeleteChannel(QTreeWidgetItem *item)
{
    auto widget = m_widget->widget(m_itemIndexMap.find(item).value());
    m_widget->removeWidget(widget);
    emit removePage(qobject_cast<TabPage*>(widget));
}

void StackedController::onNotifyChangeName(QTreeWidgetItem *item)
{
    auto index = m_itemIndexMap.find(item).value();
    auto page = qobject_cast<TabPage*>(m_widget->widget(index));
    page->setPageName(item->text(0));
    emit changePageName(page);
}

void StackedController::onNotifyChannelStart(QTreeWidgetItem *item)
{
    auto index = m_itemIndexMap.find(item).value();
    auto page = qobject_cast<TabPage*>(m_widget->widget(index));
    page->startCommunication();
}

void StackedController::onNotifyChannelStop(QTreeWidgetItem *item)
{
    auto index = m_itemIndexMap.find(item).value();
    auto page = qobject_cast<TabPage*>(m_widget->widget(index));
    page->stopCommunication();
}
