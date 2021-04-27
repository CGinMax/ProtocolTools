#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QWidget>
#include "../protocol/protocolbase.h"
#include "../../Communication/tcpclient.h"
#include "cdtworkwidget.h"

class QVBoxLayout;

class ClientPage : public QWidget
{
    Q_OBJECT
public:
    explicit ClientPage(const QSharedPointer<SettingData> &settingData, QWidget *parent = nullptr);
    ~ClientPage() override;

    bool start();
    void stop();
signals:
    void clientDisconnected();

public slots:
    void onUpdateData();
private:
    QSharedPointer<CommunicationBase> m_tcpClient;
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<CDTWorkWidget> m_centerWidget;
    QVBoxLayout* m_layout;
};
#endif // CLIENTPAGE_H
