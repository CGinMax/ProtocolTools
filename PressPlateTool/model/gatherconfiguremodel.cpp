#include "gatherconfiguremodel.h"

GatherConfigureModel::GatherConfigureModel(QObject *parent)
    : QAbstractListModel(parent)
{

}


int GatherConfigureModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_gatherDataList.count();
}

QVariant GatherConfigureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case GatherConfigureModel::Name:
        break;
    case GatherConfigureModel::HardwareVersion:
        break;
    case GatherConfigureModel::SoftwareVersion:
        break;
    case GatherConfigureModel::Address:
        break;
    }

    return QVariant();
}


QHash<int, QByteArray> GatherConfigureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(GatherConfigureModel::Name, QByteArrayLiteral("gather_name"));
    roles.insert(GatherConfigureModel::HardwareVersion, QByteArrayLiteral("hardware_version"));
    roles.insert(GatherConfigureModel::SoftwareVersion, QByteArrayLiteral("software_version"));
    roles.insert(GatherConfigureModel::Address, QByteArrayLiteral("address"));

    return roles;
}
