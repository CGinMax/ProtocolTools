#include "ybtablemodel.h"
#include <QSize>

YBTableModel::YBTableModel(const QStringList &headers, QObject *parent)
    : QAbstractListModel(parent)
    , m_headers(headers)
{
    m_roleNames = {{RoleId, QByteArray("Id")}
              ,{RoleAddress, QByteArray("Address")}
              ,{RoleVersion, QByteArray("Version")}
              ,{RoleCurrentStatus, QByteArray("CurrentStatus")}
              ,{RoleConfigedStatus, QByteArray("ConfigedStatus")}};
}

int YBTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_sensorDataList.count();
}

QVariant YBTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_sensorDataList.count()) {
        return QVariant();
    }

    switch (role) {
    case RoleId:
        return index.row() + 1;
    case RoleAddress:
        return m_sensorDataList.at(index.row()).addr();
    case RoleVersion:
        return m_sensorDataList.at(index.row()).version();
    case RoleCurrentStatus:
        return m_sensorDataList.at(index.row()).currentStatus();
    case RoleConfigedStatus:
        return m_sensorDataList.at(index.row()).configedStatus();
    case Qt::SizeHintRole:
        return QSize(100, 130);
    }

    return QVariant();
}

QHash<int, QByteArray> YBTableModel::roleNames() const
{
    return m_roleNames;
}

void YBTableModel::append()
{
    beginInsertRows(QModelIndex(), m_sensorDataList.count(), m_sensorDataList.count() + 1);
    YBSensorData data;
    data.setAddr(1);
    m_sensorDataList.append(data);
    endInsertRows();
}

void YBTableModel::clearAllSensor()
{
    beginRemoveRows(QModelIndex(), 0, m_sensorDataList.count());

    m_sensorDataList.clear();
    endRemoveRows();
}


bool YBTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
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
