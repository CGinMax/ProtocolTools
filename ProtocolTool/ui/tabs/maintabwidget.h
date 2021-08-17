#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include "../controller/savecontroller.h"

class TabPage;

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(QWidget *parent = nullptr);
    ~MainTabWidget() override;

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);
    void removeTabByWidget(QWidget* widget);
    void changeTabName(QWidget* widget, const QString& name);

    void setSaveController(SaveController* saveCtrl);

    QMultiMap<QString, SettingData*> getAllChildrenSetting();
signals:
    void currentTabChanged(QWidget* widget);
public slots:
    void onTabCloseRequested(int index);
    void onCurrentChanged(int index);
//    void onCloseAllCommunication();
private:

private:
    int m_lastTabIndex;
    int m_contenxtIndex;

    SaveController* m_saveController;
};

#endif // MAINTABWIDGET_H
