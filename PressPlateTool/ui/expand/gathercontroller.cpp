#include "gathercontroller.h"
#include "../../common/threadpool.h"
#include "expandtile.h"
#include "gatheroperwidget.h"
#include "serialport.h"
GatherController::GatherController(GatherData *data, QObject *parent)
    : QObject(parent)
    , m_gatherData(data)
    , m_tile(nullptr)
    , m_operWidget(nullptr)
    , m_communication(new SerialPort(this))
{
    m_communication->open(data->portParam());
    ThreadPool::instance()->run([=](){
        this->m_protocol.reset(new YBProtocolChannel(this->m_communication));
        this->m_protocol->start();
    });

}

GatherController::~GatherController()
{
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

void GatherController::setExpandTile(ExpandTile *tile)
{
    m_tile = tile;

    connect(tile, &ExpandTile::queryVersion, this, &GatherController::onQueryVersion);
    connect(tile, &ExpandTile::titleChanged, this, &GatherController::onTitleChanged);
}

void GatherController::setOperWidget(GatherOperWidget *operWidget)
{
    m_operWidget = operWidget;
    connect(operWidget, &GatherOperWidget::setGatherAddress, this, &GatherController::onSetGatherAddress);
    connect(operWidget, &GatherOperWidget::resetSensorCount, this, &GatherController::onResetSensorCount);

}

YBProtocolChannel *GatherController::protocol()
{
    return static_cast<YBProtocolChannel*>(m_protocol.data());
}

void GatherController::processReply(ProtocolReply *reply, QObject *obj, std::function<void()> finishFun, std::function<void()> errorFun)
{
    connect(reply, &ProtocolReply::finished, obj, [=]{
        finishFun();
        reply->deleteLater();
    });
    connect(reply, &ProtocolReply::error, obj, [=]{
        errorFun();
        reply->deleteLater();
    });
}

void GatherController::onQueryVersion()
{
    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(m_gatherData->addr()));
    processReply(reply, this, [=]{
        m_tile->setHardwareVersion(QString::fromStdString(reply->result->hardwareVersion()));
        m_tile->setSoftwareVersion(QString::fromStdString(reply->result->softwareVersion()));
        m_tile->setProductDescript(QString::fromStdString(reply->result->productDescript()));
    },[=]{
        qDebug("error");
    });
}

void GatherController::onTitleChanged(const QString &title)
{
    m_gatherData->setName(title);
}

void GatherController::onSetGatherAddress(int addr)
{
    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr));
    processReply(reply, this, [=]{
        if (reply->result->success()) {
            m_gatherData->setAddr(reply->result->setAddress());
        } else {
            //TODO(shijm): 失败处理
            qDebug("address failed");
        }
    },[=]{
        qDebug("address error");
    });

}

void GatherController::onResetSensorCount(int count)
{
    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(m_gatherData->addr()), static_cast<uint8_t>(count));
    processReply(reply, this, [=]{
        if (reply->result->success()) {
            qDebug("reset count success");
        } else {
            //TODO(shijm): 失败处理
            qDebug("reset count failed");
        }
    },[=]{
        qDebug("reset count error");
    });
}
