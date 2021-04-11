#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include "../../common/savecontroller.h"

class TabPage;

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(SaveController* saveCtrl, QWidget *parent = nullptr);

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);

    void backToBeforeIndex(bool isBack = false);

    QMultiMap<QString, SettingData*> getAllChildrenSetting();
signals:
public slots:
    void onTabCloseRequested(int index);
    void onTabBarClicked(int index);
    void onDivideTab();

    void onAddNewPage(TabPage* page);
    void onRemovePage(TabPage* page);
    void onChangePageName(TabPage* page);

private:
    void showContextMenu(int tabIndex);

private:
    int m_opendIndex;
    int m_lastTabIndex;
    int m_contenxtIndex;

    SaveController* m_saveController;
};

#endif // MAINTABWIDGET_H
