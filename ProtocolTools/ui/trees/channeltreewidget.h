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
    QTreeWidgetItem* addChannel(const QString& name, eNetworkType type);
    QTreeWidgetItem* tcpClientItem();
    QTreeWidgetItem* tcpServerItem();
    QTreeWidgetItem* udpItem();
    QTreeWidgetItem* serialPortItem();
signals:
    void notifyItemSelected(QTreeWidgetItem* item);
    void notifyAddNewChannel(QTreeWidgetItem* item, const QSharedPointer<SettingData>& settingData);
    void notifyDeleteChannel(QTreeWidgetItem* item);
    void notifyChangeName(QTreeWidgetItem* item);
    void notifyChannelStart(QTreeWidgetItem* item);
    void notifyChannelStop(QTreeWidgetItem* item);

public slots:
    void onCurrentItemChanged(QTreeWidgetItem* item);

private slots:
    void onItemClicked(QTreeWidgetItem* item);
    void onCustomContextMenuRequested(const QPoint& pos);

private:
    eNetworkType selectNetworkType(QTreeWidgetItem* item);
    QIcon createNetworkIcon(eNetworkType type);
private:
    QTreeWidgetItem* m_tcpClientParent;
    QTreeWidgetItem* m_tcpServerParent;
    QTreeWidgetItem* m_udpParent;
    QTreeWidgetItem* m_serialPortParent;
    QTreeWidgetItem* m_currentPopupItem;
    QMenu m_parentNodeMenu;
    QMenu m_childNodeMenu;

    QList<QIcon> m_networkIcons;
};

#endif // CHANNELTREEWIDGET_H
