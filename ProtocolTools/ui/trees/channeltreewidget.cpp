#include "channeltreewidget.h"
#include <QCursor>
#include <QAction>
#include <QMap>
#include <QSharedPointer>

#include <QDebug>
#include "../dialog/nameddialog.h"

ChannelTreeWidget::ChannelTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
    , m_tcpClientParent(new QTreeWidgetItem(this))
    , m_tcpServerParent(new QTreeWidgetItem(this))
    , m_udpParent(new QTreeWidgetItem(this))
    , m_currentPopupItem(nullptr)
{
    initMenuAction();
    m_tcpClientParent->setText(0, tr("Tcp Client"));
    m_tcpServerParent->setText(0, tr("Tcp Server"));
    m_udpParent->setText(0, tr("Udp"));
    setHeaderLabel(tr("Channel"));
    insertTopLevelItem(0, m_tcpClientParent);
    insertTopLevelItem(1, m_tcpServerParent);
    insertTopLevelItem(2, m_udpParent);

    setAnimated(true);
    connect(this, &QTreeWidget::itemClicked, this, &ChannelTreeWidget::notifyItemSelected);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &ChannelTreeWidget::onCustomContextMenuRequested);
}

ChannelTreeWidget::~ChannelTreeWidget()
{

}

void ChannelTreeWidget::initMenuAction()
{
    m_parentNodeMenu.addAction(tr("Add Channel"), [this]{
        NamedDialog dlg(tr("Default Page"));
        if (dlg.exec() == QDialog::Accepted) {
            auto item = new QTreeWidgetItem(this, {dlg.getNameString()});
            QSharedPointer<SettingData> settingData(new SettingData());
            m_nodeSettingDatas.insert(item, settingData);

            emit notifyAddNewChannel(item, settingData);
        }
    });
    m_parentNodeMenu.addAction(tr("Delete Child Channel"), [this]{
        auto childrenChannel = m_currentPopupItem->takeChildren();
        if (childrenChannel.isEmpty()) {
            return;
        }
        for (auto& child : childrenChannel) {
            m_nodeSettingDatas.remove(child);
            emit notifyDeleteChannel(child);
        }
    });

    m_childNodeMenu.addAction(tr("Change Name"), [this]{
        NamedDialog dlg(m_currentPopupItem->text(0));
        if (dlg.exec() == QDialog::Accepted) {
            m_currentPopupItem->setText(0, dlg.getNameString());
            emit notifyChangeName(m_currentPopupItem);
        }
    });
    m_childNodeMenu.addAction(tr("Start"), [this]{
        emit notifyChannelStart(m_currentPopupItem);
    });
    m_childNodeMenu.addAction(tr("Stop"), [this]{
        emit notifyChannelStop(m_currentPopupItem);
    });
    m_childNodeMenu.addAction(tr("Delete"), [this]{
        m_nodeSettingDatas.remove(m_currentPopupItem);
        emit notifyDeleteChannel(m_currentPopupItem);
    });
}

void ChannelTreeWidget::onCustomContextMenuRequested(const QPoint &pos)
{
    auto popupItem = itemAt(pos);
    if (popupItem == nullptr) {
        return ;
    }

    m_currentPopupItem = popupItem;
    if (popupItem == m_tcpClientParent
       || popupItem == m_tcpServerParent
       || popupItem == m_udpParent) {
        // 显示菜单

        m_parentNodeMenu.exec(QCursor::pos());
    }
    else {
        m_childNodeMenu.exec(QCursor::pos());
    }
}
