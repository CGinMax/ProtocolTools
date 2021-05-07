#include "listdelegate.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ListDelegate::ListDelegate(QAbstractListModel *model, QObject *parent)
    : QItemDelegate(parent)
    , m_model(model)
{

}


QWidget *ListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto item = new ListViewItem(parent);
    QString id = m_model->data(index, m_model->roleNames().key("Id")).toString();
    QString version = m_model->data(index, m_model->roleNames().key("Version")).toString();
    item->setId(id);
    item->setVersion(version);

    return item;
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
