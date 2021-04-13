#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QWidget>
#include "../common/threadpool.h"
#include "../protocol/protocolbase.h"
#include "../network/networkbase.h"
#include "../network/tcpclient.h"
#include "cdtworkwidget.h"

class QVBoxLayout;

class ClientPage : public QWidget
{
    Q_OBJECT
public:
    explicit ClientPage(const QSharedPointer<SettingData> &ptCfg, QWidget *parent = nullptr);
    ~ClientPage();

    bool start();
    void stop();
signals:
    void clientDisconnected();

public slots:
    void onUpdateData();
private:
    QSharedPointer<NetworkBase> m_tcpClient;
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<CDTWorkWidget> m_centerWidget;
    QVBoxLayout* m_layout;
};
#endif // CLIENTPAGE_H
