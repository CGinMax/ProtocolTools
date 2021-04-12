#include "maintabcontroller.h"
#include "../tabpage.h"

MainTabController::MainTabController(MainTabWidget *widget, QObject *parent)
    : QObject(parent)
    , m_widget(widget)
{
    connect(m_widget, &MainTabWidget::currentTabChanged, this, &MainTabController::onCurrentTabChanged);
}

MainTabController::~MainTabController()
{

}

void MainTabController::onNotifyItemSelected(QTreeWidgetItem *item)
{
    auto itemIter = m_itemWidgetMap.find(item);
    m_widget->setCurrentWidget(itemIter.value());
}

void MainTabController::onNotifyAddNewChannel(QTreeWidgetItem *item, const QSharedPointer<SettingData> &settingData)
{
    // parent在TabWidget设置，由TabWidget管理
    auto newPage = new TabPage(settingData, item->text(0));
    m_widget->addTab(newPage, item->icon(0), item->text(0));
    m_itemWidgetMap.insert(item, newPage);
}

void MainTabController::onNotifyDeleteChannel(QTreeWidgetItem *item)
{
    auto widget = m_itemWidgetMap.find(item).value();
    m_itemWidgetMap.remove(item);
    qobject_cast<TabPage*>(widget)->stopCommunication();
    m_widget->removeTabByWidget(widget);
}

void MainTabController::onNotifyChangeName(QTreeWidgetItem *item)
{
    auto page = qobject_cast<TabPage*>(m_itemWidgetMap.find(item).value());
    page->setPageName(item->text(0));
    m_widget->changeTabName(page, item->text(0));
}

void MainTabController::onNotifyChannelStart(QTreeWidgetItem *item)
{
    auto page = qobject_cast<TabPage*>(m_itemWidgetMap.find(item).value());
    page->startCommunication();
}

void MainTabController::onNotifyChannelStop(QTreeWidgetItem *item)
{
    auto page = qobject_cast<TabPage*>(m_itemWidgetMap.find(item).value());
    page->stopCommunication();
}

void MainTabController::onCurrentTabChanged(QWidget *widget)
{
    auto item = m_itemWidgetMap.key(widget);
    emit currentItemChanged(item);
}
