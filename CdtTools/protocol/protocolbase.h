#ifndef PROTOCOLBASE_H
#define PROTOCOLBASE_H

#include <QObject>
#include <QSharedPointer>
#include "../network/networkbase.h"
#include "../ui/ptcfg.h"

class ProtocolBase : public QObject
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
    ProtocolBase();
    ProtocolBase(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    virtual ~ProtocolBase();

    virtual void run() {}


    bool initConnection();

    bool isConnection();

    void showMessage(eMsgType type, const QString& msg);
    void showMessageBuffer(eMsgType type, const QString& msg, const char* buffer, int len);
    void showMessageBuffer(eMsgType type, const QString& msg, const QByteArray& buffer);

    void sendHumanizeMsg(eMsgType type, const QString& msg, const char* buffer, int len);
    void sendHumanizeMsg(eMsgType type, const QString& msg, const QByteArray& buffer);
    QString bytes2String(const char *buffer, int length);
    QString bytes2String(const QByteArray& buffer);
    QString decorateMsg(eMsgType type, const QString& desc, const QString& bufrString=QString(), int buflen=0);

signals:
    void write(const QByteArray& data);
    void sendProtocolContent(const QString& msg);
    void sendYKMsg(const QString& msg);
    void ykExecuteFinish(const QString& msg);
    void notifyYK(int ptId);

public slots:
    virtual void start();
    virtual void stop();
    virtual void startYK(int ptId, bool offon){
        Q_UNUSED(ptId)
        Q_UNUSED(offon)
    }
    virtual void reverseYx(int ptId, bool allow){
        Q_UNUSED(ptId)
        Q_UNUSED(allow)
    }
protected slots:
    virtual void onTimeout();

protected:
    QSharedPointer<NetworkBase> m_network;
    QSharedPointer<SettingData> m_settingData;
    QTimer *m_timer{nullptr};
};

#endif // PROTOCOLBASE_H
