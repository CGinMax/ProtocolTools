#ifndef MAINTABCONTROLLER_H
#define MAINTABCONTROLLER_H

#include <QObject>
#include <QTreeWidgetItem>
#include "../tabs/maintabwidget.h"
#include "../../common/ptcfg.h"

class TabPage;

class MainTabController : public QObject
{
    Q_OBJECT
public:
    explicit MainTabController(MainTabWidget* widget, QObject *parent = nullptr);
    ~MainTabController() override;

signals:

    void currentItemChanged(QTreeWidgetItem* item);

public slots:
    void onNotifyItemSelected(QTreeWidgetItem* item);
    void onNotifyAddNewChannel(QTreeWidgetItem* item, const QSharedPointer<SettingData>& settingData);
    void onNotifyDeleteChannel(QTreeWidgetItem* item);
    void onNotifyChangeName(QTreeWidgetItem* item);
    void onNotifyChannelStart(QTreeWidgetItem* item);
    void onNotifyChannelStop(QTreeWidgetItem* item);

    void onCurrentTabChanged(QWidget* widget);

private:
    MainTabWidget* m_widget;
    int m_lastIndex;
    QMap<QTreeWidgetItem*, QWidget*> m_itemWidgetMap;
};

#endif // MAINTABCONTROLLER_H
