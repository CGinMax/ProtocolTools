#include "listdelegate.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ListDelegate::ListDelegate(QAbstractListModel *model, QObject *parent)
    : QItemDelegate(parent)
    , m_model(model)
    , m_listItem(new ListViewItem)
{
}

ListDelegate::~ListDelegate()
{
}

QWidget *ListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    m_listItem->setParent(parent);
    return m_listItem;
}

void ListDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{

}

void ListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void ListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void ListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

ListViewItem *ListDelegate::getListItem()
{
    return m_listItem;
}
