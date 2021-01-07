#include "aitablemodel.h"
#include "aidata.h"
#include <QRandomGenerator>

AiTableModel::AiTableModel(const QStringList &headers, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_ptCfg(new PtCfg)
{

}

AiTableModel::AiTableModel(const QStringList &headers, const QSharedPointer<PtCfg> &ptCfg, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_ptCfg(ptCfg)
{

}

AiTableModel::~AiTableModel()
{

}

int AiTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ptCfg->m_globalAiList->count();
}

int AiTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.count();
}

QVariant AiTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0://序号
            return m_ptCfg->m_globalAiList->at(index.row()).io();
        case 1:
            return m_ptCfg->m_globalAiList->at(index.row()).name();
        case 2:
            return m_ptCfg->m_globalAiList->at(index.row()).value();
        }
    }

    return QVariant();
}

bool AiTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == Qt::EditRole) {
        if (index.column() == 2) {
            if (!value.canConvert<double>()) {
                return false;
            }
            (*m_ptCfg->m_globalAiList)[index.row()].setValue(value.toInt());
            dataChanged(index, index);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags AiTableModel::flags(const QModelIndex &index) const
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

QVariant AiTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void AiTableModel::appendRow(const QModelIndex &parent)
{
    int row = m_ptCfg->m_globalAiList->count();
    beginInsertRows(parent, row, row);
    AiData di(0, "0", 100);

    m_ptCfg->m_globalAiList->append(di);
    endInsertRows();
}

void AiTableModel::resetDatas(int num)
{
    beginResetModel();
    m_ptCfg->m_globalAiList->clear();
    for (int i = 0; i < num; i++) {
        m_ptCfg->m_globalAiList->append(AiData(i, QString("Pt%1").arg(i), num + 1));
    }
    endResetModel();
}

void AiTableModel::randomNumber()
{
    for (int i = 0; i < m_ptCfg->m_globalAiList->size(); i++) {
        (*m_ptCfg->m_globalAiList)[i].setValue(QRandomGenerator::global()->bounded(0, 255));
    }
}
