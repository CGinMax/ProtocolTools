#include "gathercontroller.h"
#include "../../common/threadpool.h"
#include "expandtile.h"
#include "gatheroperwidget.h"
#include "serialport.h"

#include <QMessageBox>
GatherController::GatherController(GatherData *data, QObject *parent)
    : QObject(parent)
    , m_gatherData(data)
    , m_tile(nullptr)
    , m_operWidget(nullptr)
    , m_communication(new SerialPort(this))
{
    ThreadPool::instance()->run([=](){
        this->m_protocol.reset(new YBProtocolChannel(this->m_communication));
        this->m_protocol->start();
        connect(this, &GatherController::stopProtocolChannel, this->m_protocol.data(), &ProtocolChannelBase::stop, Qt::BlockingQueuedConnection);
    });

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
    connect(operWidget, &GatherOperWidget::openCommunication, this, [=]{
        auto success = this->m_communication->open(m_gatherData->portParam());
        if (!success) {
            QMessageBox::information(operWidget, tr("Information"), tr("Open failed!"), QMessageBox::Ok);
        }
        operWidget->setButtonsOpened(success);
    });
    connect(operWidget, &GatherOperWidget::closeCommunication, this, [=]{
        this->m_communication->close();
    });
}

YBProtocolChannel *GatherController::protocol()
{
    return static_cast<YBProtocolChannel*>(m_protocol.data());
}

void GatherController::onQueryVersion()
{
    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(m_gatherData->addr()));
    YBProtocolChannel::processReply(reply, [=]{
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
    YBProtocolChannel::processReply(reply, [=]{
        if (reply->result->success()) {
            m_gatherData->setAddr(m_operWidget->getInputAddress());
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
    YBProtocolChannel::processReply(reply, [=]{
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
