#include "sensorcontroller.h"
using namespace std::placeholders;
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
        if (!this->error(result, std::bind(&SensorController::queryVersionCallback, this, _1))) {
            return ;
        }
        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("hardware"), QString::fromStdString(result->hardwareVersion()));
        map.insert(QLatin1String("software"), QString::fromStdString(result->softwareVersion()));
        map.insert(QLatin1String("product"), QString::fromStdString(result->productDescript()));
        emit this->queryVersionCallback(map);

    }, [this](){
        emit this->queryVersionCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query version timeout!")}});
    });
}

void SensorController::querySensorStatus(int addr, int timeout)
{
    auto reply = _controller->protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&SensorController::queryStateCallback, this, _1))) {
            return ;
        }

        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("curState"), result->currentStatusCode());
        map.insert(QLatin1String("confState"), result->configedStatusCode());
        emit this->queryStateCallback(map);

    }, [this](){
        emit this->queryStateCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query state timeout!")}});
    });
}

void SensorController::configureSensorAddress(int addr, int timeout)
{
    auto reply = _controller->protocol()->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&SensorController::configureAddressCallback, this, _1))) {
            return ;
        }

        QString errorMsg = result->success() ? "" : tr("Configure sensor address failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("errorMsg"), errorMsg);

        emit this->configureAddressCallback(map);
    }, [=](){
        emit this->configureAddressCallback({{QString("success"), false},
                                             {QString("errorMsg"), tr("Configure sensor address timeout!")}});
    });
}

void SensorController::configureSensorStatus(int addr, int status, int timeout)
{
    auto reply = _controller->protocol()->setStatus(static_cast<uint8_t>(status & 0xFF), static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result) {
        if (!this->error(result, std::bind(&SensorController::configureStateCallback, this, _1))) {
            return ;
        }

        QString errorMsg = result->success() ? "" : tr("Configure state failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("state"), status);
        map.insert(QLatin1String("errorMsg"), errorMsg);

        emit this->configureStateCallback(map);
    }, [this](){
        emit this->configureStateCallback({{QString("success"), false},
                                           {QString("errorMsg"), tr("Configure sensor state timeout!")}});
    });
}

void SensorController::querySensorAddr(int timeout)
{
    auto reply = _controller->protocol()->querySensorAddr(timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result) {
        if (!this->error(result, std::bind(&SensorController::queryAddrCallback, this, _1))) {
            return ;
        }
        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("addr"), result->responseAddr());
        emit this->queryAddrCallback(map);
    }, [this]() {
        emit this->queryAddrCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query sensor addr timeout!")}});
    });
}

bool SensorController::error(const std::shared_ptr<IContent> &result, const std::function<void (const QVariantMap &)>& callback)
{
    return _controller->error(result, callback);
}
