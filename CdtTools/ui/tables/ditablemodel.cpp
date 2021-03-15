#include <utility>

#include "ditablemodel.h"

DiTableModel::DiTableModel(const QStringList &headers, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_diDatas(nullptr)
{
}

DiTableModel::DiTableModel(const QStringList &headers, QList<DiData *> *diDatas, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_diDatas(diDatas)
{

}

DiTableModel::~DiTableModel()
{

}

int DiTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_diDatas->size();
}

int DiTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.count();
}

QVariant DiTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0://序号
            return m_diDatas->at(index.row())->io();
        case 1:
            return m_diDatas->at(index.row())->name();
        case 2:
            return m_diDatas->at(index.row())->value() ? QStringLiteral("合") : QStringLiteral("分");
        }
    }

    return QVariant();
}

bool DiTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == Qt::EditRole) {
        if (index.column() == 2) {

            bool offon = value.toString() == QStringLiteral("合") ? true : false;
            m_diDatas->at(index.row())->setValue(offon);
            dataChanged(index, index);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags DiTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QAbstractTableModel::flags(index);
    }

    Qt::ItemFlags flags = Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable;
    if (index.column() == 2) {
        return flags |= Qt::ItemFlag::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}

QVariant DiTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((Qt::DisplayRole!=role)||(Qt::Vertical==orientation))
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }
    if((-1 < section) && (section < m_headers.count()))
    {
        return m_headers.at(section);
    }
    return QVariant();
}


void DiTableModel::insertRow(DiData *diData, const QModelIndex &parent)
{
    int row = m_diDatas->count();
    beginInsertRows(parent, row, row);
    m_diDatas->append(diData);
    endInsertRows();
}

void DiTableModel::resetDatas(QList<DiData *> *diDatas)
{
    beginResetModel();
    m_diDatas = diDatas;
    endResetModel();

}

void DiTableModel::onNotifyAllChanged(bool offon)
{
    for (auto& di : *m_diDatas) {
        di->setValue(offon);
    }
    dataChanged(index(0, columnCount(QModelIndex()) - 1), index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1));
}
