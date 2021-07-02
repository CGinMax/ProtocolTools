#include "gathercontroller.h"
#include "../common/threadpool.h"
#include "serialport.h"

GatherController::GatherController(QObject *parent)
    : QObject(parent)
    , _gatherData(new GatherData())
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

bool GatherController::startCommunication(const QVariantMap& portMap)
{
    bool success = rawCommunicationBase()->open(PortParam(portMap));

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

void GatherController::queryGatherVersion(int addr)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(addr), _gatherData->gatherTimeout());
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

void GatherController::configureGatherAddress(int addr)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr), _gatherData->gatherTimeout());
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

void GatherController::configureSensorCount(int addr, int count)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(addr), static_cast<uint8_t>(count), _gatherData->gatherTimeout());
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
bool GatherController::canDoOperate()
{
    bool active = isConnected();
    return active;
}
