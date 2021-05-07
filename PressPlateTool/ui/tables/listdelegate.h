#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QAbstractListModel>
#include "listviewitem.h"
class ListDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ListDelegate(QAbstractListModel* model, QObject *parent = nullptr);

signals:

public slots:

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QAbstractListModel* m_model;
};

#endif // LISTDELEGATE_H
