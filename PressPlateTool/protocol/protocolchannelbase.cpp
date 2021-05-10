#include "protocolchannelbase.h"

ProtocolChannelBase::ProtocolChannelBase(const QSharedPointer<CommunicationBase> &communication, QObject *parent)
    : QObject(parent)
    , m_communication(communication)
    , m_loopTimer(new QTimer())
{
    connect(this, &ProtocolChannelBase::write, m_communication.data(), &CommunicationBase::writeData);
    connect(m_loopTimer.data(), &QTimer::timeout, this, &ProtocolChannelBase::onTimeout);
    connect(m_communication.data(), &CommunicationBase::readyRead, this, &ProtocolChannelBase::onReadyRead);
}

ProtocolChannelBase::~ProtocolChannelBase()
{

}

void ProtocolChannelBase::start()
{
    if (!m_loopTimer->isActive()) {
        m_loopTimer->start(100);
    }
}

void ProtocolChannelBase::stop()
{
    m_loopTimer->stop();
    disconnect(m_communication.data(), &CommunicationBase::readyRead, this, &ProtocolChannelBase::onReadyRead);
}

void ProtocolChannelBase::onTimeout()
{
    this->run();
}
