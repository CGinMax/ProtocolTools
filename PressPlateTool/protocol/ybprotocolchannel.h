#ifndef YBPROTOCOLCHANNEL_H
#define YBPROTOCOLCHANNEL_H

#include "protocolchannelbase.h"
#include "ybprotocol.h"

#include <functional>

class ProtocolReply : public QObject
{
    Q_OBJECT
public:
    ProtocolReply() = default;

signals:
    void finished();
    void error();

public:
    std::shared_ptr<IContent> result;
};

class YBProtocolChannel : public ProtocolChannelBase
{
    Q_OBJECT
public:
    explicit YBProtocolChannel(const QSharedPointer<CommunicationBase>& communication, QObject* parent = nullptr);
    ~YBProtocolChannel() override;

    void run() override;

    void processFrame(const YBFrame& frame);

    ProtocolReply* setAddress(eYBFrameType type, uint8_t addr);

    ProtocolReply* queryStatus(uint16_t dstAddr);

    ProtocolReply* queryVersion(eYBFrameType type, uint16_t dstAddr);

    ProtocolReply* setStatus(uint8_t status, uint16_t dstAddr);

    ProtocolReply* setSensorNum(uint16_t dstAddr, uint8_t num);

    static void processReply(ProtocolReply *reply, std::function<void()> finishFun, std::function<void()> errorFun);

signals:
    void reportStatus(int addr, uint8_t curStatus, uint8_t confStatus);

public slots:
    void onReadyRead() override;

protected:
    YBProtocol* m_protocol;
    std::deque<YBFrame> m_sendFrameQueue;
    ProtocolReply* m_curReply;
    bool m_waitResponse;
};

#endif // YBPROTOCOLCHANNEL_H
