#include "gatherconfiguremodel.h"
#include "portparam.h"

GatherConfigureModel::GatherConfigureModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    auto data = new GatherData("Gather1");
//    data->setAddr(1);
//    data->setSensorCount(10);
//    data->setHardwareVerion("1.0");
//    data->setSoftwareVersion("1.0");
//    data->setProductDesc("this is a product description");
//    _gatherDataList.append(QSharedPointer<GatherData>(data));
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
    case GatherConfigureModel::Timeout:
        return data->gatherTimeout();
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
    roles.insert(GatherConfigureModel::Timeout, QByteArrayLiteral("timeout"));
    return roles;
}

void GatherConfigureModel::appendGathers(int count, const QVariantMap &map)
{
    PortParam portParam(map);
    int lastAddr = 1;
    if (!_gatherDataList.isEmpty()) {
        lastAddr = _gatherDataList.last()->addr() + 1;
    }
    beginInsertRows(QModelIndex(), _gatherDataList.count(), _gatherDataList.count() -1 + count);
    for (int i = 0; i < count; i++, lastAddr++) {
        QSharedPointer<GatherData> data(new GatherData(QString("Gather%1").arg(lastAddr)));
        data->setAddr(lastAddr);
        data->setPortParam(portParam);
        _gatherDataList.append(data);
    }
    endInsertRows();
}

void GatherConfigureModel::removeGather(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _gatherDataList.erase(_gatherDataList.begin() + index);
    endRemoveRows();
}

void GatherConfigureModel::removeAll()
{
    beginResetModel();
    _gatherDataList.clear();
    endResetModel();
}

void GatherConfigureModel::updateVersion(int row, const QString &hardware, const QString &software, const QString &product)
{
    if (outOfRange(row)) {
        return;
    }
    _gatherDataList.at(row)->setHardwareVerion(hardware);
    _gatherDataList.at(row)->setSoftwareVersion(software);
    _gatherDataList.at(row)->setProductDesc(product);
    emit dataChanged(index(row, 0), index(row, 0), {GatherConfigureModel::HardwareVersion, GatherConfigureModel::SoftwareVersion, GatherConfigureModel::ProductDesc});
}

void GatherConfigureModel::updateAddress(int row, int addr)
{
    if (outOfRange(row)) {
        return;
    }
    _gatherDataList.at(row)->setAddr(addr);
    emit dataChanged(index(row, 0), index(row, 0), {GatherConfigureModel::Address});
}

void GatherConfigureModel::updateSensorCount(int row, int count)
{
    if (outOfRange(row)) {
        return;
    }
    _gatherDataList.at(row)->setSensorCount(count);
    emit dataChanged(index(row, 0), index(row, 0), {GatherConfigureModel::SensorCount});
}

QObject* GatherConfigureModel::portParam(int index)
{
    if (outOfRange(index)) {
        return nullptr;
    }
    return new PortParam(_gatherDataList.at(index)->portParam());
}

bool GatherConfigureModel::outOfRange(int index)
{
    return index < 0 || index >= _gatherDataList.count() ;
}
