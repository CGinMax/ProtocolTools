#ifndef PROTOCOLBASE_H
#define PROTOCOLBASE_H

#include <QSharedPointer>
#include "../network/networkbase.h"
#include "../ui/ptcfg.h"

class ProtocolBase
{
public:
    ProtocolBase();
    ProtocolBase(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    virtual ~ProtocolBase();

    virtual void run() {}

    virtual void start(){}
    virtual void stop(){}

    bool initConnection();
protected:
    QSharedPointer<NetworkBase> m_network;
    QSharedPointer<SettingData> m_settingData;
};

#endif // PROTOCOLBASE_H
