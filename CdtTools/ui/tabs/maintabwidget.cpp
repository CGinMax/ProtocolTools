#include "maintabwidget.h"
#include <QTabBar>
#include <QStyle>
#include <QMenu>
#include "fakeclosebutton.h"
#include "../tabpage.h"
#include <QDebug>

MainTabWidget::MainTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_lastTabIndex(-1)
{
    setTabsClosable(true);
    tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    connect(this, &QTabWidget::tabCloseRequested, this, &MainTabWidget::onTabCloseRequested);
    connect(this, &QTabWidget::tabBarClicked, this, &MainTabWidget::onTabBarClicked);
    m_lastTabIndex = addTab(new QWidget, "+");
    tabBar()->setTabButton(m_lastTabIndex
                           , static_cast<QTabBar::ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, nullptr, tabBar()))
                           , new FakeCloseButton);
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

void MainTabWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        const auto tabIndex = tabBar()->tabAt(event->pos());
        if (tabIndex < m_lastTabIndex) {
            showContextMenu(tabIndex);
            return;
        }
    }

    QTabWidget::mousePressEvent(event);
}

void MainTabWidget::onTabCloseRequested(int index)
{
    auto widget = this->widget(index);
    removeTab(index);
    delete widget;

    m_lastTabIndex--;
}

void MainTabWidget::onTabBarClicked(int index)
{
    if (index == m_lastTabIndex) {
        emit addNewPage();
    }
}

void MainTabWidget::onDivideTab()
{
    auto widget = this->widget(m_contenxtIndex);
    const auto tabName = tabText(m_contenxtIndex);
    qDebug() << tabName;
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
    connect(menu.addAction(tr("Split")), &QAction::triggered, this, &MainTabWidget::onDivideTab);

    connect(menu.addAction(tr("Close")), &QAction::triggered, this, [this, tabIndex]{
        emit this->tabCloseRequested(tabIndex);
    });
    menu.exec(QCursor::pos());
}

