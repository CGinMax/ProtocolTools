#include "gathercontroller.h"
#include "../common/threadpool.h"
#include "serialport.h"

GatherController::GatherController(const QSharedPointer<GatherData> &data, QObject *parent)
    : QObject(parent)
    , _gatherData(data)
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

GatherData *GatherController::rawGatherData()
{
    return _gatherData.data();
}

void GatherController::setGatherData(const QSharedPointer<GatherData> &gatherData)
{
    _gatherData = gatherData;
}

CommunicationBase *GatherController::rawCommunicationBase()
{
    return _communication.data();
}

void GatherController::appendSensorData(YBSensorData *data)
{
    if (_gatherData.isNull()) {
        return;
    }
    _gatherData->appendSensorData(data);
}

bool GatherController::startCommunication()
{
    bool success = rawCommunicationBase()->open(rawGatherData()->portParam());
    if (success) {
        emit startPortocolChannel();
    }
    return success;
}

void GatherController::stopCommunication()
{
    emit stopProtocolChannel();
    rawCommunicationBase()->close();
}

void GatherController::queryGatherVersion()
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(_gatherData->addr()), _gatherData->gatherTimeout());
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
        this->setHardwareVersion(QString::fromStdString(result->hardwareVersion()))
        ->setSoftwareVersion(QString::fromStdString(result->softwareVersion()))
        ->setProductDesc(QString::fromStdString(result->productDescript()));

    }, [](){
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
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
        if (result->success()) {
            this->setAddress(addr);
        } else {
            //TODO(shijm): 失败处理
            qDebug("address failed");
        }
    },
    []() {
        qDebug("gather set address timeout cancel");
    });

}

void GatherController::configureSensorCount(int count)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(_gatherData->addr()), static_cast<uint8_t>(count), _gatherData->gatherTimeout());
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
            this->setSensorCount(count);
            qDebug("reset count success");
        } else {
            //TODO(shijm): 失败处理
            qDebug("reset count failed");
        }
    },
    [](){
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

void GatherController::onTitleChanged(const QString &title)
{
    _gatherData->setName(title);
}
bool GatherController::canDoOperate()
{
    bool active = isConnected();
    return active;
}

GatherController *GatherController::setAddress(int addr)
{
    _gatherData->setAddr(addr);
    return this;
}

GatherController *GatherController::setHardwareVersion(const QString &version)
{
    _gatherData->setHardwareVerion(version);
    return this;
}

GatherController *GatherController::setSoftwareVersion(const QString &version)
{
    _gatherData->setSoftwareVersion(version);
    return this;
}

GatherController *GatherController::setProductDesc(const QString &desc)
{
    _gatherData->setProductDesc(desc);
    return this;
}

GatherController *GatherController::setSensorCount(int count)
{
    _gatherData->setSensorCount(count);
    return this;
}
