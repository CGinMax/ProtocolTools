#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include "../controller/savecontroller.h"

class TabPage;

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(SaveController* saveCtrl, QWidget *parent = nullptr);

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);
    void removeTabByWidget(QWidget* widget);
    void changeTabName(QWidget* widget, const QString& name);
    void backToBeforeIndex(bool isBack = false);

    QMultiMap<QString, SettingData*> getAllChildrenSetting();
signals:
    void currentTabChanged(QWidget* widget);
public slots:
    void onTabCloseRequested(int index);
    void onCurrentChanged(int index);
    void onTabBarClicked(int index);
    void onDivideTab();
private:
    void showContextMenu(int tabIndex);

private:
    int m_opendIndex;
    int m_lastTabIndex;
    int m_contenxtIndex;

    SaveController* m_saveController;
};

#endif // MAINTABWIDGET_H
