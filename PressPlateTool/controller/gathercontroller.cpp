#include "gathercontroller.h"
#include "../common/threadpool.h"
#include "serialport.h"
using namespace std::placeholders;

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
        connect(this->protocol(), &ProtocolChannelBase::showProtocolMsg, this, &GatherController::showProtocolMsg);
        connect(this, &GatherController::cancelLongConfigAddr, static_cast<YBProtocolChannel*>(this->protocol()), &YBProtocolChannel::cancelLongConfigAddr);
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

void GatherController::queryGatherVersion(int addr, int timeout)
{
    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::queryVersionCallback, this, _1))) {
            return ;
        }
        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("hardware"), QString::fromStdString(result->hardwareVersion()));
        map.insert(QLatin1String("software"), QString::fromStdString(result->softwareVersion()));
        map.insert(QLatin1String("product"),  QString::fromStdString(result->productDescript()));


        emit this->queryVersionCallback(map);

    }, [=](){
        emit this->queryVersionCallback({{QString("success"), false}, {QString("errorMsg"), tr("Query gather version timeout!")}});
        qDebug("gather query version timeout cancel");
    });
}

void GatherController::configureGatherAddress(int addr, int timeout)
{
    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::configureAddressCallback, this, _1))) {
            return ;
        }
        QString errorMsg = result->success() ? "" : tr("Configure gather address failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("errorMsg"), errorMsg);

        emit this->configureAddressCallback(map);
    },
    [=]() {
        emit this->configureAddressCallback({{QString("success"), false}, {QString("errorMsg"), tr("Configure gather addr timeout!")}});
        qDebug("gather set address timeout cancel");
    });

}

void GatherController::configureSensorCount(int addr, int count, int timeout)
{
    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(addr), static_cast<uint8_t>(count), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::configureCountCallback, this, _1))) {
            return ;
        }
        QString errorMsg = result->success() ? "" : tr("Configure gather's sensor count failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("count"), count);
        map.insert(QLatin1String("errorMsg"), errorMsg);
        emit this->configureCountCallback(map);
    },
    [=](){
        emit this->configureCountCallback({{QString("success"), false}, {QString("errorMsg"), tr("Configure gather's sensor count timeout!")}});
        qDebug("gather set sensor num timeout cancel");
    });
}

void GatherController::configureSensorAddr(int index, int addr, int timeout)
{
    auto reply = protocol()->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::configureSensorAddrCallback, this, _1))) {
            return ;
        }
        QString errorMsg = result->success() ? "" : tr("Configure sensor address failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("index"), index);
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("errorMsg"), errorMsg);

        emit this->configureSensorAddrCallback(map);
    }, [=](){
        emit this->configureSensorAddrCallback({{QString("success"), false},
                                                {QString("addr"), addr},
                                                {QString("index"), index},
                                                {QString("errorMsg"), tr("Configure sensor address timeout!")}});
    });
}

void GatherController::configureSensorState(int index, int addr, int state, int timeout)
{
    auto reply = protocol()->setStatus(static_cast<uint8_t>(state & 0xFF), static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::configureSensorStateCallback, this, _1))) {
            return ;
        }
        QString errorMsg = result->success() ? "" : tr("Configure sensor state failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("index"), index);
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("state"), state);
        map.insert(QLatin1String("errorMsg"), errorMsg);

        emit this->configureSensorStateCallback(map);
    }, [=](){
        emit this->configureSensorStateCallback({{QString("success"), false},
                                                 {QString("state"), state},
                                                 {QString("index"), index},
                                                 {QString("errorMsg"), tr("Configure sensor state timeout!")}});
    });
}

void GatherController::querySensorVersion(int index, int addr, int timeout)
{
    auto reply = protocol()->queryVersion(eYBFrameType::YBSensor, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::querySensorVersionCallback, this, _1))) {
            return ;
        }
        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("index"), index);
        map.insert(QLatin1String("hardware"), QString::fromStdString(result->hardwareVersion()));
        map.insert(QLatin1String("software"), QString::fromStdString(result->softwareVersion()));
        map.insert(QLatin1String("product"), QString::fromStdString(result->productDescript()));
        emit this->querySensorVersionCallback(map);

    }, [this, index](){
        emit this->querySensorVersionCallback({{QString("success"), false},
                                               {QString("index"), index},
                                               {QString("errorMsg"), tr("Query sensor version timeout!")}});
    });
}

void GatherController::querySensorState(int index, int addr, int timeout)
{
    auto reply = protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (!this->error(result, std::bind(&GatherController::querySensorStateCallback, this, _1))) {
            return;
        }
        QVariantMap map;
        map.insert(QLatin1String("success"), true);
        map.insert(QLatin1String("index"), index);
        map.insert(QLatin1String("curState"), result->currentStatusCode());
        map.insert(QLatin1String("confState"), result->configedStatusCode());
        emit this->querySensorStateCallback(map);

    }, [this, index](){
        emit this->querySensorStateCallback({{QString("success"), false},
                                             {QString("index"), index},
                                             {QString("errorMsg"), tr("Query state timeout!")}});
    });
}

void GatherController::exitConfigureState(int addr, int timeout)
{
    auto reply = protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){}, [](){});
}

//void GatherController::cancelLongConfigAddr()
//{
//    protocol()->cancelLongConfigAddr();
//}

bool GatherController::isConnected()
{
    return !_communication.isNull() && _communication->isActived();
}

YBProtocolChannel *GatherController::protocol()
{
    return dynamic_cast<YBProtocolChannel*>(_protocol.data());
}
bool GatherController::canDoOperate()
{
    return isConnected();
}

bool GatherController::error(const std::shared_ptr<IContent> &result, const std::function<void (const QVariantMap &)> &callback)
{
    if (result == nullptr) {
        qDebug("Unknow frame data");
        callback({{QString("success"), false}, {QString("errorMsg"), tr("Unknow frame data!")}});
        return false;
    }
    if (result->functionCode() == eYBFunCode::NAKCode) {
        qDebug("NAK Error");
        callback({{QString("success"), false}, {QString("errorMsg"), tr("NAK frame error!")}});
        return false;
    }
    return true;
}
