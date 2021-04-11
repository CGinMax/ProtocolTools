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


signals:
    void addNewPage(TabPage* page);
    void removePage(TabPage* page);
    void changePageName(TabPage* page);

public slots:
    void onNotifyItemSelected(QTreeWidgetItem* item);
    void onNotifyAddNewChannel(QTreeWidgetItem* item, const QSharedPointer<SettingData>& settingData);
    void onNotifyDeleteChannel(QTreeWidgetItem* item);
    void onNotifyChangeName(QTreeWidgetItem* item);
    void onNotifyChannelStart(QTreeWidgetItem* item);
    void onNotifyChannelStop(QTreeWidgetItem* item);

private:
    QStackedWidget* m_widget;
    int m_lastIndex;
    QMap<QTreeWidgetItem*, int> m_itemIndexMap;
};

#endif // STACKEDCONTROLLER_H
