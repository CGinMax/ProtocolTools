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
        connect(this->protocol(), &ProtocolChannelBase::showProtocolMsg, this, &GatherController::showProtocolMsg);
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
    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result == nullptr) {
            qDebug("Unknow frame data");
        } else if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        } /*else {
            qDebug("configure gather address failed!");
        }*/

        emit this->configureAddressCallback(result->success(), addr);
    },
    [=]() {
        emit this->configureAddressCallback(false);
        qDebug("gather set address timeout cancel");
    });

}

void GatherController::configureSensorCount(int addr, int count, int timeout)
{
    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(addr), static_cast<uint8_t>(count), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result == nullptr) {
            qDebug("Unknow frame data");
        } else if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        } /*else {
            qDebug("configure sensor count failed!");
        }*/

        emit this->configureCountCallback(result->success(), count);
    },
    [=](){
        emit this->configureCountCallback(false);
        qDebug("gather set sensor num timeout cancel");
    });
}

void GatherController::configureSensorAddr(int index, int addr, int timeout)
{
    auto reply = protocol()->setAddress(eYBFrameType::YBSensor, static_cast<uint8_t>(addr), timeout);
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

        emit this->configureSensorAddrCallback(index, map);
    }, [=](){
        emit this->configureSensorAddrCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Configure address timeout!")}});
    });
}

void GatherController::configureSensorState(int index, int addr, int state, int timeout)
{
    auto reply = protocol()->setStatus(static_cast<uint8_t>(state & 0xFF), static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        QString errorMsg = result->success() ? "" : tr("Configure state failed!");
        QVariantMap map;
        map.insert(QLatin1String("success"), result->success());
        map.insert(QLatin1String("addr"), addr);
        map.insert(QLatin1String("errorMsg"), errorMsg);
        if (result == nullptr) {
            qDebug("Unknow frame data");
        } else if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->configureSensorStateCallback(index, map);
    }, [=](){
        emit this->configureSensorStateCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Configure state timeout!")}});
    });
}

void GatherController::querySensorVersion(int index, int addr, int timeout)
{
    auto reply = protocol()->queryVersion(eYBFrameType::YBSensor, static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            QVariantMap map;
            map.insert(QLatin1String("success"), true);
            map.insert(QLatin1String("hardware"), QString::fromStdString(result->hardwareVersion()));
            map.insert(QLatin1String("software"), QString::fromStdString(result->softwareVersion()));
            map.insert(QLatin1String("product"), QString::fromStdString(result->productDescript()));
            map.insert(QLatin1String("errorMsg"), QString());
            emit this->querySensorVersionCallback(index, map);
            return ;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->querySensorVersionCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Query version failed!")}});

    }, [this, index](){
        emit this->querySensorVersionCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Query version timeout!")}});
    });
}

void GatherController::querySensorState(int index, int addr, int timeout)
{
    auto reply = protocol()->queryStatus(static_cast<uint16_t>(addr), timeout);
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result != nullptr && result->functionCode() != eYBFunCode::NAKCode) {
            QVariantMap map;
            map.insert(QLatin1String("success"), true);
            map.insert(QLatin1String("curState"), result->currentStatusCode());
            map.insert(QLatin1String("confState"), result->configedStatusCode());
            map.insert(QLatin1String("errorMsg"), QString());
            emit this->querySensorStateCallback(index, map);
            return ;
        }
        if (result == nullptr) {
            qDebug("Unknow frame data");
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
        }
        emit this->querySensorStateCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Query state failed!")}});
    }, [this, index](){
        emit this->querySensorStateCallback(index, {{QString("success"), false}, {QString("errorMsg"), tr("Query state timeout!")}});
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
    return isConnected();
}
