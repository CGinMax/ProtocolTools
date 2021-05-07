#include "ybtablemodel.h"
#include <QSize>

YBTableModel::YBTableModel(const QStringList &headers, QObject *parent)
    : QAbstractListModel(parent)
    , m_headers(headers)
{

}


int YBTableModel::rowCount(const QModelIndex &parent) const
{
    return dataList.count();
}

QVariant YBTableModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= dataList.count()) {
        return QVariant();
    }

    switch (role) {
    case Qt::UserRole + 1:
        return "1";
    case Qt::UserRole +2:
        return "1.2";
    case Qt::SizeHintRole:
        return QSize(100, 60);
    }

    return QVariant();
}

QHash<int, QByteArray> YBTableModel::roleNames() const
{
    return {{Qt::UserRole + 1, "Id"}, {Qt::UserRole + 2, "Version"}};
}

void YBTableModel::append()
{
    beginInsertRows(QModelIndex(), 0, 1);
    dataList.append("112211");
    endInsertRows();
}


bool YBTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == Qt::EditRole) {
        if (index.column() == 0) {

//            m_aiDatas->at(index.row())->setValue(value.toDouble());
            dataChanged(index, index);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags YBTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QAbstractListModel::flags(index);
    }

    Qt::ItemFlags flags = Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable;
    return flags |= Qt::ItemFlag::ItemIsEditable;

//    return QAbstractListModel::flags(index);
}
