#include "sensorcontroller.h"

SensorController::SensorController(QObject *parent)
    : QObject(parent)
    , _controller(nullptr)
{

}

void SensorController::setGatherController(GatherController *controller)
{
    _controller = controller;
}

GatherController *SensorController::gatherController()
{
    return _controller;
}

bool SensorController::isConnected()
{
    return _controller->isConnected();
}

void SensorController::querySensorVersion(int addr, int timeout)
{
    if (!canDoOperate()) {
        return;
    }

    auto reply = _controller->protocol()->queryVersion(eYBFrameType::YBSensor, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            emit this->queryVersionCallback(
                    true, QString::fromStdString(result->hardwareVersion())
                    , QString::fromStdString(result->softwareVersion()) , QString::fromStdString(result->productDescript())
            );
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->queryVersionCallback(false);

    }, [this](){
        emit this->queryVersionCallback(false);
        qDebug("query sensor version timeout!");
    });
}

void SensorController::querySensorStatus(int addr, int timeout)
{
    if (!canDoOperate()) {
        return;
    }

    auto reply = _controller->protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            emit this->queryStateCallback(true, result->currentStatusCode(), result->configedStatusCode());
            qDebug("curstatus:%d,config:%d", result->currentStatusCode(), result->configedStatusCode());
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->queryStateCallback(false);
    }, [this](){
        emit this->queryStateCallback(false);
        qDebug("query sensor status timeout!");
    });
}

void SensorController::configureSensorAddress(int addr, int timeout)
{
    if (!canDoOperate()) {
        return;
    }

    auto reply = _controller->protocol()->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode
                && result->success()) {
            emit this->configureAddressCallback(true, addr);
            return;
        }

        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        qDebug("set sensor address failed!");
        emit this->configureAddressCallback(false);
    }, [this](){
        emit this->configureAddressCallback(false);
        qDebug("set sensor address timeout!");
    });
}

void SensorController::configureSensorStatus(int addr, int status, int timeout)
{
    if (!canDoOperate()) {
        return;
    }

    auto reply = _controller->protocol()->setStatus(static_cast<uint8_t>(status & 0xFF), static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode
                && result->success()) {
            emit this->configureStateCallback(true, status);
            qDebug("curstatus:%d", status);
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");

        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");

        }

        qDebug("change status failed!");
        emit this->configureStateCallback(false);
    }, [this](){
        emit this->configureStateCallback(false);
        qDebug("change status timeout!");
    });
}

bool SensorController::canDoOperate()
{
    return _controller->canDoOperate();
}
