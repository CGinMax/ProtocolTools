#include "sensorconfiguremodel.h"

SensorConfigureModel::SensorConfigureModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    auto data = new YBSensorData("Sensor1");
//    data->setAddr(1);
//    data->setCurrentStatus(YBStatus::OnStatus);
//    data->setConfigedStatus(YBStatus::OnStatus);
//    data->setHardwareVersion("1.0");
//    data->setSoftwareVersion("1.0");
//    data->setProductDesc("this is a product description");
//    _gatherData->appendSensorData(QSharedPointer<YBSensorData>(data));
}

SensorConfigureModel::~SensorConfigureModel()
{

}

int SensorConfigureModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _ybSensorDataList.count();
}

QVariant SensorConfigureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (_ybSensorDataList.isEmpty()) {
        return QVariant();
    }

    if (index.row() >= _ybSensorDataList.count()) {
        return QVariant();
    }

    auto data = _ybSensorDataList.at(index.row());

    switch (role) {
    case SensorConfigureModel::Name:
        return data->name();
    case SensorConfigureModel::HardwareVersion:
        return data->hardwareVersion();
    case SensorConfigureModel::SoftwareVersion:
        return data->softwareVersion();
    case SensorConfigureModel::ProductDesc:
        return data->productDescription();
    case SensorConfigureModel::Address:
        return data->addr();
    case SensorConfigureModel::CurrentStatus:
        return data->currentStatus();
    case SensorConfigureModel::ConfiguredStatus:
        return data->configedStatus();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> SensorConfigureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(SensorConfigureModel::Name, QByteArrayLiteral("sensor_name"));
    roles.insert(SensorConfigureModel::HardwareVersion, QByteArrayLiteral("hardware_version"));
    roles.insert(SensorConfigureModel::SoftwareVersion, QByteArrayLiteral("software_version"));
    roles.insert(SensorConfigureModel::ProductDesc, QByteArrayLiteral("product_description"));
    roles.insert(SensorConfigureModel::Address, QByteArrayLiteral("address"));
    roles.insert(SensorConfigureModel::CurrentStatus, QByteArrayLiteral("current_status"));
    roles.insert(SensorConfigureModel::ConfiguredStatus, QByteArrayLiteral("configured_status"));
    roles.insert(SensorConfigureModel::Timeout, QByteArrayLiteral("timeout"));
    return roles;
}

void SensorConfigureModel::appendSensors(int count)
{
//    int lastAddr = 1;
//    if (!_gatherData->sensorDataList().isEmpty()) {
//        lastAddr = _gatherData->sensorDataList().last()->addr() + 1;
//    }
//    beginInsertRows(QModelIndex(), _gatherData->sensorDataList().count(), _gatherData->sensorDataList().count() - 1 + count);
//    for (int i = 0; i < count; i++, lastAddr++) {
//        auto sensorData = new YBSensorData(tr("Sensor #%1").arg(lastAddr));
//        sensorData->setAddr(lastAddr);
//        _gatherData->appendSensorData(QSharedPointer<YBSensorData>(sensorData));
//    }
//    endInsertRows();
}

void SensorConfigureModel::removeSensor(int index)
{
//    beginRemoveRows(QModelIndex(), index, index);
//    _gatherData->removeSensorData(index);
//    endRemoveRows();
}

void SensorConfigureModel::removeAll()
{
//    beginResetModel();
//    _gatherData->clearSensorDataList();
//    endResetModel();
}
