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
    explicit ProtocolChannelBase(const QSharedPointer<CommunicationBase>& communication, QObject* parent = nullptr);
    ~ProtocolChannelBase() override;

    virtual void run() {}

signals:
    void write(const QByteArray& data);
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
