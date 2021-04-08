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
#include "../../common/saveconfig.h"

MainTabWidget::MainTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_lastTabIndex(-1)
{
    auto bar = new MainTabBar(this);
    setTabBar(bar);

    setTabsClosable(true);
    tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    connect(bar, &MainTabBar::tabAtIndexClicked, this, &MainTabWidget::onTabAtIndexClicked);
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

void MainTabWidget::backToBeforeIndex(bool isBack)
{
    if (isBack) {
        setCurrentIndex(m_opendIndex);
    }
    else {
        m_opendIndex = currentIndex();
    }
}

void MainTabWidget::onTabCloseRequested(int index)
{
    if (QMessageBox::information(this, tr("Close Tab"), QString("Close tab %1?").arg(tabText(index))
                                 , QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
    }
    auto widget = this->widget(index);
    removeTab(index);
    delete widget;

    m_lastTabIndex--;
}

void MainTabWidget::onTabBarClicked(int index)
{
    if (index == m_lastTabIndex) {
        emit addNewPage();
        return;
    }

    m_opendIndex = index;
}

void MainTabWidget::onTabAtIndexClicked(int index)
{
    if (index < m_lastTabIndex) {
        showContextMenu(index);
        return;
    }
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
    connect(menu.addAction(tr("Change Name")), &QAction::triggered, this, [this, tabIndex]{
        NamedDialog dlg(this->tabText(tabIndex));
        if (dlg.exec() == QDialog::Accepted) {
            this->setTabText(tabIndex, dlg.getNameString());
            qobject_cast<TabPage*>(this->widget(tabIndex))->setPageName(dlg.getNameString());
        }
    });
    connect(menu.addAction(tr("Save")), &QAction::triggered, this, [=]{
        auto saveFileName = QFileDialog::getSaveFileName(nullptr, tr("Save")
                            , QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()+"/cdt.bk", QLatin1String("All Files (*.*)"));
        if (saveFileName.isNull()) {
            return ;
        }
        ThreadPool::instance()->run([=]{
            auto tab = qobject_cast<TabPage*>(this->widget(tabIndex));
            tab->resetSettingData();
            QMultiMap<QString, SettingData *> settingMap;
            settingMap.insert(tab->getPageName(), tab->getSettingData());
            try {
                SaveConfig::saveConfig(settingMap, saveFileName);
            } catch (std::exception& e) {
                qDebug("%s", e.what());
            }
//            emit this->saveFinish(success, success ? tr("Save %1 Success!").arg(saveFileName) : tr("Save %1 Failed!").arg(saveFileName));
        });
    });
    connect(menu.addAction(tr("Split")), &QAction::triggered, this, &MainTabWidget::onDivideTab);

    connect(menu.addAction(tr("Close")), &QAction::triggered, this, [this, tabIndex]{
        emit this->tabCloseRequested(tabIndex);
    });
    menu.exec(QCursor::pos());
}

