#ifndef PROTOCOLCHANNELBASE_H
#define PROTOCOLCHANNELBASE_H

#include <QObject>
#include <QTimer>
#include <QSharedPointer>
#include "communicationbase.h"
class ProtocolChannelBase : public QObject
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
    explicit ProtocolChannelBase(const QSharedPointer<CommunicationBase>& communication, QObject* parent = nullptr);
    ~ProtocolChannelBase() override;

    virtual void run() {}

    void showMessage(eMsgType type, const std::string& msg, const std::vector<uint8_t>& buffer = std::vector<uint8_t>());

protected:
    QString transferMsgHumanize(eMsgType type, const std::string& msg, const std::vector<uint8_t>& buffer);
    QString decorateMsg(eMsgType type, const std::string &desc, const std::string &bufString, int buflen);
signals:
    void write(const QByteArray& data);
    void showProtocolMsg(const QString& msg);
public slots:
    virtual void start();
    virtual void stop();

    virtual void onReadyRead(){}

protected slots:
    virtual void onTimeout();

protected:
    QSharedPointer<CommunicationBase> m_communication;
    QScopedPointer<QTimer> m_loopTimer;
};

#endif // PROTOCOLCHANNELBASE_H
