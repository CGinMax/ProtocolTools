#include "ybprotocolchannel.h"
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

    if (m_replyQueue.empty()) {
        return ;
    }

    auto iter = std::find_if(m_replyQueue.begin(), m_replyQueue.end(), [&frame](ProtocolReply* reply){
            return reply->m_funcode == frame.m_funCode;
    });
    if (iter == m_replyQueue.end()) {
        qDebug("unknow frame");
        return;
    }
    auto curReply = *iter;
    m_replyQueue.removeOne(curReply);
    curReply->result = frame.m_dataContent;
    switch (frame.m_funCode) {
    case eYBFunCode::NAKCode:
        emit curReply->error();
        break;
    case eYBFunCode::SetStatusCode:
    case eYBFunCode::QueryStatusCode:
    case eYBFunCode::QueryVersionCode:
    case eYBFunCode::SetAddressCode:
    case eYBFunCode::SetSensorNumCode:
    case eYBFunCode::QueryAddrCode:
        emit curReply->finished();
        qDebug("finish");
        break;
    default:
        break;
    }
}

ProtocolReply *YBProtocolChannel::setAddress(eYBFrameType type, uint8_t addr)
{
    m_sendFrameQueue.enqueue(YBFrame::settingAddress(type, addr));

    auto reply = new ProtocolReply(eYBFunCode::SetAddressCode);
    m_replyQueue.enqueue(reply);
    return reply;
}

ProtocolReply *YBProtocolChannel::queryStatus(uint16_t dstAddr)
{
    m_sendFrameQueue.enqueue(YBFrame::queryStatus(dstAddr));

    auto reply = new ProtocolReply(eYBFunCode::QueryStatusCode);
    m_replyQueue.enqueue(reply);
    return reply;
}

ProtocolReply *YBProtocolChannel::queryVersion(eYBFrameType type, uint16_t dstAddr)
{
    m_sendFrameQueue.enqueue(YBFrame::queryVersion(type, dstAddr));

    auto reply = new ProtocolReply(eYBFunCode::QueryVersionCode);
    m_replyQueue.enqueue(reply);
    return reply;
}

ProtocolReply *YBProtocolChannel::setStatus(uint8_t status, uint16_t dstAddr)
{
    m_sendFrameQueue.enqueue(YBFrame::settingStatus(status, dstAddr));

    auto reply = new ProtocolReply(eYBFunCode::SetStatusCode);
    m_replyQueue.enqueue(reply);
    return reply;
}

ProtocolReply *YBProtocolChannel::setSensorNum(uint16_t dstAddr, uint8_t num)
{
    m_sendFrameQueue.enqueue(YBFrame::setSensorNum(dstAddr, num));

    auto reply = new ProtocolReply(eYBFunCode::SetSensorNumCode);
    m_replyQueue.enqueue(reply);
    return reply;
}

void YBProtocolChannel::processReply(ProtocolReply *reply, std::function<void ()>&& finishFun, std::function<void ()>&& errorFun)
{
    connect(reply, &ProtocolReply::finished, [=]{
        finishFun();
        reply->deleteLater();
    });
    connect(reply, &ProtocolReply::error, [=]{
        errorFun();
        reply->deleteLater();
    });
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
