#include "maintabwidget.h"
#include <QTabBar>
#include <QStyle>
#include <QMenu>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMultiMap>
#include "fakeclosebutton.h"
#include "maintabbar.h"
#include "../tabpage.h"
#include "../dialog/nameddialog.h"
#include "ui/controller/savecontroller.h"

MainTabWidget::MainTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_lastTabIndex(0)
{
    auto bar = new MainTabBar(this);
    setTabBar(bar);

    setTabsClosable(false);
    tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    connect(this, &QTabWidget::tabCloseRequested, this, &MainTabWidget::onTabCloseRequested);
    connect(this, &QTabWidget::currentChanged, this, &MainTabWidget::onCurrentChanged);
}

MainTabWidget::~MainTabWidget()
{

}

int MainTabWidget::addTab(QWidget *widget, const QString &label)
{
    const int tabIndex = QTabWidget::addTab(widget, label);

    tabBar()->moveTab(tabIndex, m_lastTabIndex);
    setCurrentIndex(m_lastTabIndex);
    m_lastTabIndex++;
    return tabIndex;
}

int MainTabWidget::addTab(QWidget *widget, const QIcon &icon, const QString &label)
{
    const int tabIndex = QTabWidget::addTab(widget, icon, label);

    tabBar()->moveTab(tabIndex, m_lastTabIndex);
    setCurrentIndex(m_lastTabIndex);
    m_lastTabIndex++;
    return tabIndex;
}

void MainTabWidget::removeTabByWidget(QWidget *widget)
{
    int index = indexOf(widget);
    onTabCloseRequested(index);
}

void MainTabWidget::changeTabName(QWidget *widget, const QString &name)
{
    setTabText(indexOf(widget), name);
}

void MainTabWidget::setSaveController(SaveController *saveCtrl)
{
    m_saveController = saveCtrl;
}

QMultiMap<QString, SettingData *> MainTabWidget::getAllChildrenSetting()
{
    QMultiMap<QString, SettingData*> settingMap;
    for (int i = 0; i < count(); i++) {
        auto tab = qobject_cast<TabPage*>(this->widget(i));
        tab->resetSettingData();
        settingMap.insert(tab->getPageName(), tab->getSettingData());
    }
    return settingMap;
}

void MainTabWidget::onTabCloseRequested(int index)
{
    auto widget = this->widget(index);
    this->removeTab(index);
    delete widget;

    m_lastTabIndex--;
}

void MainTabWidget::onCurrentChanged(int index)
{
    auto widget = this->widget(index);
    emit currentTabChanged(widget);
}

//void MainTabWidget::onCloseAllCommunication()
//{
//    if (this->count() <= 0) {
//        return;
//    }

//    for (int i = 0; i < this->count(); i++) {
//        auto page = qobject_cast<TabPage*>(widget(i));
//        page->stopCommunication();
//    }
//}

