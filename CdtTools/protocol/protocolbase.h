#ifndef PROTOCOLBASE_H
#define PROTOCOLBASE_H

#include <QSharedPointer>
#include "../network/networkbase.h"

class ProtocolBase
{
public:
    ProtocolBase();
    ProtocolBase(const QSharedPointer<NetworkBase>& network);
    virtual ~ProtocolBase();

    virtual void run() {}

    virtual void start(){}
    virtual void stop(){}

    bool initConnection();

    QSharedPointer<NetworkBase> m_network;
};

#endif // PROTOCOLBASE_H
