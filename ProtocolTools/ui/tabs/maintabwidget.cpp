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

MainTabWidget::MainTabWidget(SaveController *saveCtrl, QWidget *parent)
    : QTabWidget(parent)
    , m_lastTabIndex(0)
    , m_saveController(saveCtrl)
{
    auto bar = new MainTabBar(this);
    setTabBar(bar);

    setTabsClosable(false);
    tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    connect(this, &QTabWidget::tabCloseRequested, this, &MainTabWidget::onTabCloseRequested);
    connect(this, &QTabWidget::tabBarClicked, this, &MainTabWidget::onTabBarClicked);
    connect(this, &QTabWidget::currentChanged, this, &MainTabWidget::onCurrentChanged);
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

void MainTabWidget::backToBeforeIndex(bool isBack)
{
    if (isBack) {
        setCurrentIndex(m_opendIndex);
    }
    else {
        m_opendIndex = currentIndex();
    }
}

QMultiMap<QString, SettingData *> MainTabWidget::getAllChildrenSetting()
{
    QMultiMap<QString, SettingData*> settingMap;
    for (int i = 0; i < count() - 1; i++) {
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

void MainTabWidget::onTabBarClicked(int index)
{
    m_opendIndex = index;
}

void MainTabWidget::onDivideTab()
{
    auto widget = this->widget(m_contenxtIndex);
    const auto tabName = tabText(m_contenxtIndex);
    removeTab(m_contenxtIndex);
    widget->setParent(nullptr);
    widget->setWindowTitle(tabName);
    widget->setGeometry(200, 200, 260, 360);
    widget->show();
    m_lastTabIndex--;
}

void MainTabWidget::showContextMenu(int tabIndex)
{
    QMenu menu;
    m_contenxtIndex = tabIndex;
    connect(menu.addAction(tr("Change Name")), &QAction::triggered, this, [=]{
        NamedDialog dlg(this->tabText(tabIndex));
        if (dlg.exec() == QDialog::Accepted) {
            this->setTabText(tabIndex, dlg.getNameString());
            qobject_cast<TabPage*>(this->widget(tabIndex))->setPageName(dlg.getNameString());
        }
    });
    connect(menu.addAction(tr("Save")), &QAction::triggered, this, [=]{

        auto tab = qobject_cast<TabPage*>(this->widget(tabIndex));
        tab->resetSettingData();
        QMultiMap<QString, SettingData *> settingMap;
        settingMap.insert(tab->getPageName(), tab->getSettingData());
        m_saveController->onActionSaveTriggered(settingMap);
    });
    connect(menu.addAction(tr("Split")), &QAction::triggered, this, &MainTabWidget::onDivideTab);

    connect(menu.addAction(tr("Close")), &QAction::triggered, this, [this, tabIndex]{
        emit this->tabCloseRequested(tabIndex);
    });
    menu.exec(QCursor::pos());
}

