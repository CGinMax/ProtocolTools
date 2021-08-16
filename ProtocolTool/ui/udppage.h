#ifndef UDPPAGE_H
#define UDPPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "../common/threadpool.h"
#include "../protocol/protocolbase.h"
#include "../../Communication/udpsocket.h"
#include "cdtworkwidget.h"


class UdpPage : public QWidget
{
    Q_OBJECT
public:
    explicit UdpPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent = nullptr);
    ~UdpPage() override;

    bool start();
    bool start(const PortParam& param);
    void stop();
signals:

public slots:
    void onUpdateData();

private:
    QSharedPointer<CommunicationBase> m_udp;
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<CDTWorkWidget> m_centerWidget;
    QVBoxLayout* m_layout;
};

#endif // UDPPAGE_H
