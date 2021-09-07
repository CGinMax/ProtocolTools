#include "sensorconfiguremodel.h"

QStringList SensorConfigureModel::CURSTATUSDESC = {tr("Open"), tr("Close"), tr("Error Open"), tr("Error Close"), tr("Waiting Open"), tr("Waiting Close")};
QMap<int, QString> SensorConfigureModel::CONFIGSTATUSDESC = {{0, tr("Open")}, {1, tr("Close")}, {0xFF, tr("Unconfigured")}};

SensorConfigureModel::SensorConfigureModel(QObject *parent)
    : QAbstractListModel(parent)
{

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
    case SensorConfigureModel::CurrentStatusText:
        return CURSTATUSDESC.at(data->currentStatus());
    case SensorConfigureModel::ConfiguredStatusText:
        return CONFIGSTATUSDESC.value(data->configedStatus(), tr("Unconfigured"));
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

    roles.insert(SensorConfigureModel::CurrentStatusText, QByteArrayLiteral("current_status_text"));
    roles.insert(SensorConfigureModel::ConfiguredStatusText, QByteArrayLiteral("configured_status_text"));
    return roles;
}

void SensorConfigureModel::appendSensors(int count)
{
    int lastAddr = 1;
    if (!_ybSensorDataList.isEmpty()) {
        lastAddr = _ybSensorDataList.last()->addr() + 1;
    }
    beginInsertRows(QModelIndex(), _ybSensorDataList.count(), _ybSensorDataList.count() - 1 + count);
    for (int i = 0; i < count; i++, lastAddr++) {
        auto sensorData = new YBSensorData(tr("Sensor #%1").arg(lastAddr));
        sensorData->setAddr(lastAddr);
        _ybSensorDataList.append(QSharedPointer<YBSensorData>(sensorData));
    }
    endInsertRows();
}

void SensorConfigureModel::appendSensors(int beginNum, int count)
{

    beginInsertRows(QModelIndex(), _ybSensorDataList.count(), _ybSensorDataList.count() - 1 + count);
    for (int i = 0; i < count; i++, beginNum++) {
        auto sensorData = new YBSensorData(tr("Sensor #%1").arg(beginNum));
        sensorData->setAddr(beginNum);
        _ybSensorDataList.append(QSharedPointer<YBSensorData>(sensorData));
    }
    endInsertRows();

}

void SensorConfigureModel::removeSensor(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _ybSensorDataList.removeAt(index);
    endRemoveRows();
}

void SensorConfigureModel::removeAll()
{
    beginResetModel();
    _ybSensorDataList.clear();
    endResetModel();
}

void SensorConfigureModel::setVersion(int idx, const QString &hardware, const QString &software, const QString &product)
{
    if (outOfRange(idx)) {
        return;
    }
    _ybSensorDataList.at(idx)->setHardwareVersion(hardware);
    _ybSensorDataList.at(idx)->setSoftwareVersion(software);
    _ybSensorDataList.at(idx)->setProductDesc(product);
    emit dataChanged(index(idx, 0), index(idx, 0));
}

void SensorConfigureModel::setState(int idx, int curState, int confState)
{
    if (outOfRange(idx)) {
        return;
    }
    _ybSensorDataList.at(idx)->setCurrentStatus(YBStatus(curState));
    _ybSensorDataList.at(idx)->setConfigedStatus(YBStatus(confState));
    emit dataChanged(index(idx, 0), index(idx, 0));
}

void SensorConfigureModel::setAddress(int idx, int addr)
{
    if (outOfRange(idx)) {
        return;
    }
    _ybSensorDataList.at(idx)->setAddr(static_cast<uint8_t>(addr));
    emit dataChanged(index(idx, 0), index(idx, 0));
}

void SensorConfigureModel::setConfState(int idx, int state)
{
    if (outOfRange(idx)) {
        return;
    }
    _ybSensorDataList.at(idx)->setConfigedStatus(YBStatus(state));
    emit dataChanged(index(idx, 0), index(idx, 0));
}

QString SensorConfigureModel::getName(int idx)
{
    if (outOfRange(idx)) {
        return QString();
    }
    return _ybSensorDataList.at(idx)->name();
}

int SensorConfigureModel::getAddr(int idx)
{
    if (outOfRange(idx)) {
        return 0;
    }
    return _ybSensorDataList.at(idx)->addr();
}

bool SensorConfigureModel::outOfRange(int index)
{
    return index < 0 || index >= _ybSensorDataList.count();
}
