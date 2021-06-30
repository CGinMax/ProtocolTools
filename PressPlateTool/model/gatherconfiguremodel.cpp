#include "gatherconfiguremodel.h"
#include <QDebug>
GatherConfigureModel::GatherConfigureModel(QObject *parent)
    : QAbstractListModel(parent)
{
    auto data = new GatherData("Gather1");
    data->setAddr(1);
    data->setSensorCount(10);
    data->setHardwareVerion("1.0");
    data->setSoftwareVersion("1.0");
    data->setProductDesc("this is a product description");
    _gatherDataList.append(QSharedPointer<GatherData>(data));
}

GatherConfigureModel::~GatherConfigureModel()
{

}

int GatherConfigureModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _gatherDataList.count();
}

QVariant GatherConfigureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= _gatherDataList.count()) {
        return QVariant();
    }

    auto data = _gatherDataList.at(index.row());

    switch (role) {
    case GatherConfigureModel::Name:
        return data->name();
    case GatherConfigureModel::HardwareVersion:
        return data->hardwareVersion();
    case GatherConfigureModel::SoftwareVersion:
        return data->softwareVersion();
    case GatherConfigureModel::ProductDesc:
        return data->productDescription();
    case GatherConfigureModel::Address:
        return data->addr();
    case GatherConfigureModel::SensorCount:
        return data->sensorCount();
    case GatherConfigureModel::QueryVersionState:
        return data->queryVersionState();
    case GatherConfigureModel::ConfigureAddrState:
        return data->configureAddrState();
    case GatherConfigureModel::SensorCountState:
        return data->sensorCountState();
    default:
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
    roles.insert(GatherConfigureModel::ProductDesc, QByteArrayLiteral("product_description"));
    roles.insert(GatherConfigureModel::Address, QByteArrayLiteral("address"));
    roles.insert(GatherConfigureModel::SensorCount, QByteArrayLiteral("sensor_count"));
    roles.insert(GatherConfigureModel::QueryVersionState, QByteArrayLiteral("query_version_state"));
    roles.insert(GatherConfigureModel::ConfigureAddrState, QByteArrayLiteral("configure_addr_state"));
    roles.insert(GatherConfigureModel::SensorCountState, QByteArrayLiteral("sensor_count_state"));
    return roles;
}

void GatherConfigureModel::appendGatherList(const QList<QSharedPointer<GatherData> > &dataList)
{
    beginInsertRows(QModelIndex(), _gatherDataList.count(), _gatherDataList.count() -1 + dataList.count());
    _gatherDataList.append(dataList);
    endInsertRows();
}


void GatherConfigureModel::removeGather(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _gatherDataList.erase(_gatherDataList.begin() + index);
    endRemoveRows();
}

QList<QSharedPointer<GatherData> > GatherConfigureModel::gatherDataList() const
{
    return _gatherDataList;
}

void GatherConfigureModel::onUpdateData()
{
    emit dataChanged(index(0, 0), index(rowCount(QModelIndex()) - 1, 0));
}
