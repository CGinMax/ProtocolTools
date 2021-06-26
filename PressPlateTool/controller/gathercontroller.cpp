#include "gathercontroller.h"
#include "../common/threadpool.h"
#include "serialport.h"

GatherController::GatherController(QObject *parent)
    : QObject(parent)
{

}

GatherController::~GatherController()
{
    emit stopProtocolChannel();
    m_communication->close();
}

QSharedPointer<GatherData> GatherController::gatherData() const
{
    return m_gatherData;
}

void GatherController::setGatherData(const QSharedPointer<GatherData> &gatherData)
{
    m_gatherData = gatherData;
}

void GatherController::appendSensorData(YBSensorData *data)
{
    if (m_gatherData.isNull()) {
        return;
    }
    m_gatherData->appendSensorData(data);
}


bool GatherController::isCommunicationActive()
{
    return !m_communication.isNull() && m_communication->isActived();
}

YBProtocolChannel *GatherController::protocol()
{
    return static_cast<YBProtocolChannel*>(m_protocol.data());
}

void GatherController::onQueryVersion()
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(m_gatherData->addr()), m_gatherData->gatherTimeout());
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

void GatherController::onTitleChanged(const QString &title)
{
    m_gatherData->setName(title);
}

void GatherController::onSetGatherAddress(int addr)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr), m_gatherData->gatherTimeout());
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

void GatherController::onResetSensorCount(int count)
{
    if(!canDoOperate()) {
        return;
    }

    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(m_gatherData->addr()), static_cast<uint8_t>(count), m_gatherData->gatherTimeout());
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

bool GatherController::canDoOperate()
{
    bool active = isCommunicationActive();
    return active;
}

GatherController *GatherController::setAddress(int addr)
{
    this->m_gatherData->setAddr(addr);
    return this;
}

GatherController *GatherController::setHardwareVersion(const QString &version)
{
    this->m_gatherData->setHardwareVerion(version);
    return this;
}

GatherController *GatherController::setSoftwareVersion(const QString &version)
{
    this->m_gatherData->setSoftwareVersion(version);
    return this;
}

GatherController *GatherController::setProductDesc(const QString &desc)
{
    this->m_gatherData->setProductDesc(desc);
    return this;
}

GatherController *GatherController::setSensorCount(int count)
{
    this->m_gatherData->setSensorCount(count);
    return this;
}
