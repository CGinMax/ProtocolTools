#ifndef YBPROTOCOLCHANNEL_H
#define YBPROTOCOLCHANNEL_H

#include "protocolchannelbase.h"
#include "../Protocols/YBProtocol/ybprotocol.h"
#include "../../asyncfuture/asyncfuture.h"

#include <functional>
#include <QQueue>

using IContentDeferredPtr = std::shared_ptr<AsyncFuture::Deferred<std::shared_ptr<IContent>>>;

class ProtocolReply : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolReply(int type, int funcode, int msecTimeout = 5000)
        : m_dirty(false)
        , m_type(type)
        , m_funcode(funcode)
        , m_timer(new QTimer())
        , m_result(new AsyncFuture::Deferred<std::shared_ptr<IContent>>())
    {
        m_timer->setInterval(msecTimeout);
        auto timeout = AsyncFuture::observe(m_timer.get(), &QTimer::timeout).future();
        connect(m_timer.get(), &QTimer::timeout, this, &ProtocolReply::onTimeout);
        m_timer->start();
        m_result->cancel(timeout);
    }
    ~ProtocolReply() override{
        m_timer->stop();
    }

    void cancelTimeout() {
        m_timer->stop();
        disconnect(m_timer.get(), &QTimer::timeout, this, &ProtocolReply::onTimeout);
        m_dirty = true;
    }

    bool m_dirty;
    int m_type;
    int m_funcode;
    std::shared_ptr<QTimer> m_timer;
    IContentDeferredPtr m_result;

public slots:
    void onTimeout() {
        m_dirty = true;
    }
};

class YBProtocolChannel : public ProtocolChannelBase
{
    Q_OBJECT
public:
    explicit YBProtocolChannel(const QSharedPointer<CommunicationBase>& communication, QObject* parent = nullptr);
    ~YBProtocolChannel() override;

    void run() override;

    void processFrame(const YBFrame& frame);

    IContentDeferredPtr setAddress(eYBFrameType type, uint8_t addr, int msecTimeout = 5000);

    IContentDeferredPtr queryStatus(uint16_t dstAddr, int msecTimeout = 5000);

    IContentDeferredPtr queryVersion(eYBFrameType type, uint16_t dstAddr, int msecTimeout = 5000);

    IContentDeferredPtr setStatus(uint8_t status, uint16_t dstAddr, int msecTimeout = 5000);

    IContentDeferredPtr setSensorNum(uint16_t dstAddr, uint8_t num, int msecTimeout = 5000);

    IContentDeferredPtr querySensorAddr(int msecTimeout = 5000);

private:
    IContentDeferredPtr buildResultContent(int type, int funcode, int msecTimeout = 5000);
    void clearDirtyReply();
signals:

public slots:
    void onReadyRead() override;


protected:
    YBProtocol* m_protocol;
    QQueue<YBFrame> m_sendFrameQueue;
    QList<ProtocolReply*> m_replyList;
    bool m_waitResponse;
};

#endif // YBPROTOCOLCHANNEL_H
