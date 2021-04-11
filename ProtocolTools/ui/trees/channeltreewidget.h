#ifndef CHANNELTREEWIDGET_H
#define CHANNELTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>

#include "../../common/ptcfg.h"

class ChannelTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ChannelTreeWidget(QWidget *parent = nullptr);
    ~ChannelTreeWidget() override;

    void initMenuAction();
signals:
    void notifyItemSelected(QTreeWidgetItem* item);
    void notifyAddNewChannel(QTreeWidgetItem* item, const QSharedPointer<SettingData>& settingData);
    void notifyDeleteChannel(QTreeWidgetItem* item);
    void notifyChangeName(QTreeWidgetItem* item);
    void notifyChannelStart(QTreeWidgetItem* item);
    void notifyChannelStop(QTreeWidgetItem* item);

private slots:
    void onCustomContextMenuRequested(const QPoint& pos);

private:
    QTreeWidgetItem* m_tcpClientParent;
    QTreeWidgetItem* m_tcpServerParent;
    QTreeWidgetItem* m_udpParent;
    QTreeWidgetItem* m_currentPopupItem;
    QMenu m_parentNodeMenu;
    QMenu m_childNodeMenu;

    QMap<QTreeWidgetItem*, QSharedPointer<SettingData>> m_nodeSettingDatas;
};

#endif // CHANNELTREEWIDGET_H
