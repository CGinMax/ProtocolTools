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
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
//        this->m_table->setListItemVersion(index
//                                          , QString::fromStdString(result->hardwareVersion())
//                                          , QString::fromStdString(result->softwareVersion())
//                                          , QString::fromStdString(result->productDescript()));
    }, [this](){

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
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
//        this->m_table->setListItemStatus(index, result->currentStatusCode(), result->configedStatusCode());
    }, [this](){
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
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
        if (result->success()) {
//            this->m_table->setListItemAddr(index, addr);
//            this->onQuerySensorStatus(index, addr);
        } else {
            qDebug("set sensor address failed!");
        }
    }, [this](){
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
        if (result == nullptr) {

            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
        if (result->success()) {
//            this->m_table->setListItemConfigedStatus(index, static_cast<uint8_t>(status & 0xFF));
        } else {

            qDebug("change status failed!");
        }
    }, [this](){

        qDebug("change status timeout!");
    });
}

bool SensorController::canDoOperate()
{

}
