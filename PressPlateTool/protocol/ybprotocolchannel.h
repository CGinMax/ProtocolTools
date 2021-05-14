#ifndef YBPROTOCOLCHANNEL_H
#define YBPROTOCOLCHANNEL_H

#include "protocolchannelbase.h"
#include "../Protocols/YBProtocol/ybprotocol.h"

#include <functional>
#include <QQueue>

class ProtocolReply : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolReply(uint8_t funCode)
        : m_funcode(funCode)
    {}

signals:
    void finished();
    void error();

public:
    uint8_t m_funcode;
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

    static void processReply(ProtocolReply *reply, std::function<void()>&& finishFun, std::function<void()>&& errorFun);

signals:

public slots:
    void onReadyRead() override;

protected:
    YBProtocol* m_protocol;
    QQueue<YBFrame> m_sendFrameQueue;
    QQueue<ProtocolReply*> m_replyQueue;
    bool m_waitResponse;
};

#endif // YBPROTOCOLCHANNEL_H
