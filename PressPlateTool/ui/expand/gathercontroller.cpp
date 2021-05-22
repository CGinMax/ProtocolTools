#include "gathercontroller.h"
#include "../../common/threadpool.h"
#include "expandtile.h"
#include "gatheroperwidget.h"
#include "serialport.h"
#include "../notification/snackbar.h"
#include "../../mainwindow.h"

#include <QApplication>

#include <QDebug>
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

    connect(tile, &ExpandTile::deleteItem, this, &GatherController::deleteItem);
}

void GatherController::setOperWidget(GatherOperWidget *operWidget)
{
    m_operWidget = operWidget;
    m_gatherData->setAddr(m_operWidget->getInputAddress());
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
        operWidget->setButtonsOpened(false);
    });
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

    auto reply = protocol()->queryVersion(eYBFrameType::YBGather, static_cast<uint16_t>(m_gatherData->addr()));
    reply->subscribe([=](std::shared_ptr<IContent> result){
        if (result == nullptr) {
            qDebug("Unknow frame data");
            return ;
        }
        if (result->functionCode() == eYBFunCode::NAKCode) {
            qDebug("NAK Error");
            return ;
        }
        this->m_tile->setHardwareVersion(QString::fromStdString(result->hardwareVersion()));
        this->m_tile->setSoftwareVersion(QString::fromStdString(result->softwareVersion()));
        this->m_tile->setProductDescript(QString::fromStdString(result->productDescript()));

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

    auto reply = protocol()->setAddress(eYBFrameType::YBGather, static_cast<uint8_t>(addr));
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
            m_gatherData->setAddr(m_operWidget->getInputAddress());
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

    auto reply = protocol()->setSensorNum(static_cast<uint16_t>(m_gatherData->addr()), static_cast<uint8_t>(count));
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
    if (!active) {
        MainWindow::showSnackBar(tr("Can not operate!"));
    }
    return active;
}
