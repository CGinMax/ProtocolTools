#include <utility>

#include "ditablemodel.h"

DiTableModel::DiTableModel(const QStringList &headers, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_ptCfg(new PtCfg)
{
}

DiTableModel::DiTableModel(const QStringList &headers, const QSharedPointer<PtCfg> &ptcfg, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_ptCfg(ptcfg)
{

}

DiTableModel::~DiTableModel()
{

}

int DiTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ptCfg->m_globalDiList->size();
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
            return m_ptCfg->m_globalDiList->at(index.row()).io();
        case 1:
            return m_ptCfg->m_globalDiList->at(index.row()).name();
        case 2:
            return m_ptCfg->m_globalDiList->at(index.row()).value() ? QStringLiteral("合") : QStringLiteral("分");
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
            (*m_ptCfg->m_globalDiList)[index.row()].setValue(offon);
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


void DiTableModel::insertRow(const DiData &diData, const QModelIndex &parent)
{
    int row = m_ptCfg->m_globalDiList->count();
    beginInsertRows(parent, row, row);
    m_ptCfg->m_globalDiList->append(diData);
    endInsertRows();
}

void DiTableModel::resetDatas(int num)
{
    beginResetModel();
    m_ptCfg->m_globalDiList->clear();
    for (int i = 0; i < num; i++) {
        m_ptCfg->m_globalDiList->append(DiData(i, QString("Pt%1").arg(i), false));
    }
    endResetModel();

}

void DiTableModel::setPtCfg(QSharedPointer<PtCfg> &ptcfg)
{
    m_ptCfg = ptcfg;
}

