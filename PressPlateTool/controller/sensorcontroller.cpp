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
    auto reply = _controller->protocol()->queryVersion(eYBFrameType::YBSensor, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            QVariantMap map;
            map.insert(QLatin1String("success"), true);
            map.insert(QLatin1String("hardware"), QString::fromStdString(result->hardwareVersion()));
            map.insert(QLatin1String("software"), QString::fromStdString(result->softwareVersion()));
            map.insert(QLatin1String("product"), QString::fromStdString(result->productDescript()));
            emit this->queryVersionCallback(map);
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }

        emit this->queryVersionCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query version failed!")}});

    }, [this](){
        emit this->queryVersionCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query version timeout!")}});
    });
}

void SensorController::querySensorStatus(int addr, int timeout)
{
    auto reply = _controller->protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            QVariantMap map;
            map.insert(QLatin1String("success"), true);
            map.insert(QLatin1String("curState"), result->currentStatusCode());
            map.insert(QLatin1String("confState"), result->configedStatusCode());
            emit this->queryStateCallback(map);
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->queryStateCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query state failed!")}});
    }, [this](){
        emit this->queryStateCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query state timeout!")}});
    });
}

void SensorController::configureSensorAddress(int addr, int timeout)
{
    auto reply = _controller->protocol()->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        QString errorMsg = result->success() ? "" : tr("Configure address failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("errorMsg"), errorMsg);
        if (result == nullptr) {
            qDebug("Unknow frame data");
        } else if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }

        emit this->configureAddressCallback(map);
    }, [=](){
        emit this->configureAddressCallback({{QString("success"), false}, {QString("addr"), addr},
                                             {QString("errorMsg"), tr("Configure address timeout!")}});
    });
}

void SensorController::configureSensorStatus(int addr, int status, int timeout)
{
    auto reply = _controller->protocol()->setStatus(static_cast<uint8_t>(status & 0xFF), static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        QString errorMsg = result->success() ? "" : tr("Configure state failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("state"), status);
        map.insert(QLatin1String("errorMsg"), errorMsg);
        if (result == nullptr) {
            qDebug("Unknow frame data");
        } else if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }

        emit this->configureStateCallback(map);
    }, [this](){
        emit this->configureStateCallback({{QString("success"), false}, {QString("errorMsg"), tr("Configure state timeout!")}});
    });
}
