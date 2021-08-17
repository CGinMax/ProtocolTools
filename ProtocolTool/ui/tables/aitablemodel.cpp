#include "aitablemodel.h"
#include <QRandomGenerator>

AiTableModel::AiTableModel(const QStringList &headers, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_aiDatas(nullptr)
    , m_isRandom(false)
{

}

AiTableModel::AiTableModel(const QStringList &headers, QList<AiData *> *aiDatas, QObject *parent)
    : QAbstractTableModel(parent)
    , m_headers(headers)
    , m_aiDatas(aiDatas)
    , m_isRandom(false)
{

}

AiTableModel::~AiTableModel()
{

}

int AiTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_aiDatas->count();
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
            return m_aiDatas->at(index.row())->io();
        case 1:
            return m_aiDatas->at(index.row())->name();
        case 2:
            return m_aiDatas->at(index.row())->value();
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
            m_aiDatas->at(index.row())->setValue(value.toDouble());
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
    int row = m_aiDatas->count();
    beginInsertRows(parent, row, row);
    auto ai = new AiData(0, "0", 100);
    m_aiDatas->append(ai);
    endInsertRows();
}

void AiTableModel::resetDatas(QList<AiData *> *aiDatas)
{
    beginResetModel();
    m_aiDatas = aiDatas;
    endResetModel();
}

void AiTableModel::onNotifyRandom(bool isRandom)
{
    m_isRandom = isRandom;
}

void AiTableModel::randomNumber()
{
    if (!m_isRandom) {
        return ;
    }
    for (int i = 0; i < m_aiDatas->size(); i++) {
        m_aiDatas->at(i)->setValue(QRandomGenerator::global()->bounded(static_cast<double>(0x7FF)));
    }
}
