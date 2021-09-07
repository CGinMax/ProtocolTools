#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "portparam.h"
#include "gatherdata.h"
#include "ybprotocolchannel.h"

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(QObject *parent = nullptr);
    ~GatherController() override;

    CommunicationBase* rawCommunicationBase();

    Q_INVOKABLE bool startCommunication(const QVariantMap& portMap);
    Q_INVOKABLE bool stopCommunication();

    Q_INVOKABLE bool isConnected();
    YBProtocolChannel* protocol();

    Q_INVOKABLE void queryGatherVersion(int addr, int timeout);
    Q_INVOKABLE void configureGatherAddress(int addr, int timeout);
    Q_INVOKABLE void configureSensorCount(int addr, int count, int timeout);
    Q_INVOKABLE void configureSensorAddr(int index, int addr, int timeout);
    Q_INVOKABLE void configureSensorState(int index, int addr, int state, int timeout);
    Q_INVOKABLE void querySensorVersion(int index, int addr, int timeout);
    Q_INVOKABLE void querySensorState(int index, int addr, int timeout);
    // 用于自动查询地址后，随便发送查状态，不做数据应答
    Q_INVOKABLE void exitConfigureState(int addr, int timeout);
    bool canDoOperate();

    bool error(const std::shared_ptr<IContent>& result, const std::function<void(const QVariantMap&)>& callback);
signals:
    void startPortocolChannel();
    void stopProtocolChannel();
    void showProtocolMsg(const QString& msg);
    void queryVersionCallback(const QVariantMap& result/* bool success, const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString()*/);
    void configureAddressCallback(const QVariantMap& result/* bool success, int addr = 0*/);
    void configureCountCallback(const QVariantMap& result /*bool success, int count = 0*/);
    void configureSensorAddrCallback(const QVariantMap& result/*int index, bool success, int addr = 0*/);
    void configureSensorStateCallback(const QVariantMap& result/*int index, bool success, int state = 0*/);
    void querySensorVersionCallback(const QVariantMap& result/*int index, bool success, const QString& hardware = QString(), const QString& software = QString(), const QString& product = QString()*/);
    void querySensorStateCallback(const QVariantMap& result/*int index, bool success, int curState = 0xFF, int confState = 0xFF*/);

public slots:

private:
    QSharedPointer<GatherData> _gatherData;
    QSharedPointer<CommunicationBase> _communication;
    QSharedPointer<ProtocolChannelBase> _protocol;

};

#endif // GATHERCONTROLLER_H
