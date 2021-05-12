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
        auto frame = m_sendFrameQueue.front();
        m_sendFrameQueue.pop_front();

        auto ucharVector = frame.packetFrame();
        QByteArray bytearray(reinterpret_cast<char*>(ucharVector.data()), ucharVector.size());

        qDebug() << m_communication->isActived();
        emit write(bytearray);
    }
}

void YBProtocolChannel::processFrame(const YBFrame &frame)
{
    if (frame.funCode == eYBFunCode::ReportStatusCode) {
        auto bytes = frame.dataContent->toByteVector();
        emit reportStatus(frame.dstAddr, bytes.at(0), bytes.at(1));
        return ;
    }

    m_curReply->result = frame.dataContent;
    switch (frame.funCode) {
    case eYBFunCode::NAKCode:
        emit m_curReply->error();
        break;
    case eYBFunCode::SetStatusCode:
    case eYBFunCode::QueryStatusCode:
    case eYBFunCode::QueryVersionCode:
    case eYBFunCode::SetAddressCode:
    case eYBFunCode::SetSensorNumCode:
    case eYBFunCode::QueryAddrCode:
        emit m_curReply->finished();
        break;
    default:
        break;
    }
}

ProtocolReply *YBProtocolChannel::setAddress(eYBFrameType type, uint8_t addr)
{
    m_sendFrameQueue.push_back(m_protocol->settingAddress(type, addr));

    m_curReply = new ProtocolReply();
    return m_curReply;
}

ProtocolReply *YBProtocolChannel::queryVersion(eYBFrameType type, uint16_t dstAddr)
{
    m_sendFrameQueue.push_back(m_protocol->queryVersion(type, dstAddr));

    m_curReply = new ProtocolReply();
    return m_curReply;
}

ProtocolReply *YBProtocolChannel::setSensorNum(uint16_t dstAddr, uint8_t num)
{
    m_sendFrameQueue.push_back(m_protocol->setSensorNum(dstAddr, num));

    m_curReply = new ProtocolReply();
    return m_curReply;
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
    while (!m_protocol->recvFrameEmpty()) {
        auto frame = m_protocol->popRecvFrame();
        processFrame(frame);
    }
}