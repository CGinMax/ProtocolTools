#include "ybprotocolchannel.h"

YBProtocolChannel::YBProtocolChannel()
{

}

YBProtocolChannel::~YBProtocolChannel()
{

}


void YBProtocolChannel::run()
{
}

void YBProtocolChannel::processFrame(const YBFrame &frame)
{
    switch (frame.funCode) {
    case eYBFunCode::NAKCode:
        break;
    case eYBFunCode::SettingStatusCode:
        break;
    case eYBFunCode::QueryStatusCode:
        break;
    case eYBFunCode::QueryVersionCode:
        break;
    case eYBFunCode::SettingAddrCode:
        break;
    case eYBFunCode::ReportStatusCode:
        break;
    case eYBFunCode::QueryAddrCode:
        break;

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
    while (!m_protocol->getRecvFrameQueue().empty()) {
        auto frame = m_protocol->getRecvFrameQueue().front();
        m_protocol->getRecvFrameQueue().pop_front();
        processFrame(frame);
    }
}
