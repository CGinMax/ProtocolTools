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

void StackedController::insertInitWidget(QTreeWidgetItem *item, QWidget *widget)
{
    m_itemIndexMap.insert(item, m_lastIndex);
    m_widget->addWidget(widget);
    m_lastIndex++;
}

void StackedController::onNotifyItemSelected(QTreeWidgetItem *item)
{
    auto itemIter = m_itemIndexMap.find(item);
    m_widget->setCurrentIndex(itemIter.value());
}

void StackedController::onNotifyAddNewChannel(QTreeWidgetItem *item, const QSharedPointer<SettingData> &settingData, eNetworkType type)
{
    // parent在TabWidget设置，由TabWidget管理
    auto newPage = new TabPage(settingData, item->text(0));
    m_widget->insertWidget(m_lastIndex, newPage);
    emit addNewPage(newPage, type);
    m_itemIndexMap.insert(item, m_lastIndex++);
}

void StackedController::onNotifyDeleteChannel(QTreeWidgetItem *item, eNetworkType type)
{
    auto widget = m_widget->widget(m_itemIndexMap.find(item).value());
    m_widget->removeWidget(widget);
    emit removePage(qobject_cast<TabPage*>(widget), type);
}

void StackedController::onNotifyChangeName(QTreeWidgetItem *item, eNetworkType type)
{
    auto index = m_itemIndexMap.find(item).value();
    auto page = qobject_cast<TabPage*>(m_widget->widget(index));
    page->setPageName(item->text(0));
    emit changePageName(page, type);
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
