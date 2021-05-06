#ifndef YBPROTOCOLCHANNEL_H
#define YBPROTOCOLCHANNEL_H

#include "protocolchannelbase.h"
#include "ybprotocol.h"

class YBProtocolChannel : public ProtocolChannelBase
{
    Q_OBJECT
public:
    YBProtocolChannel();
    ~YBProtocolChannel() override;

    void run() override;

    void processFrame(const YBFrame& frame);

public slots:
    void onReadyRead() override;

protected:
    YBProtocol* m_protocol;
};

#endif // YBPROTOCOLCHANNEL_H
