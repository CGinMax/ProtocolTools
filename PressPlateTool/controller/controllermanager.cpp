#include "controllermanager.h"
#include "portparam.h"

#include <QVector>

ControllerManager::ControllerManager(QObject *parent)
    : QObject(parent)
    , _gatherModel(nullptr)
{

}

ControllerManager::~ControllerManager()
{

}

void ControllerManager::addGatherConfig(int count, const QVariantMap& map)
{
    PortParam portParam(map);
    int lastAddr = 1;
    if (!_gatherModel->gatherDataList().isEmpty()) {
        auto dataList = _gatherModel->gatherDataList();
        lastAddr = dataList.last()->addr();
    }
    QList<QSharedPointer<GatherData>> dataList;
    for (int i = 0; i < count; i++, lastAddr++) {
        QSharedPointer<GatherData> data(new GatherData(QString("Gather%1").arg(lastAddr)));
        data->setAddr(lastAddr);
        data->setPortParam(portParam);
        dataList.append(data);

        auto controller = QSharedPointer<GatherController>(new GatherController(data, this));
        connect(controller.data(), &GatherController::updateData, gatherModel(), &GatherConfigureModel::onUpdateData);
        _controllers.append(controller);

    }
    _gatherModel->appendGatherList(dataList);
}

void ControllerManager::removeController(int index)
{
    if (isOutOfRange(index)) {
        return ;
    }
    _controllers.erase(_controllers.begin() + index);
}

void ControllerManager::queryVersion(int index)
{
    if (isOutOfRange(index)) {
        return ;
    }
    _controllers.at(index)->queryGatherVersion();
}

void ControllerManager::configureAddress(int index, int addr)
{
    if (isOutOfRange(index)) {
        return ;
    }
    _controllers.at(index)->configureGatherAddress(addr);
}

void ControllerManager::configureSensorCount(int index, int count)
{
    if (isOutOfRange(index)) {
        return;
    }
    _controllers.at(index)->configureGatherAddress(count);
}

bool ControllerManager::toggleCommunication(int index)
{
    if (isOutOfRange(index)) {
        return false;
    }
    if (isConnected(index)) {
        return _controllers.at(index)->stopCommunication();
    }

    return _controllers.at(index)->startCommunication();
}

bool ControllerManager::isConnected(int index)
{
    if (isOutOfRange(index)) {
        return false;
    }
    return _controllers.at(index)->isConnected();
}

void ControllerManager::setGatherModel(GatherConfigureModel *model)
{
    _gatherModel = model;
}

GatherConfigureModel *ControllerManager::gatherModel()
{
    return _gatherModel;
}

bool ControllerManager::isOutOfRange(int index)
{
    return index < 0 || index >= _controllers.count();
}
