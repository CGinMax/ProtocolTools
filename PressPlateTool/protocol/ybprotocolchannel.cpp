#include "ybprotocolchannel.h"

#include "../Protocols/YBProtocol/content/contentfactory.h"
#include <QtDebug>
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

    auto iter = std::find_if(m_replyList.begin(), m_replyList.end(), [&frame](const ProtocolReply& reply){
        return (reply.m_type == frame.m_srcType) && (reply.m_funcode == frame.m_funCode);
    });
    if (iter == m_replyList.end()) {
        qDebug("unknow frame");
        return;
    }

    iter->m_result->complete(std::shared_ptr<IContent>(ContentFactory::createContent(frame.m_funCode, frame.m_data)));
    m_replyList.erase(iter);
    switch (frame.m_funCode) {
    case eYBFunCode::NAKCode:
        qDebug("Nak");
        break;
    case eYBFunCode::SetStatusCode:
    case eYBFunCode::QueryStatusCode:
    case eYBFunCode::QueryVersionCode:
    case eYBFunCode::SetAddressCode:
    case eYBFunCode::SetSensorNumCode:
    case eYBFunCode::QueryAddrCode:
        qDebug("finish");
        break;
    default:
        break;
    }
}

IContentDeferredPtr YBProtocolChannel::setAddress(eYBFrameType type, uint8_t addr, int msecTimeout)
{
    auto frame = YBFrame::settingAddress(type, addr);
    m_sendFrameQueue.enqueue(frame);

    ProtocolReply reply(frame.m_dstType, frame.m_funCode, msecTimeout);
    m_replyList.append(reply);
    return reply.m_result;
}

IContentDeferredPtr YBProtocolChannel::queryStatus(uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::queryStatus(dstAddr);
    m_sendFrameQueue.enqueue(frame);

    ProtocolReply reply(frame.m_dstType, frame.m_funCode, msecTimeout);
    m_replyList.append(reply);
    return reply.m_result;
}

IContentDeferredPtr YBProtocolChannel::queryVersion(eYBFrameType type, uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::queryVersion(type, dstAddr);
    m_sendFrameQueue.enqueue(frame);


    ProtocolReply reply(frame.m_dstType, frame.m_funCode, msecTimeout);
    connect(reply.m_timer.get(), &QTimer::timeout, this, &YBProtocolChannel::onReplyTimeout);
    m_replyList.append(reply);
    return reply.m_result;
}

IContentDeferredPtr YBProtocolChannel::setStatus(uint8_t status, uint16_t dstAddr, int msecTimeout)
{
    auto frame = YBFrame::settingStatus(status, dstAddr);
    m_sendFrameQueue.enqueue(frame);

    ProtocolReply reply(frame.m_dstType, frame.m_funCode, msecTimeout);
    m_replyList.append(reply);
    return reply.m_result;
}

IContentDeferredPtr YBProtocolChannel::setSensorNum(uint16_t dstAddr, uint8_t num, int msecTimeout)
{
    auto frame = YBFrame::setSensorNum(dstAddr, num);
    m_sendFrameQueue.enqueue(frame);

    ProtocolReply reply(frame.m_dstType, frame.m_funCode, msecTimeout);
    m_replyList.append(reply);
    return reply.m_result;
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

void YBProtocolChannel::onReplyTimeout()
{
    auto timer = qobject_cast<QTimer*>(sender());
    auto iter = std::find_if(m_replyList.begin(), m_replyList.end(), [=](const ProtocolReply& reply){
        return reply.m_timer.get() == timer;
    });
    if (iter == m_replyList.end()) {
        qDebug("not found");
    }
    m_replyList.erase(iter);
}
