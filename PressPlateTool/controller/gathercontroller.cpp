#include "gathercontroller.h"
#include "../common/threadpool.h"
#include "serialport.h"

GatherController::GatherController(QObject *parent)
    : QObject(parent)
    , _communication(new SerialPort(this))
{
    ThreadPool::instance()->run([=]{
        this->_protocol.reset(new YBProtocolChannel(this->_communication));
        // TODO(shijm): check whether use BlockingQueuedConnection
        connect(this, &GatherController::startPortocolChannel, this->protocol(), &ProtocolChannelBase::start, Qt::BlockingQueuedConnection);
        connect(this, &GatherController::stopProtocolChannel, this->protocol(), &ProtocolChannelBase::stop, Qt::BlockingQueuedConnection);
    });
}

GatherController::~GatherController()
{
    stopCommunication();
}

CommunicationBase *GatherController::rawCommunicationBase()
{
    return _communication.data();
}

//void GatherController::appendSensorData(YBSensorData *data)
//{
//    if (_gatherData.isNull()) {
//        return;
//    }
//    _gatherData->appendSensorData(data);
//}

bool GatherController::startCommunication(QObject* param)
{
    bool success = false;
    if (param != nullptr) {
        auto portParam = static_cast<PortParam*>(param);
        success = rawCommunicationBase()->open(*portParam);
        delete portParam;
    }

    if (success) {
        emit startPortocolChannel();
    }
    return success;
}

bool GatherController::stopCommunication()
{
    emit stopProtocolChannel();
    rawCommunicationBase()->close();
    return !isConnected();
}

void GatherController::queryGatherVersion(int addr, int timeout)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            emit this->queryVersionCallback(
                    true, QString::fromStdString(result->hardwareVersion())
                    , QString::fromStdString(result->softwareVersion()) , QString::fromStdString(result->productDescript())
            );
            qDebug("query gather version success");
            return ;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->queryVersionCallback(false);

    }, [=](){
        emit this->queryVersionCallback(false);
        qDebug("gather query version timeout cancel");
    });
}

void GatherController::configureGatherAddress(int addr, int timeout)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            emit this->configureAddressCallback(result->success(), addr);
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->configureAddressCallback(false);
    },
    [=]() {
        emit this->configureAddressCallback(false);
        qDebug("gather set address timeout cancel");
    });

}

void GatherController::configureSensorCount(int addr, int count, int timeout)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(addr), static_cast<uint8_t>(count), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            emit this->configureCountCallback(result->success(), count);
            return;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->configureCountCallback(false);
    },
    [=](){
        emit this->configureCountCallback(false);
        qDebug("gather set sensor num timeout cancel");
    });
}

bool GatherController::isConnected()
{
    return !_communication.isNull() && _communication->isActived();
}

YBProtocolChannel *GatherController::protocol()
{
    return static_cast<YBProtocolChannel*>(_protocol.data());
}

//void GatherController::onTitleChanged(const QString &title)
//{
//    _gatherData->setName(title);
//}
bool GatherController::canDoOperate()
{
    bool active = isConnected();
    return active;
}
