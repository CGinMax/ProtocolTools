#include "ybprotocolchannel.h"

#include "../Protocols/YBProtocol/content/contentfactory.h"
#include <QDebug>
#include <QThread>
YBProtocolChannel::YBProtocolChannel(const QSharedPointer<CommunicationBase> &communication, QObject *parent)
    : ProtocolChannelBase (communication, parent)
    , m_protocol(new YBProtocol())
    , m_waitResponse(false)
{

}

YBProtocolChannel::~YBProtocolChannel()
{

}


void YBProtocolChannel::run()
{
    if (!m_waitResponse && !m_sendFrameQueue.empty()) {

        auto frame = m_sendFrameQueue.dequeue();

        auto srcBytes = frame.packetFrameToPureData();
        QByteArray bytearray(reinterpret_cast<char*>(srcBytes.data()), static_cast<int>(srcBytes.size()));
        emit write(bytearray);

        showMessage(eMsgType::eMsgSend, frame.parseToString(), srcBytes);

    }
}

void YBProtocolChannel::processFrame(const YBFrame &frame)
{
    if (m_replyList.isEmpty()) {
        return ;
    }

    clearDirtyReply();

    auto iter = std::find_if(m_replyList.begin(), m_replyList.end(), [&frame](ProtocolReply* reply){
        return (reply->m_type == frame.m_srcType) && (reply->m_funcode == frame.m_funCode);
    });
    if (iter == m_replyList.end()) {
        qDebug("Invalid reply frame");
        return;
    }

    auto reply = *iter;
    reply->m_result->complete(std::shared_ptr<IContent>(ContentFactory::createContent(frame.m_funCode, frame.m_data)));
    reply->cancelTimeout();
    m_replyList.erase(iter);
    delete reply;

//    switch (frame.m_funCode) {
//    case eYBFunCode::NAKCode:
//        qDebug("Nak");
//        break;
//    case eYBFunCode::SetStatusCode:
//    case eYBFunCode::QueryStatusCode:
//    case eYBFunCode::QueryVersionCode:
//    case eYBFunCode::SetAddressCode:
//    case eYBFunCode::SetSensorNumCode:
//    case eYBFunCode::QueryAddrCode:
//        qDebug("finish");
//        break;
//    default:
//        break;
//    }
}

IContentDeferredPtr YBProtocolChannel::setAddress(eYBFrameType type, uint8_t addr, int msecTimeout)
{
    auto frame = YBFrame::settingAddress(type, addr);
    m_sendFrameQueue.enqueue(frame);

    return buildResultContent(frame.m_dstType, frame.m_funCode, msecTimeout);
}

IContentDeferredPtr YBProtocolChannel::queryStatus(uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::queryStatus(dstAddr);
    m_sendFrameQueue.enqueue(frame);

    return buildResultContent(frame.m_dstType, frame.m_funCode, msecTimeout);
}

IContentDeferredPtr YBProtocolChannel::queryVersion(eYBFrameType type, uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::queryVersion(type, dstAddr);
    m_sendFrameQueue.enqueue(frame);

    return buildResultContent(frame.m_dstType, frame.m_funCode, msecTimeout);
}

IContentDeferredPtr YBProtocolChannel::setStatus(uint8_t status, uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::settingStatus(status, dstAddr);
    m_sendFrameQueue.enqueue(frame);

    return buildResultContent(frame.m_dstType, frame.m_funCode, msecTimeout);
}

IContentDeferredPtr YBProtocolChannel::setSensorNum(uint16_t dstAddr, uint8_t num, int msecTimeout)
{
    auto frame = YBFrame::setSensorNum(dstAddr, num);
    m_sendFrameQueue.enqueue(frame);

    return buildResultContent(frame.m_dstType, frame.m_funCode, msecTimeout);
}

IContentDeferredPtr YBProtocolChannel::buildResultContent(int type, int funcode, int msecTimeout)
{
    auto reply = new ProtocolReply(type, funcode, msecTimeout);
    reply->m_timer->moveToThread(this->thread());
    m_replyList.append(reply);
    return reply->m_result;
}

void YBProtocolChannel::clearDirtyReply()
{
    for (auto iter = m_replyList.begin(); iter != m_replyList.end();) {
        if ((*iter)->m_dirty) {
            auto reply = *iter;
            iter = m_replyList.erase(iter);
            reply->cancelTimeout();
            delete reply;

        } else {
            iter++;
        }
    }
}

void YBProtocolChannel::onReadyRead()
{
    auto bytes = m_communication->readAll();

    if (!bytes.isEmpty()) {
        m_protocol->appendDatas(reinterpret_cast<uint8_t*>(bytes.data()), bytes.size());
        //处理数据
        m_protocol->parseRecvData();
    }
    // 处理帧
    while (!m_protocol->isRecvFrameEmpty()) {
        auto frame = m_protocol->popRecvFrame();
        showMessage(eMsgType::eMsgRecv, frame.parseToString(), frame.packetFrameToPureData());
        processFrame(frame);
    }
}
