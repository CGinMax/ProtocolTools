#ifndef PROTOCOLBASE_H
#define PROTOCOLBASE_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include "../network/networkbase.h"
#include "../common/ptcfg.h"
#include "strategybase.h"

class  ProtocolBase : public QObject
{
    Q_OBJECT
public:
    enum eMsgType {
        //其他
        eMsgOther = 0,
        //连接
        eMsgLink = 1,
        //发送
        eMsgSend = 2,
        //接收
        eMsgRecv = 3,
    };
    ProtocolBase(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    virtual ~ProtocolBase();

    virtual void initStrategy() = 0;

    virtual void run() {}

    bool initConnection();

    virtual void processPortOpenSucceed();

    bool isConnection();

    void showMessage(eMsgType type, const QString& msg);
    void showMessageBuffer(eMsgType type, const QString& msg, const char* buffer, int len);
    void showMessageBuffer(eMsgType type, const QString& msg, const QByteArray& buffer);

    void sendHumanizeMsg(eMsgType type, const QString& msg, const char* buffer, int len);
    void sendHumanizeMsg(eMsgType type, const QString& msg, const QByteArray& buffer);

    QString decorateMsg(eMsgType type, const QString& desc, const QString& bufrString=QString(), int buflen=0);

signals:
    void write(const QByteArray& data);
    void sendProtocolContent(const QString& msg);
    void sendYKMsg(const QString& msg);
    void notifyYK(int ptId);

    void lockOrUnlock(bool locked);
    void sendYk(int ptId, bool offon);

public slots:
    virtual void start();
    virtual void stop();

    // lock true为闭锁，false为解锁

    virtual void onReverseYx(int ptId, bool allow){
        Q_UNUSED(ptId)
        Q_UNUSED(allow)
    }
    virtual void onReadyRead() {}
    virtual void onDisconnected() {}
protected slots:
    virtual void onTimeout();

protected:
    QSharedPointer<NetworkBase> m_network;
    QSharedPointer<SettingData> m_settingData;
    StrategyBase* m_strategy;
    QTimer *m_timer{nullptr};

    int m_portOpenFailedCount;
};

#endif // PROTOCOLBASE_H
