#ifndef STACKEDCONTROLLER_H
#define STACKEDCONTROLLER_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QStackedWidget>
#include "../../common/ptcfg.h"

class TabPage;

class StackedController : public QObject
{
    Q_OBJECT
public:
    explicit StackedController(QStackedWidget* widget, QObject *parent = nullptr);
    ~StackedController() override;
    void insertInitWidget(QTreeWidgetItem* item, QWidget* widget);

signals:
    void addNewPage(TabPage* page, eNetworkType type);
    void removePage(TabPage* page, eNetworkType type);
    void changePageName(TabPage* page, eNetworkType type);

public slots:
    void onNotifyItemSelected(QTreeWidgetItem* item);
    void onNotifyAddNewChannel(QTreeWidgetItem* item, const QSharedPointer<SettingData>& settingData, eNetworkType type);
    void onNotifyDeleteChannel(QTreeWidgetItem* item, eNetworkType type);
    void onNotifyChangeName(QTreeWidgetItem* item, eNetworkType type);
    void onNotifyChannelStart(QTreeWidgetItem* item);
    void onNotifyChannelStop(QTreeWidgetItem* item);

private:
    QStackedWidget* m_widget;
    int m_lastIndex;
    QMap<QTreeWidgetItem*, int> m_itemIndexMap;
};

#endif // STACKEDCONTROLLER_H
